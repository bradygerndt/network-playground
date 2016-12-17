#include <xinu.h>

syscall ipwrite(uchar *payload, int length, int protocol, uchar dstIP[IP_ADDR_LEN])
{
  uchar srcIP[IP_ADDR_LEN];
  struct icmpgram *icmp = NULL;
  uchar dstMac[ETH_ADDR_LEN];

  icmp = (struct icmpgram *) malloc (sizeof(struct icmpgram));
  dot2ip(nvramGet("lan_ipaddr\0"), srcIP);

  arpResolve(dstIP, &dstMac);

  struct ipgram *ip;
  //Do we need to malloc this?

  ip = (struct ipgram *) malloc(sizeof(struct ipgram) + length);
  ip->ver_ihl = (char) (IPv4_VERSION << 4);
  ip->ver_ihl += (IPv4_MIN_IHL); //Fill in with version and header length
  ip->tos = IPv4_TOS_ROUTINE;
  ip->len = length + IPv4_HDR_LEN;//add header length
  ip->id = ntohs(0);
  ip->flags_froff =ntohs(0);
  ip->ttl = IPv4_TTL;
  ip->proto = protocol;
  ip->chksum = checksum(&ip, IPv4_HDR_LEN);
  memcpy(&ip->src, &srcIP, IP_ADDR_LEN);
  memcpy(&ip->dst, dstIP, IP_ADDR_LEN);
  memcpy(&ip->opts, payload, length);

  //Send down to netwrite
  netwrite(dstMac, ip);

  // fprintf(CONSOLE, "ver_ihl = %02x\n", ip->ver_ihl);
  // fprintf(CONSOLE, "tos = %d\n", ip->tos);
  // fprintf(CONSOLE, "len = %d\n", ip->len);
  // fprintf(CONSOLE, "id = %d\n", ip->id);
  // fprintf(CONSOLE, "flags_froff = %d\n", ip->flags_froff);
  // fprintf(CONSOLE, "TTL = %d\n", ip->ttl);
  // fprintf(CONSOLE, "Protocol = %d\n", ip->proto);
  // fprintf(CONSOLE, "chksum = %d\n", ip->chksum);
  // fprintf(CONSOLE, "Source IP = %d.%d.%d.%d\n", ip->src[0], ip->src[1], ip->src[2], ip->src[3]);
  // fprintf(CONSOLE, "Destination IP = %d.%d.%d.%d\n", ip->dst[0], ip->dst[1], ip->dst[2], ip->dst[3]);






}
