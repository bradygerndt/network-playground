/**
 * @file bufpool.h
 * @provides isbadpool roundword.
 *
 */
/* Embedded Xinu, Copyright (C) 2008.  All rights reserved. */

#ifndef _BUFPOOL_H_
#define _BUFPOOL_H_

#include <kernel.h>
#include <semaphore.h>

#define NPOOL  8
#define POOL_MAX_BUFSIZE  2048
#define POOL_MIN_BUFSIZE  8
#define POOL_MAX_NBUFS    8192

/* Buffer pool state definitions */
#define BFPFREE  1
#define BFPUSED  2

/**
 * Individual pool buffer
 */
struct poolbuf
{
    struct poolbuf *next;
    int poolid;
};

/**
 * Buffer pool table entry
 */
struct bfpentry
{
    uchar state;
    ulong bufsize;
    ulong nbuf;
    void *head;
    struct poolbuf *next;
    semaphore freebuf;
};

/**
 * isbadpool - check validity of reqested buffer pool id and state
 * @param p id number to test
 */
#define isbadpool(p) ((p >= NPOOL)||(p < 0)||(BFPFREE == bfptab[p].state))

/** roundword - round byte sized request to word size
 *  @param b size in bytes
 */
#define roundword(b) ((3 + b) & ~0x03)

extern struct bfpentry bfptab[];

/* function prototypes */
void *bufget(int);
syscall buffree(void *);
int bfpalloc(ulong, ulong);
syscall bfpfree(int);

#endif                          /* _BUFPOOL_H_ */
