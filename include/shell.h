/**
 * @file shell.h
 *
 * $Id: shell.h 1740 2009-04-16 23:21:34Z akoehler $
 */
/* Embedded Xinu, Copyright (C) 2008.  All rights reserved. */

#ifndef _SHELL_H_
#define _SHELL_H_

#include <kernel.h>

/* Size contstants */
#define SHELL_BUFLEN  80        /**< length of general buffer           */
#define SHELL_MAXTOK  16        /**< maximum tokens per line            */
#define SHELL_CMDSTK  8192      /**< size of command proc. stack        */
#define SHELL_CMDPRIO 20        /**< command process priority           */

/* Message constants */
#define SHELL_BANNER  "\033[1;35m______________________________________\n    _    _  _____  ______   _     _ \n   \\ \\  / /(_____)|  ___ \\ | |   | |\n    \\ \\/ /    _   | |   | || |   | |\n     )  (    | |  | |   | || |   | |\n    / /\\ \\  _| |_ | |   | || |___| |\n   /_/  \\_\\(_____)|_|   |_| \\______|\n______________________________________\033[0;39m\n\n"
/** start message */
#define SHELL_START     "Welcome to the wonderful world of Xinu!\n"
#define SHELL_EXIT      "Shell closed.\n"  /**< exit message            */
#define SHELL_PROMPT    "xsh"            /**< prompt                  */
#define SHELL_SYNTAXERR "Syntax error.\n"  /**< syntax error            */
#define SHELL_CHILDERR  "Cannot create.\n" /**< command error           */

/**
 * Defines what an entry in the shell command table looks like.
 */
struct centry
{
    char *name;                 /**< name of command                    */
    bool builtin;               /**< built-in command?                  */
    command (*procedure) (int, char *[]);/**< procedure                */
};

/* Token parsing functions */
#define isEndOfLine(c)    ((c) == '\0' || (c) == '\r' || (c) == '\n')
#define isQuote(c)        ((c) == '"' || (c) == '\'')
#define isOtherSpecial(c) ((c) == '<' || (c) == '>' || (c) == '&')
#define isWhitespace(c)   ((c) == ' ' || (c) == '\t')

extern struct centry commandtab[];   /**< table of commands             */
extern ulong ncommand;               /**< number of commands in table   */

/* Function prototypes */
int shell(int);
short lexan(char *, ushort, char *, char *[]);

#endif                          /* _SHELL_H_ */
