#include <xinu.h>

syscall arpResolve (uchar *ipaddr, uchar *mac)
{
  struct arpgram *arpCast = NULL;
  struct ethergram *egram = NULL;
  uchar *buf;
  uchar sMac[ETH_ADDR_LEN], ip[IP_ADDR_LEN];
  int i, j, k;


  buf = (uchar *) malloc(PKTSZ);
  arpCast = (struct arpgram *) malloc(sizeof(struct arpgram) + 20);
  egram = (struct ethergram *) malloc(sizeof(struct ethergram) + sizeof(arpCast));

  control(ETH0, ETH_CTRL_GET_MAC, (ulong) sMac, 0);
  dot2ip(nvramGet("lan_ipaddr\0"), ip);


  //
  // for(j = 0; j < 3; j++)
  // {
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
      signal(sem);
    }

    fprintf(CONSOLE, "%s\n", "Broadcasting");
    arpCast->hwtype = htons(ARP_HW_ETHERNET);
    arpCast->prtype = htons(ARP_PRTYPE_IPv4);
    arpCast->hwalen = ETH_ADDR_LEN;
    arpCast->pralen = IP_ADDR_LEN;
    arpCast->op = htons(ARP_OP_RQST);
    memcpy(&arpCast->addr[ARP_ADDR_SHA], sMac, ETH_ADDR_LEN);
    memcpy(&arpCast->addr[ARP_ADDR_SPA], ip, IP_ADDR_LEN);
    memcpy(&arpCast->addr[ARP_ADDR_DPA], ipaddr, IP_ADDR_LEN);
    bzero(&arpCast->addr[ARP_ADDR_DHA], ETH_ADDR_LEN);
    //Set up eth packet
    memcpy(&egram->src, &arpCast->addr[ARP_ADDR_SHA], ETH_ADDR_LEN);
    //memcpy(&egram->dst, &arpCast->addr[ARP_ADDR_DHA], ETH_ADDR_LEN);

    bzero(&egram->dst, ETH_ADDR_LEN);

    for(k = 0; k < ETH_ADDR_LEN; k++)
    {
      egram->dst[k] = 0XFF;
    }
    egram->type = htons(ETYPE_ARP);
    /*Set ARP to ethergram payload*/
    memcpy(&egram->data, &arpCast, sizeof(arpCast));
    /*Copy ethergram to buf*/
    memcpy(buf, &egram, PKTSZ);


    /*check packet contents*/
     fprintf(CONSOLE, "\n\n");
     fprintf(CONSOLE, "%s\n", "Sending arpCast");
     fprintf(CONSOLE, "Hardware type --> %d\n", arpCast->hwtype);
     fprintf(CONSOLE, "Protocol type --> %04x\n", arpCast->prtype);
     fprintf(CONSOLE, "Hardware length --> %d\n", arpCast->hwalen);
     fprintf(CONSOLE, "Protocol length --> %d\n", arpCast->pralen);
     fprintf(CONSOLE, "Op --> %04x\n", arpCast->op);
     fprintf(CONSOLE, "Source MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", arpCast->addr[0], arpCast->addr[1],arpCast->addr[2], arpCast->addr[3], arpCast->addr[4], arpCast->addr[5], arpCast->addr[ETH_ADDR_LEN]);
     fprintf(CONSOLE, "Source IP --> %d.%d.%d.%d\n", arpCast->addr[ARP_ADDR_SPA], arpCast->addr[7], arpCast->addr[8], arpCast->addr[9]);
     fprintf(CONSOLE, "Destination MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", arpCast->addr[ARP_ADDR_DHA], arpCast->addr[11], arpCast->addr[12], arpCast->addr[13], arpCast->addr[14], arpCast->addr[15]);
     fprintf(CONSOLE, "Destination IP --> %d.%d.%d.%d\n", arpCast->addr[ARP_ADDR_DPA], arpCast->addr[17], arpCast->addr[18], arpCast->addr[19]);
     fprintf(CONSOLE, "Ether Destination MAC --> %x:%x:%x:%x:%x:%x\n", egram->dst[0], egram->dst[1],egram->dst[2], egram->dst[3], egram->dst[4], egram->dst[5], egram->dst[ETH_ADDR_LEN]);
     fprintf(CONSOLE, "Ether Source MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", egram->src[0], egram->src[1],egram->src[2], egram->src[3], egram->src[4], egram->src[5], egram->src[ETH_ADDR_LEN]);


  if((write(ETH0, buf, PKTSZ)) == SYSERR)
  {
    fprintf(CONSOLE, "%s\n", "Packet failed to send");
  }
  else
  {
    fprintf(CONSOLE, "%s\n", "Sent ARP Request from Resolve");
  }
  //Block with a time based while loop

// }




  free(arpCast);
  free(egram);
  free(buf);

  return OK;
}
