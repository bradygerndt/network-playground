/**
 * @file     xsh_iptest.c
 * @provides xsh_iptest
 *
 */
/* Embedded XINU, Copyright (C) 2009.  All rights reserved. */

#include <xinu.h>

/**
 * Shell command (iptest) is testing hook.
 * @param nargs count of arguments in args
 * @param args array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command xsh_iptest(int nargs, char *args[])
{

if(nargs < 2)
{
  fprintf(CONSOLE, "%s\n", "Enter a command you big dummie..");
  return OK;
}

uchar payload[] = "Test";
uchar dstIP[IP_ADDR_LEN];
dot2ip(args[1], dstIP);
fprintf(CONSOLE, "You provided = %d.%d.%d.%d\n", dstIP[0], dstIP[1], dstIP[2], dstIP[3]);
ipwrite(&payload, 4, IPv4_PROTO_TCP, dstIP);

	return OK;
}
