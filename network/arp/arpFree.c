#include <xinu.h>

syscall arpFree(uchar ipaddr[IP_ADDR_LEN])
{
  uchar ip[IP_ADDR_LEN];  //Holds formatted ip address
  dot2ip(ipaddr, ip);
  int i;
  wait(sem);
  for (i = 0; i < ARP_NUM_ENTRY; i++)
  {
    int mem = memcmp(ip, arptab[i].praddr, IP_ADDR_LEN);
    if(0 == mem)
    {
      fprintf(CONSOLE, "%s\n", "Found a match");
      arptab[i].state = ARP_FREE;
      signal(sem);
      return OK;
    }
  }
    signal(sem);
    return SYSERR;
}
