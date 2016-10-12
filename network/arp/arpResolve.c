#include <xinu.h>

syscall arpResolve(uchar *ipaddr, uchar *mac)
{
  struct arpgram *arp = NULL;
  struct ethergram *egram = NULL;
  uchar mac[ETH_ADDR_LEN];
  uchar ip[IP_ADDR_LEN];

  mac = control(ETH0, ETH_CTRL_GET_MAC, (ulong) mac, 0);
  ip = nvramGet("lan_ipaddr\0");









}
