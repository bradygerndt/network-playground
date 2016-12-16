#include <xinu.h>


syscall icmpRequest(uchar ip[IP_ADDR_LEN])
{
  struct icmpgram *icmpPkt = NULL;
  ushort chksum;

  //malloc all deez foolz
icmpPkt = (struct icmpPkt *) malloc(sizeof(struct icmpgram));

icmpPkt->type = ICMP_ECHO_RQST;
icmpPkt->code = 0;
icmpPkt->checksum = 0;

chksum = checksum(icmpPkt, sizeof(struct icmpgram));

icmpPkt->checksum = chksum;
//send to ip
ipwrite(icmpPkt, sizeof(struct icmpgram), IPv4_PROTO_ICMP, ip);

}
