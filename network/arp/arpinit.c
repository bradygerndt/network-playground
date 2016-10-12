#include <xinu.h>

struct arpEntry arptab[ARP_NUM_ENTRY];
int arpDaemonId;

void arpInit(void)
{
  int i = 0;
  //fprintf(CONSOLE, "%s\n", "We're in arpInit");

  /*initialize the ARP table*/
  for (i = 0; i < ARP_NUM_ENTRY; i++)
  {
    bzero(&arptab[i], sizeof(struct arpEntry));
    arptab[i].state = ARP_FREE;
  }

  arpDaemonId = create((void *)arpDaemon, INITSTK, 3, "arpDaemon", 0);
  ready(arpDaemonId, 1);

}
