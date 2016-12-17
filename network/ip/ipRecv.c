#include <xinu.h>

syscall ipRecv(struct ethergram *pkt)
{
  struct ipgram *ip = NULL;
  int mem, i, op;

  ip = (struct ipgram *)pkt->data;
  fprintf(CONSOLE, "ver_ihl = %02x\n", ip->ver_ihl);
  fprintf(CONSOLE, "tos = %d\n", ip->tos);
  fprintf(CONSOLE, "len = %d\n", ip->len);
  fprintf(CONSOLE, "id = %d\n", ip->id);
  fprintf(CONSOLE, "flags_froff = %d\n", ip->flags_froff);
  fprintf(CONSOLE, "TTL = %d\n", ip->ttl);
  fprintf(CONSOLE, "Protocol = %d\n", ip->proto);
  fprintf(CONSOLE, "chksum = %d\n", ip->chksum);
  fprintf(CONSOLE, "Source IP = %d.%d.%d.%d\n", ip->src[0], ip->src[1], ip->src[2], ip->src[3]);
  fprintf(CONSOLE, "Destination IP = %d.%d.%d.%d\n", ip->dst[0], ip->dst[1], ip->dst[2], ip->dst[3]);



}
