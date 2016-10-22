#include <xinu.h>

syscall arpResolve (uchar *ipaddr, uchar *mac)
{
  struct arpgram *arp = NULL;
  struct ethergram *egram = NULL;
  uchar *sMac, *ip;
  int i;

  sMac = (uchar *) malloc(ETH_ADDR_LEN);
  ip = (uchar *) malloc(IP_ADDR_LEN);

  sMac = control(ETH0, ETH_CTRL_GET_MAC, (ulong) mac, 0);
  dot2ip(nvramGet("lan_ipaddr\0"), &ip);

  for (i = 0; i < ARP_NUM_ENTRY; i++)
  {
    if(ipaddr == arptab[i].praddr)
    {
      mac == arptab[i].hwaddr;
      arptab[i].expires = clocktime + 1800;
      return OK;
    }
  }


free(mac);
free(ip);

  return OK;
}
