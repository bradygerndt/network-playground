#include <xinu.h>

int arpAlloc(uchar ipaddr[IP_ADDR_LEN], uchar mac[ETH_ADDR_LEN])
{
  int i;
  wait(sem);
  for (i = 0; i < ARP_NUM_ENTRY; i++)
  {
    if(ARP_FREE == arptab[i].state)
    {
      arptab[i].state = ARP_USED;
      memcpy(&arptab[i].praddr, ipaddr, IP_ADDR_LEN);
      memcpy(&arptab[i].hwaddr, mac, ETH_ADDR_LEN);
      arptab[i].expires = clocktime + 1800;
      fprintf(CONSOLE, "Added ip to space %d\n", i);
      signal(sem);

      return TRUE;
      }

  }
  //No free spots in arp entry
  signal(sem);
  return FALSE;
}
