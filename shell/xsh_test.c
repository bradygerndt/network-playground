/**
 * @file     xsh_test.c
 * @provides xsh_test
 *
 */
/* Embedded XINU, Copyright (C) 2009.  All rights reserved. */

#include <xinu.h>

/**
 * Shell command (test) is testing hook.
 * @param nargs count of arguments in args
 * @param args array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command xsh_test(int nargs, char *args[])
{
	uchar packet[PKTSZ];
	uchar *ppkt = packet;
	int i = 0;

	fprintf(CONSOLE, "%s\n", "Test works");

	// Zero out the packet buffer.
	bzero(packet, PKTSZ);

	return OK;
}
