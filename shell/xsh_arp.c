#include <xinu.h>

/**
 * Shell command arp is for displaying and manipulating the
 * arp table.
 * @param nargs count of arguments in args
 * @param args array of arguments
 * @return OK for success, SYSERR for syntax error
 */

int isInit = 0;
command xsh_arp(int nargs, char *args[])
{
	uchar packet[PKTSZ];
	uchar *pkt = packet;

	int i;
  wait(sem);
  for (i = 0; i < ARP_NUM_ENTRY; i++)
  {
    if(ARP_USED == arptab[i].state)
    {
			fprintf(CONSOLE, "%d.%d.%d.%d ", arptab[i].praddr[0], arptab[i].praddr[1], arptab[i].praddr[2], arptab[i].praddr[3]);
			fprintf(CONSOLE, "%s", "at ");
			fprintf(CONSOLE, "%02x:%02x:%02x:%02x:%02x:%02x\n", arptab[i].hwaddr[0], arptab[i].hwaddr[1],
			arptab[i].hwaddr[2], arptab[i].hwaddr[3], arptab[i].hwaddr[4], arptab[i].hwaddr[5]);
		}
	}
	signal(sem);


	// Zero out the packet buffer.
	bzero(packet, PKTSZ);

	return OK;
}
