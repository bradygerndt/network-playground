/**
 * @file     xsh_ping.c
 * @provides xsh_ping
 *
 */
/* Embedded XINU, Copyright (C) 2009.  All rights reserved. */

#include <xinu.h>

/**
 * Shell command (ping) will send a ping request to specified IP.
 * @param nargs count of arguments in args
 * @param args array of arguments
 * @return OK for success, SYSERR for syntax error
 */
command xsh_ping(int nargs, char *args[])
{

  if(nargs < 2)
  {
    fprintf(CONSOLE, "%s\n", "Please specify a host.");
    return OK;
  }
  uchar dstIP[IP_ADDR_LEN];
  dot2ip(args[1], dstIP);
  icmpRequest(dstIP);

	return OK;
}
