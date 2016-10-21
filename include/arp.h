#ifndef _ARP_H_
#define _ARP_H_

#include <kernel.h>
#include <semaphore.h>



/*define the hardware types - only ethernet for our purposes*/
#define ARP_HW_ETHERNET 1
/*ARP protocol types*/
#define ARP_PROTOTYPE_IPv4 ETHER_TYPE_IPv4
/*ARP Operations - Request and reply*/
#define ARP_RQST 1
#define ARP_REPLY 2
/* define the ARP Header*/
#define ARP_HDR_LEN_CONST 8
/*Define the ARP Table*/
#define ARP_NUM_ENTRY 32
#define ARP_FREE 0
#define ARP_USED 1
/*ARP unresolved if USED and not RESOLVED*/
#define ARP_UNRESOLVED 1
/*ARP entry resolved if it is USED and RESOLVED*/
#define ARP_RESOLVED 3
#define ARP_NTHRWAIT 10
/*define ARP operations*/
#define ARP_OP_RQST 1
#define ARP_OP_REPLY 2
/*WILL ADD MORE AS NECESSARY*/

/*define the offsets for the addresses*/
#define ARP_ADDR_SHA 0
#define ARP_ADDR_SPA ETH_ADDR_LEN
#define ARP_ADDR_DHA ARP_ADDR_SPA + IP_ADDR_LEN
#define ARP_ADDR_DPA ARP_ADDR_DHA + ETH_ADDR_LEN

/*ARP packet*/

struct arpgram
{
//Need to add 20 any time we allocate for an ARP packet
  ushort hwtype;
  ushort prtype;
  uchar hwalen;
  uchar pralen;
  ushort op;
  uchar addr[];
                  /* source hardware address (SHA)
                  source proto address (SPA)
                    destination hardware address(DHA)
                    Destination protocol address(DPA)
                    skip to the spot in the array.
                    //uchar addrs[1]; */

};

/*Table entry*/

struct arpEntry
{
  ushort state;
  uchar hwaddr;
  uchar praddr;
  int expires;

};

/*ARP Table*/
extern struct arpEntry arptab[ARP_NUM_ENTRY];

/*semaphore*/
extern semaphore sem;

/*function prototypes for ARP*/
void arpDaemon(void);
void arpInit(void);
syscall arpRecv(struct ethergram *pkt);
syscall arpResolve(void); //(uchar *ipaddr, uchar *mac);
syscall arpReply(struct ethergram *pkt);

#endif
