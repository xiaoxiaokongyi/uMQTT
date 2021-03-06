/******************************************************************************
 * File: uMQTT_linux_client.c
 * Description: Functions to implement socket based Linux client.
 * Author: Steven Swann - swannonline@googlemail.com
 *
 * Copyright (c) swannonline, 2013-2014
 *
 * This file is part of uMQTT.
 *
 * uMQTT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * uMQTT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with uMQTT.  If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include "uMQTT_linux_client.h"
#include "uMQTT_helper.h"
#include "inc/log.h"

/**
 * \brief Function to initialise socket based broker connection struct.
 * \param conn_p Pointer to the address of the new connection struct.
 * \param ip Pointer to the IP address string.
 * \param ip_len The length of the IP address string.
 * \param port The port to connect to.
 */
void init_linux_socket_connection(struct broker_conn **conn_p, char *ip,
    unsigned int ip_len, unsigned int port) {
  LOG_DEBUG_FN("fn: init_linux_socket_connection");

  struct broker_conn *conn;

  init_connection(&conn);
  struct linux_broker_socket *skt = '\0';

  if (conn && (!(skt = calloc(1, sizeof(struct linux_broker_socket))))) {
      LOG_ERROR("Allocating space for the broker connection failed");
      free_linux_socket(conn);
      return;
  }

  skt->serv_addr.sin_family = AF_INET;
  skt->port = port;
  skt->serv_addr.sin_port = htons(skt->port);
  memcpy(skt->ip, ip, ip_len);

  register_connection_methods(conn, linux_socket_connect,
      linux_socket_disconnect, send_socket_packet, read_socket_packet,
      broker_process_packet, free_linux_socket);

  conn->context = skt;
  *conn_p = conn;

  return;
}

/**
 * \brief Function to connect to linux socket.
 * \param conn Pointer to the broker_conn struct.
 * \return mqtt_ret
 */
umqtt_ret linux_socket_connect(struct broker_conn *conn) {
  LOG_DEBUG_FN("fn: linux_socket_connect");

  struct linux_broker_socket *skt = (struct linux_broker_socket *)conn->context;

  if ((skt->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    LOG_ERROR("Could not create socket");
    return UMQTT_CONNECT_ERROR;
  }

  /* convert ip address to binary */
  if (inet_pton(skt->serv_addr.sin_family, skt->ip,
        &skt->serv_addr.sin_addr) <= 0)
  {
    LOG_ERROR("inet_pton error occured");
    return UMQTT_CONNECT_ERROR;
  }

  if (connect(skt->sockfd, (struct sockaddr *)&skt->serv_addr,
        sizeof(skt->serv_addr)) == -1)
  {
    LOG_ERROR("Connect Failed: %s", strerror(errno));
    return UMQTT_CONNECT_ERROR;
  }

  return UMQTT_SUCCESS;
}

/**
 * \brief Function to disconnect from linux socket.
 * \param conn Pointer to the broker_conn struct.
 * \return mqtt_ret
 */
umqtt_ret linux_socket_disconnect(struct broker_conn *conn) {
  LOG_DEBUG_FN("fn: linux_socket_disconnect");
  struct linux_broker_socket *skt = (struct linux_broker_socket *)conn->context;

  if (skt->sockfd) {
    if (close(skt->sockfd)) {
      return UMQTT_DISCONNECT_ERROR;
    }
  }

  return UMQTT_SUCCESS;
}

/**
 * \brief Function to send packet to the to the broker socket.
 * \param conn Pointer to the croker_conn struct.
 * \param pkt Pointer to the packet to be sent.
 */
umqtt_ret send_socket_packet(struct broker_conn *conn, struct mqtt_packet *pkt) {
  LOG_DEBUG_FN("fn: send_socket_packet");

  LOG_DEBUG("TX: %s", get_type_string(pkt->fixed->generic.type));

  umqtt_ret ret = UMQTT_SUCCESS;
  struct linux_broker_socket *skt = (struct linux_broker_socket *)conn->context;
  print_packet_raw_debug(pkt);
  int n = write(skt->sockfd, pkt->raw.buf, pkt->len);
  if (n < 0) {
    LOG_ERROR("writing to socket");
    ret = UMQTT_SEND_ERROR;
  }

  return ret;
}

/**
 * \brief Function to receive packet from the broker socket.
 * \param conn Pointer to the croker_conn struct.
 * \param pkt Pointer to the receiver buffer/packet.
 * \return Number of bytes read.
 */
umqtt_ret read_socket_packet(struct broker_conn *conn, struct mqtt_packet *pkt) {
  LOG_DEBUG_FN("fn: read_socket_packet");

  umqtt_ret ret = UMQTT_SUCCESS;
  ssize_t len = 0;
  size_t read_len = 0;
#if DEBUG
  static ssize_t largest = 0;
#endif

  struct linux_broker_socket *skt = (struct linux_broker_socket *)conn->context;

  /* Peek the packet fixed header to determine the packet length */
  do {
    len = recv(skt->sockfd, pkt->raw.buf, sizeof(struct pkt_fixed_header),
        MSG_PEEK);
  } while (len < MQTT_MIN_PKT_LEN && len > 0);

  if (len == 0) {
    /* Possibly disconnected from broker */
    ret = UMQTT_RECEIVE_ERROR;
    goto exit;
  }

  pkt->fixed = (struct pkt_fixed_header *)pkt->raw.buf;

  /* Get size of packet */
  pkt->len = decode_remaining_len(pkt);
  pkt->len += required_remaining_len_bytes(pkt->len) + 1;
  LOG_DEBUG("Detected packet length: %zu", pkt->len);

#if DEBUG
  if (pkt->len > largest) {
    largest = pkt->len;
  }
  LOG_DEBUG("Largest packet detected: %zu", largest);
#endif

  if (pkt->len > pkt->raw.len) {
    LOG_DEBUG("Resizing packet from: %zu to: %zu bytes", pkt->raw.len, pkt->len);
    ret = resize_packet(&pkt, pkt->len);
    if (ret) {
      goto exit;
    }
  }

  /* Ensure we read all bytes of the packet */
  while (read_len < pkt->len) {
    len = 0;
    len = recv(skt->sockfd, pkt->raw.buf + read_len, pkt->len - read_len , 0);
    if (len < 0) {
      LOG_ERROR("Reading from socket %s", strerror(errno));
      ret = UMQTT_RECEIVE_ERROR;
      break;
    }

    read_len += len;
    LOG_DEBUG("Bytes expected: %zu, received: %zu, total: %zu", pkt->len,
        len, read_len);
  }

  /* Ensure read was sucessful */
  if (!ret && read_len >= MQTT_MIN_PKT_LEN) {

    pkt->len = read_len;
    print_packet_raw_debug(pkt);

    ret = disect_raw_packet(pkt);
    if (ret) {
      LOG_ERROR("Failed to decode %s packet.",
          get_type_string(pkt->fixed->generic.type));
      conn->fail_count++;

    } else {
      LOG_DEBUG("RX: %s - %zu bytes",
          get_type_string(pkt->fixed->generic.type), pkt->len);

      /* Update packet counts */
      conn->success_count++;
      if (pkt->fixed->generic.type == PUBLISH) {
        conn->publish_count++;
      }

      /* Can we process the message? */
      if (conn->process_method) {
        ret = conn->process_method(conn, pkt);
      }
    }
  }

exit:
  return ret;
}

/**
 * \brief Function to free memory allocated to struct broker_conn.
 * \param conn The connection to free.
 */
void free_linux_socket(struct broker_conn *conn) {
  LOG_DEBUG_FN("fn: free_linux_socket");
  struct linux_broker_socket *skt = (struct linux_broker_socket *)conn->context;
  if (skt) {
    free(skt);
  }

  return;
}
