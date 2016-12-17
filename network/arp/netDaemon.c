#include <xinu.h>


void arpDaemon()
{
  int lenRecv;
  uchar *pkt = NULL;
  struct ethergram *egram = NULL;
  ushort type;

  pkt = (uchar *) malloc(PKTSZ);

  while(1)
  {
    if((lenRecv = read(ETH0, pkt, PKTSZ)) == SYSERR)
    {
      fprintf(CONSOLE, "%s\n", "Failed to read from ETH");
    }
     if(lenRecv > 0)
     {
       egram = (struct ethergram *) malloc(PKTSZ);
       egram = (struct ethergram *) pkt;
       type = ntohs(egram->type);


    //Handle ARP ethernet packets
       if (type == ETYPE_ARP)
       {
        arpRecv(pkt);
        free(egram);
       }

       if (type == ETYPE_IPv4)
       {
         ipRecv(pkt);
       }
     }
  }
 }
