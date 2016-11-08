/**
 * @file     shell-commands.c
 * @provides commandtab
 *
 */
/* Embedded XINU, Copyright (C) 2009.  All rights reserved. */

#include <xinu.h>

/* Prototypes for shell commands defined in other files. */
command xsh_clear(int, char *[]);
command xsh_ethstat(int, char *[]);
command xsh_exit(int, char *[]);
command xsh_help(int, char *[]);
command xsh_kill(int, char *[]);
command xsh_memstat(int, char *[]);
command xsh_ps(int, char *[]);
command xsh_test(int, char *[]);
command xsh_arp(int, char *[]);

/* This structure describes commands available to the shell. */
struct centry commandtab[] = {
    {"clear", TRUE, xsh_clear},
    {"ethstat", FALSE, xsh_ethstat},
    {"exit", TRUE, xsh_exit},
    {"help", FALSE, xsh_help},
    {"kill", TRUE, xsh_kill},
    {"memstat", FALSE, xsh_memstat},
    {"ps", FALSE, xsh_ps},
    {"test", FALSE, xsh_test},
    {"arp", FALSE, xsh_arp},
    //add ping entry
    {"?", FALSE, xsh_help}

};

ulong ncommand = sizeof(commandtab) / sizeof(struct centry);
