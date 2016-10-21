#include <xinu.h>

syscall arpRecv(struct ethergram *pkt)
{
  struct arpgram *arp = NULL;
  ushort type;
  uchar *sIp, *dIp, *sHwa;
  int mem, i;


  dIp = (uchar *) malloc(IP_ADDR_LEN);
  sIp = (uchar *) malloc(IP_ADDR_LEN);
  sHwa = (uchar *) malloc(ETH_ADDR_LEN);

  dot2ip(nvramGet("lan_ipaddr\0"), sIp);
  arp = (struct arpgram *)pkt->data;
  memcpy(dIp, &arp->addr[ARP_ADDR_DPA], IP_ADDR_LEN);
  mem = memcmp(sIp, dIp, IP_ADDR_LEN);


  fprintf(CONSOLE, "Hardware type --> %d\n", ntohs(arp->hwtype));
  fprintf(CONSOLE, "Protocol type --> %04x\n", ntohs(arp->prtype));
  fprintf(CONSOLE, "Hardware length --> %d\n", arp->hwalen);
  fprintf(CONSOLE, "Protocol length --> %d\n", arp->pralen);
  fprintf(CONSOLE, "Op --> %04x\n", ntohs(arp->op));
  fprintf(CONSOLE, "Source MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", arp->addr[0], arp->addr[1],arp->addr[2], arp->addr[3], arp->addr[4], arp->addr[5], arp->addr[ETH_ADDR_LEN]);
  fprintf(CONSOLE, "Source IP --> %d.%d.%d.%d\n", arp->addr[ARP_ADDR_SPA], arp->addr[7], arp->addr[8], arp->addr[9]);
  fprintf(CONSOLE, "Destination MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", arp->addr[ARP_ADDR_DHA], arp->addr[11], arp->addr[12], arp->addr[13], arp->addr[14], arp->addr[15]);
  fprintf(CONSOLE, "Destination IP --> %d.%d.%d.%d\n", arp->addr[ARP_ADDR_DPA], arp->addr[17], arp->addr[18], arp->addr[19]);
  fprintf(CONSOLE, "my IP address is %d.%d.%d.%d\n", sIp[0], sIp[1], sIp[2], sIp[3]);


  if(0 == mem)
  {

    //fprintf(CONSOLE, "I is %d\n", i);
    //fprintf(CONSOLE, "%s\n", "This packet is for me!");
    if(ARP_REPLY == arp->op)
    {
      wait(sem);

      for (i = 0; i < ARP_NUM_ENTRY; i++)
      {
        if(arptab[i].state == ARP_FREE)
        {
          arptab[i].state == ARP_USED;
          memcpy(&arptab[i].hwaddr, &arp->addr[ARP_ADDR_SHA], ETH_ADDR_LEN);
          memcpy(&arptab[i].praddr, &arp->addr[ARP_ADDR_SPA], IP_ADDR_LEN);
          signal(sem);
          break;
        }
      }
    }
    else
    {
      fprintf(CONSOLE, "%s\n", "Replying");
      arpReply(pkt);
    }


  }



  fprintf(CONSOLE, "\n\n");

  free(sIp);
  free(dIp);



}
