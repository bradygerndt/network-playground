#include <xinu.h>

syscall arpResolve (uchar *ipaddr, uchar *mac)
{
  struct arpgram *arpCast = NULL;
  struct ethergram *egram = NULL;
  uchar *buf = NULL;
  uchar sMac[ETH_ADDR_LEN], ip[IP_ADDR_LEN];
  int i, k, lenWritten;


  buf = (uchar *) malloc(PKTSZ);
  arpCast = (struct arpgram *) malloc(sizeof(struct arpgram) + 20);
  egram = (struct ethergram *) malloc(sizeof(struct ethergram) + sizeof(arpCast));

  control(ETH0, ETH_CTRL_GET_MAC, (ulong) sMac, 0);
  dot2ip(nvramGet("lan_ipaddr\0"), ip);

//See if it's already in the table
    wait(sem);
    for (i = 0; i < ARP_NUM_ENTRY; i++)
    {
      if(*ipaddr == arptab[i].praddr)
      {
        mac = arptab[i].hwaddr;
        arptab[i].expires = clocktime + 1800;
        signal(sem);
        return OK;
      }
    }
    signal(sem);
  //If it's not in the table, set up an ARP broadcast

  //Build the ARP broadcast message
    arpCast->hwtype = htons(ARP_HW_ETHERNET);
    arpCast->prtype = htons(ARP_PRTYPE_IPv4);
    arpCast->hwalen = ETH_ADDR_LEN;
    arpCast->pralen = IP_ADDR_LEN;
    arpCast->op = htons(ARP_RQST);
    memcpy(&arpCast->addr[ARP_ADDR_SHA], sMac, ETH_ADDR_LEN);
    memcpy(&arpCast->addr[ARP_ADDR_SPA], ip, IP_ADDR_LEN);
    memcpy(&arpCast->addr[ARP_ADDR_DPA], ipaddr, IP_ADDR_LEN);
    bzero(&arpCast->addr[ARP_ADDR_DHA], ETH_ADDR_LEN);
    //Set up eth packet
    memcpy(&egram->src, &arpCast->addr[ARP_ADDR_SHA], ETH_ADDR_LEN);
    //This may not be necessary. Let's give it a try
    //bzero(&egram->dst, ETH_ADDR_LEN);

    for(k = 0; k < ETH_ADDR_LEN; k++)
    {
      egram->dst[k] = 0XFF;
    }
    egram->type = htons(ETYPE_ARP);


    /*Set ARP to ethergram payload*/
    memcpy(&egram->data, arpCast, sizeof(struct arpgram) + 20);
    /*Copy ethergram to buf*/
    memcpy(buf, &egram, PKTSZ);


  if((lenWritten = write(ETH0, egram, 60)) == SYSERR)
  {
    fprintf(CONSOLE, "%s\n", "Packet failed to send");
    return SYSERR;
  }


  //Block with a time based while loop to set up for helper process.

// }

  free(arpCast);
  free(egram);
  free(buf);

  return OK;
}
