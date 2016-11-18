#include <xinu.h>


void arpDaemon()
{
  int lenRecv;
  uchar *pkt = NULL;
  struct ethergram *egram = NULL;
  ushort type;
  //uchar data;

 // struct ethergram *ethgram = NULL;
  pkt = (uchar *) malloc(PKTSZ);
 //fprintf(CONSOLE, "%s\n", "we in");
 //fprintf(CONSOLE, "%x\n", pkt);
  while(1)
  {
    if((lenRecv = read(ETH0, pkt, PKTSZ)) == SYSERR)
    {
      fprintf(CONSOLE, "%s\n", "Failed to read from ETH");
    }
     if(lenRecv > 0)
     {
    	 //fprintf(CONSOLE, "%s\n", "Got something!");
       //might need to make this ethergram a pointer later
       egram = (struct ethergram *) malloc(PKTSZ);
       egram = (struct ethergram *) pkt;
       type = ntohs(egram->type);

       //data = (egram->data);

       if (type == ETYPE_ARP)
       {
        //fprintf(CONSOLE, "%s\n", "Got dat yung ARP packet");
        arpRecv(pkt);
        free(egram);
        //fprintf(CONSOLE, "%x\n", data);

       }




     }
  }
 }
