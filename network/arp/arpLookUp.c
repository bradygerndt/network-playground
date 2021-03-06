#include <xinu.h>




//Checks arp entries for existing ip address. Returns OK if exists.

syscall arpLookUp(uchar ipaddr[IP_ADDR_LEN])
{
  int i;
  wait(sem);
  for (i = 0; i < ARP_NUM_ENTRY; i++)
  {
    if(ARP_USED == arptab[i].state)
    {
      int mem = memcmp(ipaddr, arptab[i].praddr, IP_ADDR_LEN);
      if(0 == mem)
      {
        arptab[i].expires = clocktime + 1800;
        signal(sem);
        return i;
      }
    }
  }
    signal(sem);
    return SYSERR;
}
