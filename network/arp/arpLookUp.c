#include <xinu.h>




//Should probably check by MAC rather than IP.

int arpLookUp(uchar ipaddr[IP_ADDR_LEN])
{
  uchar mac;
  int i;
  wait(sem);
  for (i = 0; i < ARP_NUM_ENTRY; i++)
  {
    if(ipaddr == arptab[i].praddr)
    {
      mac = arptab[i].hwaddr;
      arptab[i].expires = clocktime + 1800;
      signal(sem);
      return TRUE;
      }
    else
    {
      return FALSE;
    }
    signal(sem);
  }
}
