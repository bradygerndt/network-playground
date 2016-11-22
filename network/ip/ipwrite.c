#include <xinu.h>

syscall ipwrite(uchar *payload, int length, int protocol, uchar dstIp[IP_ADDR_LEN])
{
  uchar srcIp[IP_ADDR_LEN];

  dot2ip(nvramGet("lan_ipaddr\0"), srcIp);

  struct ipgram *ip;

  ip = (struct ipgram *) malloc(sizeof(struct ipgram) + length);
  ip->ver_ihl = (char) (IPv4_VERSION << 4);
  ip->ver_ihl += (IPv4_MIN_IHL); //Fill in with version and header length
  ip->tos = IPv4_TOS_ROUTINE;
  ip->len = length + IPv4_HDR_LEN;//add header length
  ip->id = 0;
  ip->flags_froff = 0;
  ip->ttl = IPv4_TTL;
  ip->proto = protocol;
  ip->chksum = checksum(&ip, IPv4_HDR_LEN);
  ip->src = srcIp;




}
