#include <xinu.h>

syscall ipRecv(struct ethergram *pkt)
{
  struct ipgram *ip = NULL;
  // int mem, i, op;
  ip = (struct ipgram *)pkt->data;

  uchar dIP[IP_ADDR_LEN];
  memcpy(dIP, &ip->src, IP_ADDR_LEN);

  ip = (struct ipgram *)pkt->data;

  if(1 == ip->proto)
  {
    fprintf(CONSOLE, "%s\n", "We got ourselves a ping!");
    icmpRecv(dIP);
  }


}
