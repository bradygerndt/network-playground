#include <xinu.h>




//Should probably check by MAC rather than IP.

int arpLookUp(uchar ipaddr[IP_ADDR_LEN])
{
  int i;
  wait(sem);
  for (i = 0; i < ARP_NUM_ENTRY; i++)
  {
    // fprintf(CONSOLE, "arp table has %d.%d.%d.%d\n", arptab[i].praddr[0], arptab[i].praddr[1], arptab[i].praddr[2], arptab[i].praddr[3]);
    // fprintf(CONSOLE, "Passed the function %d.%d.%d.%d\n", ipaddr[0], ipaddr[1],ipaddr[2], ipaddr[3]);
    // fprintf(CONSOLE, "Comparing %d.%d.%d.%d and %d.%d.%d.%d\n", ipaddr[0], ipaddr[1],ipaddr[2], ipaddr[3]);
    int mem = memcmp(ipaddr, arptab[i].praddr, IP_ADDR_LEN);
    if(0 == mem)
    {
      arptab[i].expires = clocktime + 1800;
      signal(sem);
      return TRUE;
    }
  }
    signal(sem);
    return FALSE;
}
