/******************************************************************************
 * File: uMQTT_helper.c
 * Description: uMQTT helper fucntions - not necessarily required for general
                usage.
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
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "uMQTT_helper.h"
#include "../inc/log.h"

#define NO_TOPIC_STRING     "(No topic)"
#define NO_MESSAGE_STRING   "(No message)"
/**
 * \brief Function to return the name of a give type.
 * \param type The type string to return.
 */
char *get_type_string(ctrl_pkt_type type) {
  char *ret = 0;

  switch (type) {
    case RESERVED_0:
    case RESERVED_15:
      ret = RESERVED_STR;
      break;

    case CONNECT:
      ret = CONNECT_STR;
      break;

    case CONNACK:
      ret = CONNACK_STR;
      break;

    case PUBLISH:
      ret = PUBLISH_STR;
      break;

    case PUBACK:
      ret = PUBACK_STR;
      break;

    case PUBREC:
      ret = PUBREC_STR;
      break;

    case PUBREL:
      ret = PUBREL_STR;
      break;

    case PUBCOMP:
      ret = PUBCOMP_STR;
      break;

    case SUBSCRIBE:
      ret = SUBSCRIBE_STR;
      break;

    case SUBACK:
      ret = SUBACK_STR;
      break;

    case UNSUBSCRIBE:
      ret = UNSUBSCRIBE_STR;
      break;

    case UNSUBACK:
      ret = UNSUBACK_STR;
      break;

    case PINGREQ:
      ret = PINGREQ_STR;
      break;

    case PINGRESP:
      ret = PINGRESP_STR;
      break;

    case DISCONNECT:
      ret = DISCONNECT_STR;
      break;
  }

  return ret;
}

/**
 * \brief Function to return ctrl_pkt_type from a string.
 * \param type The type string.
 */
ctrl_pkt_type get_string_type(char *type) {
  char ret = 0;

  if (!strcmp(type, CONNECT_STR)) {
    ret = CONNECT;
  } else if (!strcmp(type, CONNACK_STR)) {
    ret = CONNACK;
  } else if (!strcmp(type, PUBLISH_STR)) {
    ret = PUBLISH;
  } else if (!strcmp(type, PUBACK_STR)) {
    ret = PUBACK;
  } else if (!strcmp(type, PUBREC_STR)) {
    ret = PUBREC;
  } else if (!strcmp(type, PUBREL_STR)) {
    ret = PUBREL;
  } else if (!strcmp(type, PUBCOMP_STR)) {
    ret = PUBCOMP;
  } else if (!strcmp(type, SUBSCRIBE_STR)) {
    ret = SUBSCRIBE;
  } else if (!strcmp(type, SUBACK_STR)) {
    ret = SUBACK;
  } else if (!strcmp(type, UNSUBSCRIBE_STR)) {
    ret = UNSUBSCRIBE;
  } else if (!strcmp(type, UNSUBACK_STR)) {
    ret = UNSUBACK;
  } else if (!strcmp(type, PINGREQ_STR)) {
    ret = PINGREQ;
  } else if (!strcmp(type, PINGRESP_STR)) {
    ret = PINGRESP;
  } else if (!strcmp(type, DISCONNECT_STR)) {
    ret = DISCONNECT;
  } else {
    ret = RESERVED_0;
  }

  return ret;
}

/**
 * \brief Function to return the protocol version string.
 * \param type The type string to return.
 */
char *get_proto_ver_string(proto_version ver) {
  char *ret = 0;

  switch (ver) {
    case V1:
      ret = V1_STR;
      break;
    case V2:
      ret = V2_STR;
      break;
    case V3_V3_1:
      ret = V3_V3_1_STR;
      break;
    case V3_1_1:
      ret = V3_1_1_STR;
      break;
  }
  return ret;
}

/**
 * \brief Function to return the connect return string.
 * \param type The connection ret string to return.
 */
char *get_connect_ret_string(connect_return state) {
  char *ret = 0;

  switch (state) {
    case CONN_ACCEPTED:
      ret = CONN_ACCEPTED_STR;
      break;
    case CONN_UNACCEPT_PROTO_VER:
      ret = CONN_UNACCEPT_PROTO_VER_STR;
      break;
    case CONN_REF_IDENTIFIER_REJ:
      ret = CONN_REF_IDENTIFIER_REJ_STR;
      break;
    case CONN_REF_SERVER_UNAVAIL:
      ret = CONN_REF_SERVER_UNAVAIL_STR;
      break;
    case CONN_REF_BAD_USER_PASS:
      ret = CONN_REF_BAD_USER_PASS_STR;
      break;
    case CONN_REF_NOT_AUTH:
      ret = CONN_REF_NOT_AUTH_STR;
      break;
    default:
      ret = CONN_STATE_RESERVED_STR;
      break;
  }
  return ret;
}

/**
 * \brief Function to return the SUBACK return string.
 * \param type The type string to return.
 */
char *get_suback_return_string(suback_return sret) {
  char *ret = 0;

  switch (sret) {
    case SUB_SUCCESS_MAX_QOS_0:
      ret = SUB_SUCCESS_MAX_QOS_0_STR;
      break;
    case SUB_SUCCESS_MAX_QOS_1:
      ret = SUB_SUCCESS_MAX_QOS_1_STR;
      break;
    case SUB_SUCCESS_MAX_QOS_2:
      ret = SUB_SUCCESS_MAX_QOS_2_STR;
      break;
    case SUB_FAILURE:
      ret = SUB_FAILURE_STR;
      break;
  }
  return ret;

}

/**
 * \brief Function to return the QoS string.
 * \param type The QoS string to return.
 */
char *get_qos_string(qos_t qos) {
  char *ret = 0;

  switch (qos) {
    case QOS_AT_MOST_ONCE:
      ret = QOS_AT_MOST_ONCE_STR;
      break;
    case QOS_AT_LEAST_ONCE:
      ret = QOS_AT_LEAST_ONCE_STR;
      break;
    case QOS_EXACTLY_ONCE:
      ret = QOS_EXACTLY_ONCE_STR;
      break;
    case QOS_RESERVED:
      ret = QOS_RESERVED_STR;
      break;
  }
  return ret;
}

/**
 * \brief Function to print memory in hex.
 * \param ptr The memory to start printing.
 * \param len The number of bytes to print.
 */
void print_memory_bytes_hex_debug(void *ptr, size_t len) {
  if (DEBUG)
  {
    size_t i;

    char buf[5 * len];
    buf[0] = '\0';

    char tbuf[10] = "\0";

    LOG_DEBUG("%zu bytes starting at address %p", len, &ptr);
    for (i = 0; i < len; i++) {
      sprintf(tbuf, "0x%02X ", ((uint8_t *)ptr)[i]);
      strcat(buf, tbuf);
    }
    LOG_DEBUG("%s", buf);
  }
  return;
}

/**
 * \brief Function to print a packet on LOG_DEBUG.
 * \param pkt Pointer to the packet to be printed
 */
void print_packet_hex_debug(struct mqtt_packet *pkt) {

  if (DEBUG) {
    LOG_DEBUG("%s Packet Type:", get_type_string(pkt->fixed->generic.type));

    LOG_DEBUG("Fixed header:");
    LOG_DEBUG("Length: %zu", pkt->fix_len);
    print_memory_bytes_hex_debug((void *)pkt->fixed, pkt->fix_len);

    if (pkt->var_len) {
      LOG_DEBUG("Variable header:");
      LOG_DEBUG("Length: %zu", pkt->var_len);
      /* print variable header with oversized packet guard */
      print_memory_bytes_hex_debug((void *)pkt->variable,
          (pkt->var_len >= pkt->len) ? pkt->len : pkt->var_len);
    } else {
      LOG_DEBUG("No Variable header.");
    }

    /* print payload with oversized packet guard */
    if (pkt->pay_len && ((pkt->pay_len + pkt->var_len) < pkt->len)) {
      LOG_DEBUG("Payload:");
      LOG_DEBUG("Length: %zu", pkt->pay_len);
      print_memory_bytes_hex_debug((void *)&pkt->payload->data, pkt->pay_len);
    } else {
      LOG_DEBUG("No Payload.");
    }
  }
  return;
}

/**
 * \brief Function to print a raw packet based on the pkt->len
 *          size on LOG_DEBUG.
 * \param pkt Pointer to the packet to be printed
 */
void print_packet_raw_debug(struct mqtt_packet *pkt) {

  if (DEBUG) {
    LOG_DEBUG("Raw packet:");
    print_memory_bytes_hex_debug((void *)pkt->raw.buf, pkt->len);
  }
  return;
}

/**
 * \brief Function to print a summary of a packet on lOG_INFO.
 * \param pkt Pointer to the packet to be printed
 */
void print_packet_detailed_info(struct mqtt_packet *pkt) {
  uint16_t len = 0;
  char buf[UTF8_ENC_STR_MAX_LEN];

  LOG_INFO("%s PACKET", get_type_string(pkt->fixed->generic.type));

  switch (pkt->fixed->generic.type) {
    case RESERVED_0:
    case RESERVED_15:
      break;

    case CONNECT:
      LOG_INFO("Protocol name: %c%c%c%c",
          pkt->variable->connect.proto_name[0],
          pkt->variable->connect.proto_name[1],
          pkt->variable->connect.proto_name[2],
          pkt->variable->connect.proto_name[3]);
      LOG_INFO("Protocol version: %s",
          get_proto_ver_string(pkt->variable->connect.proto_level));

      len = 0;
      len += decode_utf8_string((char *)buf,
            (struct utf8_enc_str *)(&pkt->payload->data + len));
      LOG_INFO("ClientId: %s", buf);
      /* add space for utf8 str len */
      len += sizeof(uint16_t);

      if (pkt->variable->connect.flags.user_flag) {
        LOG_INFO("Username flag set:");
        len += decode_utf8_string((char *)buf,
            (struct utf8_enc_str *)(&pkt->payload->data + len));
        LOG_INFO("Username: %s", buf);
        /* add space for utf8 str len */
        len += sizeof(uint16_t);
      }

      if (pkt->variable->connect.flags.pass_flag) {
        LOG_INFO("Password flag set:");
        len += decode_utf8_string((char *)buf,
            (struct utf8_enc_str *)(&pkt->payload->data + len));
        LOG_INFO("Password: %s", buf);
        /* add space for utf8 str len */
        len += sizeof(uint16_t);
      }

      if (pkt->variable->connect.flags.will_flag) {
        LOG_INFO("Will flag set:");
        LOG_INFO("  Will QoS:");
        LOG_INFO("    %d - %s",
            pkt->variable->connect.flags.will_qos,
            get_qos_string(pkt->variable->connect.flags.will_qos));

        /* get will topic and will message from payload  */
        len += decode_utf8_string((char *)buf,
            (struct utf8_enc_str *)(&pkt->payload->data + len));
        LOG_INFO("  Will Topic: %s",
            (buf[0] == '\0' ? NO_TOPIC_STRING : buf));
        /* add space for utf8 str len */
        len += sizeof(uint16_t);

        len += decode_utf8_string((char *)buf,
            (struct utf8_enc_str *)(&pkt->payload->data + len));
        LOG_INFO("  Will Message: %s",
            (buf[0] == '\0' ? NO_MESSAGE_STRING : buf));
        /* add space for utf8 str len */
        len += sizeof(uint16_t);

        if (pkt->variable->connect.flags.will_retain_flag) {
          LOG_INFO("  Will Retain flag set.");
        }
      }

      if (pkt->variable->connect.flags.clean_session_flag) {
        LOG_INFO("Clean Session flag set");
      }

      if (pkt->variable->connect.keep_alive) {
        LOG_INFO("Keep alive timer set to: %ds",
            pkt->variable->connect.keep_alive);
      } else {
        LOG_INFO("Keep alive timer off");
      }
      break;

    case CONNACK:
      if (pkt->variable->connack.session_present_flag) {
        LOG_INFO("Session present on broker");
      } else {
        LOG_INFO("No session present on broker");
      }
      LOG_INFO("CONNECT return: %s",
          get_connect_ret_string(pkt->variable->connack.connect_ret));
      break;

    case PUBLISH:
      LOG_INFO("Publish flags:");

      if (pkt->fixed->publish.dup) {
        LOG_INFO("  Duplicate packet");
      }

      LOG_INFO("  QoS: %d - %s", pkt->fixed->publish.qos,
          get_qos_string(pkt->fixed->publish.qos));

      if (pkt->fixed->publish.retain) {
        LOG_INFO("  Retain flag set");
      }
      if (pkt->fixed->publish.qos > QOS_AT_MOST_ONCE) {
        LOG_INFO("Packet Identifier: %d", get_packet_pkt_id(pkt));
      }

      len = (uint16_t)((pkt->variable->publish.topic.len_msb << 8)
          | (pkt->variable->publish.topic.len_lsb));
      strncpy(buf, &pkt->variable->publish.topic.utf8_str, len);
      buf[len] = '\0';
      LOG_INFO("Topic: %s",
          (buf[0] == '\0' ? NO_TOPIC_STRING : buf));

      LOG_INFO("Message:\n%.*s", pkt->pay_len, &pkt->payload->data);
      break;

    case PUBREL:
      if (pkt->fixed->generic.reserved != 0x2) {
        LOG_ERROR("Malformed fixed header - reserved nibble: %d",
            pkt->fixed->generic.reserved);
      }

    case PUBACK:
    case PUBREC:
    case PUBCOMP:
        LOG_INFO("Packet Identifier: %d", get_packet_pkt_id(pkt));
      break;

    case SUBSCRIBE:
        LOG_INFO("Packet Identifier: %d", get_packet_pkt_id(pkt));

      /* decode topics */
      len = 0;
      do {

        len += decode_utf8_string((char *)&buf,
            (struct utf8_enc_str *)(&pkt->payload->data + len));

        LOG_INFO("Topic: %s",
            (buf[0] == '\0' ? NO_TOPIC_STRING : buf));
        LOG_INFO("  (QoS: %s)",
            get_qos_string((qos_t )*(&pkt->payload->data + len +
                sizeof(uint16_t))));

        /* don't add encoded string and QoS len until QoS has been retieved */
        len += sizeof(uint16_t) + sizeof(uint8_t);
      } while (len < pkt->pay_len);

      if (pkt->fixed->generic.reserved != 0x2) {
        LOG_ERROR("Malformed fixed header - reserved nibble: %d",
            pkt->fixed->generic.reserved);
      }

      break;

    case SUBACK:
      LOG_INFO("Packet Identifier: %d", get_packet_pkt_id(pkt));

      /* print return codes */
      do {
        LOG_INFO("SUBACK return: %s",
            get_suback_return_string((suback_return)*(&pkt->payload->data
                + len++)));

      } while (len < pkt->pay_len);

      break;

    case UNSUBSCRIBE:
      LOG_INFO("Packet Identifier: %d", get_packet_pkt_id(pkt));

      len = 0;

      /* decode topics */
      do {
        len += decode_utf8_string((char *)&buf,
            (struct utf8_enc_str *)(&pkt->payload->data + len));
        len += sizeof(uint16_t);

        LOG_INFO("Topic: %s",
            (buf[0] == '\0' ? NO_TOPIC_STRING : buf));

      } while (len < pkt->pay_len);


      if (pkt->fixed->generic.reserved != 0x2) {
        LOG_ERROR("Malformed fixed header - reserved nibble: %d",
            pkt->fixed->generic.reserved);
      }

      break;

    case UNSUBACK:
      LOG_INFO("Packet Identifier: %d", get_packet_pkt_id(pkt));
      break;

    case PINGREQ:
    case PINGRESP:
    case DISCONNECT:
      break;
  }
  return;
}

/**
 * \brief Function to print a PUBLISH packet on LOG_INFO.
 * \param pkt Pointer to the publish packet to be printed
 */
void print_publish_packet_info(struct mqtt_packet *pkt) {

  if (pkt->fixed->generic.type == PUBLISH) {
    /* Print topic */
    uint16_t len = (uint16_t)((pkt->variable->publish.topic.len_msb << 8)
        | (pkt->variable->publish.topic.len_lsb));
    if (len) {
      LOG_INFO("PUBLISH Topic: %.*s",
          len, &pkt->variable->publish.topic.utf8_str);
    } else {
      LOG_INFO("PUBLISH Topic: %s", NO_TOPIC_STRING);
    }

    /* Print message */
    LOG_INFO("Message:\n%.*s", pkt->pay_len, &pkt->payload->data);
  }

  return;
}

/**
 * \brief Function to generate a unique string to be used
 *        as part of the default clientid.
 * \param str Buffer to store generated string.
 * \param len Length of the string to generate.
 */
void gen_unique_string(char *str, size_t len) {

  const char charset[] = UNIQUE_STR_CHARSET;
  size_t i;

  srand(time(NULL));
  if (len) {
    --len;
    for (i = 0; i < len; i++) {
      int key = rand() % (int) (sizeof(charset) - 1);
      str[i] = charset[key];
    }
    str[len] = '\0';
  }
}
