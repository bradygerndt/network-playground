#include <xinu.h>

syscall arpResolve ()//(uchar *ipaddr, uchar *mac)
{
  struct arpgram *arp = NULL;
  struct ethergram *egram = NULL;
  uchar *mac, *ip;

  mac = (uchar *) malloc(ETH_ADDR_LEN);
  ip = (uchar *) malloc(IP_ADDR_LEN);

  mac = control(ETH0, ETH_CTRL_GET_MAC, (ulong) mac, 0);
  ip = nvramGet("lan_ipaddr\0");

  fprintf(CONSOLE, "%s\n", "Calling the arp resolve yo!");
  fprintf(CONSOLE, "%s\n", ip);

  return OK;
}
