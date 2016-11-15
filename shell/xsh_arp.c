#include <xinu.h>

/**
 * Shell command arp is for displaying and manipulating the
 * arp table.
 * @param nargs count of arguments in args
 * @param args array of arguments
 * @return OK for success, SYSERR for syntax error
 */

command xsh_arp(int nargs, char *args[])
{
	uchar new[] = "-n";
	uchar delete[] = "-d";

	if( 2 > nargs)
	{
		int i;
	  wait(sem);
	  for (i = 0; i < ARP_NUM_ENTRY; i++)
	  {
	    if(ARP_USED == arptab[i].state)
	    {
				fprintf(CONSOLE, "%d.%d.%d.%d ", arptab[i].praddr[0], arptab[i].praddr[1], arptab[i].praddr[2], arptab[i].praddr[3]);
				fprintf(CONSOLE, "%s", "at ");
				fprintf(CONSOLE, "%02x:%02x:%02x:%02x:%02x:%02x\n", arptab[i].hwaddr[0], arptab[i].hwaddr[1], arptab[i].hwaddr[2], arptab[i].hwaddr[3], arptab[i].hwaddr[4], arptab[i].hwaddr[5]);
			}
		}
		signal(sem);

	}
	else
	{
		if(0 == (strcmp(args[1], &new)))
		{
			fprintf(CONSOLE, "%s\n", "New");
		}
		if(0 == (strcmp(args[1], &delete)))
		{
			fprintf(CONSOLE, "%s\n", "Delete");
		}
	}



/* If necessary, zero out all of the indexes that were used in
	args. They values are currently persistent*/
	int a;
	for(a = 0; a < nargs; a++)
	{
		bzero(args[a], sizeof(char));
	}
	return OK;
}
