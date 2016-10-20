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
	int i = 0;

	arpResolve();

	// Zero out the packet buffer.
	bzero(packet, PKTSZ);

	return OK;
}
