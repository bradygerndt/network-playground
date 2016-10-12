/* Device table declarations */
#include <kernel.h>

#ifndef _DEVICE_H_
#define _DEVICE_H_

typedef struct dentry
{                               /* device table entry */
    int dvnum;
    char *dvname;
    devcall (*dvinit) (struct dentry *, ...);
    devcall (*dvopen) (struct dentry *, ...);
    devcall (*dvclose) (struct dentry *, ...);
    devcall (*dvread) (struct dentry *, ...);
    devcall (*dvwrite) (struct dentry *, ...);
    devcall (*dvgetc) (struct dentry *, ...);
    devcall (*dvputc) (struct dentry *, ...);
    devcall (*dvseek) (struct dentry *, ...);
    devcall (*dvcntl) (struct dentry *, ...);
    int dvcsr;
    int mask;
    void (*intr) (void);
    char *dvioblk;
    int dvminor;
} device;

extern struct dentry devtab[];  /* one entry per device */

/* Device name definitions */
#define CONSOLE     0           /* type tty      */
#define TTY0        0           /* type tty      */
#define TTY1        1           /* type tty      */
#define ETH0        2           /* type ether    */

/* Control block sizes */

#define	NTTY	 2
#define NDISK    0
#define NETHER   1

#define	NDEVS	(NTTY + NDISK + NETHER)

#define isbaddev(f)     ( (f)<0 || (f)>=NDEVS )

devcall close(int);
devcall control(int, int, int, int);
devcall getc(int);
devcall open(int, ...);
devcall putc(int, char);
devcall read(int, void *, int);
devcall seek(int, int);
devcall write(int, void *, int);

#endif                          /* _DEVICE_H_ */
