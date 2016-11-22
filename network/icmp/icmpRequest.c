#include <xinu.h>


syscall icmpRequest(uchar ip[IP_ADDR_LEN])
{
  struct ethergram *ethPkt;
  struct ipgram *ipPkt;
  struct icmpgram *icmpPkt;
  ushort chksum;

  //malloc all deez foolz
icmpPkt = (struct icmpPkt *) malloc(sizeof(struct icmpPkt));
ipPkt = (struct ipgram *) malloc(sizeof(struct ipgram) + sizeof(struct icmpPkt));
etherPkt = (struct ethergram *) malloc(sizeof(struct ethergram) + sizeof(struct ipgram) + sizeof(struct icmpPkt));

icmpPkt->type = ICMP_ECHO_RQST;
icmpPkt->code = 0;
icmpPkt->checksum = 0;

chksum = checksum(icmpPkt, sizeof(struct icmpgram));

icmpPkt->checksum = chksum;




}
