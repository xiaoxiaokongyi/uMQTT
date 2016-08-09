#!/bin/bash

DEBUG=$1

if [ $DEBUG ]
 then
  echo "Debug level set to $DEBUG"
  DEBUG="-v$DEBUG"
fi

echo "-------------------------------------------------------------------------"
echo "Help test ==============================================================="
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt --help $DEBUG
echo "-------------------------------------------------------------------------"
echo "INVALID packet type tests ==============================================="
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt RESERVED $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt somenonepackettype $DEBUG
echo "-------------------------------------------------------------------------"
echo "CONNECT packet type tests ==============================================="
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt CONNECT $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt CONNECT -c 'uMQTT-cli-test' -u 'someuser' \
    -P 'hahahahaha' -s -r -t "A test will topic" -q1 \
    -m"will I write a message?" -k 20 $DEBUG
echo "-------------------------------------------------------------------------"
echo "CONNACK packet type tests ==============================================="
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt CONNACK $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt CONNACK -p 23654 -r 2 -s $DEBUG
echo "-------------------------------------------------------------------------"
echo "PUBLISH packet type tests ==============================================="
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PUBLISH $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PUBLISH -t "" -m"" $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PUBLISH -t "A" \
    -m"This PUBLISH message should have no pkt_id since QoS = 0 [MQTT-3.3.2-2]" \
    $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PUBLISH -t "A/Test/Topic" -m"This is a nice message..." \
    -q1 $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PUBLISH -t "A/Test/Topic" -m"pkt_id should be 45341" \
    -q2 -r -p 45341 -d $DEBUG
echo "-------------------------------------------------------------------------"
echo "PUBACK packet type tests ================================================"
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PUBACK $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PUBACK -p73 $DEBUG
echo "-------------------------------------------------------------------------"
echo "PUBREC packet type tests ================================================"
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PUBREC $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PUBREC -p300 $DEBUG
echo "-------------------------------------------------------------------------"
echo "PUBREL packet type tests ================================================"
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PUBREL $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PUBREL -p6712 $DEBUG
echo "-------------------------------------------------------------------------"
echo "PUBCOMP packet type tests ==============================================="
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PUBCOMP $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PUBCOMP -p 32632 $DEBUG
echo "-------------------------------------------------------------------------"
echo "SUBSCRIBE packet type tests ============================================="
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt SUBSCRIBE $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt SUBSCRIBE -t "" -q1 -p 2564 $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt SUBSCRIBE -t "A" -q1 -p 2564 $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt SUBSCRIBE -t "A/test/topic" -q2 \
    -t"pkt_id should be 2564" -q2 -p 2564 $DEBUG
echo "-------------------------------------------------------------------------"
echo "SUBACK packet type tests ================================================"
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt SUBACK -p 3421 $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt SUBACK -r1 -p3 $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt SUBACK -r2 -p3152 $DEBUG
echo "-------------------------------------------------------------------------"
echo "UNSUBSCRIBE packet type tests ==========================================="
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt UNSUBSCRIBE $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt UNSUBSCRIBE -t "A" -p 2564 $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt UNSUBSCRIBE -t "A/test/topic" -t"Another/test/topic" \
    -t"Yet/another/test/topic" -p 2564 $DEBUG
echo "-------------------------------------------------------------------------"
echo "UNSUBACK packet type tests =============================================="
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt UNSUBACK -p 111 $DEBUG
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt UNSUBACK -p25153 $DEBUG
echo "-------------------------------------------------------------------------"
echo "PINGREQ packet type tests ==============================================="
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PINGREQ $DEBUG
echo "-------------------------------------------------------------------------"
echo "PINGRESP packet type tests =============================================="
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt PINGRESP $DEBUG
echo "-------------------------------------------------------------------------"
echo "DISCONNECT type tests ==================================================="
echo "-------------------------------------------------------------------------"
../../bin/uMQTT_gen_pkt DISCONNECT $DEBUG
echo "-------------------------------------------------------------------------"
echo "========================================================================="
