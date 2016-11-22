#include <xinu.h>

syscall ipwrite(uchar *payload, int length, int protocol)
{
  struct ipgram *ip;

  ip = (struct ipgram *) malloc(sizeof(struct ipgram) + length);
  ip->ver_ihl = //Fill in with version and header length
  ip->tos = IPv4_TOS_ROUTINE;
  ip->len = length + //add header length
  ip->id = //arbitrary;
  ip->flags_froff = 0;
  ip->ttl = IPv4_TTL;
  ip->proto =
  ip




}
