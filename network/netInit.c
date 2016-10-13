/**
 * @file netInit.c
 * @provides netInit.
 *
 */
/* Embedded Xinu, Copyright (C) 2008.  All rights reserved. */

#include <xinu.h>

/**
 * Initialize network interface.
 */


void netInit(void)
{
	int d;

	if((d = (open(ETH0))) == SYSERR)
  {
    fprintf(CONSOLE, "%s\n", "ETH0 failed to open");
  }
/*initialize ARP*/
  arpInit();
}
