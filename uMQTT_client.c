/******************************************************************************
 * File: uMQTT_client.c
 * Description: Functions to implement socket based client.
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
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

#include "uMQTT.h"
#include "uMQTT_client.h"

/**
 * \brief Function to allocate memory for a broker connection struct.
 * \param conn_p Pointer to the address of the new connection struct.
 */
void init_connection(struct broker_conn **conn_p, char *ip, unsigned int ip_len,  unsigned int port) {
  struct broker_conn *conn;

  if (!(conn = calloc(1, sizeof(struct broker_conn)))) {
    printf("Error: Allocating space for the broker connection failed.\n");
    //free_pkt(pkt);
  }

  /* the following should be dynamic */
  conn->serv_addr.sin_family = AF_INET;
  conn->port = port;
  conn->serv_addr.sin_port = htons(conn->port); 
  memcpy(conn->ip, ip, ip_len);

  *conn_p = conn;

  return;
}

/**
 * \brief Function to allocate memory for a raw_pkt struct.
 * \param pkt_p Pointer to the address of the new packet.
 */
void init_raw_packet(struct raw_pkt **pkt_p) {
  struct raw_pkt *pkt;

  if (!(pkt = calloc(1, sizeof(struct raw_pkt)))) {
    printf("Error: Allocating space for the new packet failed.\n");
    //free_pkt(pkt);
  }

  *pkt_p = pkt;
  return;
}

/**
 * \brief Function to connect to broker socket.
 * \param conn Pointer to the broker_conn struct.
 */
int broker_connect(struct broker_conn *conn) {

  if ((conn->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("Error: Could not create socket\n");
    return 1;
  } 

  /* convert ip address to binary */
  if (inet_pton(conn->serv_addr.sin_family, conn->ip,
        &conn->serv_addr.sin_addr) <= 0)
  {
    printf("\n inet_pton error occured\n");
    return 1;
  } 

  if (connect(conn->sockfd, (struct sockaddr *)&conn->serv_addr,
        sizeof(conn->serv_addr)) < 0)
  {
    printf("\n Error : Connect Failed \n");
    return 1;
  } 

  return conn->sockfd;
}

/**
 * \brief Function to send packet to the to the broker socket.
 * \param conn Pointer to the croker_conn struct.
 * \param pkt Pointer to the packet to be sent.
 */
int send_packet(struct broker_conn *conn, struct raw_pkt *pkt) {
  int n = write(conn->sockfd,pkt->buf, pkt->len); //strlen(pkt->buf));
  if (n < 0) 
    error("ERROR writing to socket");
  return n;
}

/**
 * \brief Function to recieve packetfrom the broker socket.
 * \param conn Pointer to the croker_conn struct.
 * \param pkt Pointer to the reciever buffer/packet.
 */
int read_packet(struct broker_conn *conn, struct raw_pkt *pkt) {
  int n = read(conn->sockfd, pkt->buf, sizeof(pkt->buf) - 1);
    //write(conn-sockfd,pkt->buf, pkt->len); //strlen(pkt->buf));
  if (n < 0) 
    error("ERROR reading socket");
  return n;
}