#include <xinu.h>


syscall icmpRecv(uchar ip[IP_ADDR_LEN])
{
  struct icmpgram *icmpPkt = NULL;
  ushort chksum;

  //malloc all deez foolz
icmpPkt = (struct icmpPkt *) malloc(sizeof(struct icmpgram));

icmpPkt->type = ICMP_ECHO_REPLY;
icmpPkt->code = 0;
icmpPkt->checksum = 0;

chksum = checksum(icmpPkt, sizeof(struct icmpgram));

icmpPkt->checksum = chksum;
fprintf(CONSOLE, "%s\n", "Reply ICMP packet is ->");
printICMP(icmpPkt);

//send to ip
ipwrite(icmpPkt, sizeof(struct icmpgram), IPv4_PROTO_ICMP, ip);

}
