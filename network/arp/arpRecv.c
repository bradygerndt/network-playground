#include <xinu.h>

syscall arpRecv(struct ethergram *pkt)
{
  struct arpgram *arp = NULL;
  ushort type;
  uchar sIp[IP_ADDR_LEN], dIp[IP_ADDR_LEN], sMac[ETH_ADDR_LEN], rIp[IP_ADDR_LEN];
  int mem, i, op;



  dot2ip(nvramGet("lan_ipaddr\0"), sIp);
  arp = (struct arpgram *)pkt->data;
  memcpy(dIp, &arp->addr[ARP_ADDR_DPA], IP_ADDR_LEN);
  memcpy(rIp, &arp->addr[ARP_ADDR_SPA], IP_ADDR_LEN);
  memcpy(sMac, &arp->addr[ARP_ADDR_SHA], ETH_ADDR_LEN);
  mem = memcmp(sIp, dIp, IP_ADDR_LEN);
  op = ntohs(arp->op);



  fprintf(CONSOLE, "%s\n", "Recieving from:" );
  fprintf(CONSOLE, "Hardware type --> %d\n", arp->hwtype);
  fprintf(CONSOLE, "Protocol type --> %04x\n", arp->prtype);
  fprintf(CONSOLE, "Hardware length --> %d\n", arp->hwalen);
  fprintf(CONSOLE, "Protocol length --> %d\n", arp->pralen);
  // fprintf(CONSOLE, "Op --> %d\n", ntohs(arp->op));
  fprintf(CONSOLE, "Source MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", arp->addr[0], arp->addr[1],arp->addr[2], arp->addr[3], arp->addr[4], arp->addr[5], arp->addr[ETH_ADDR_LEN]);
  fprintf(CONSOLE, "Source IP --> %d.%d.%d.%d\n", arp->addr[ARP_ADDR_SPA], arp->addr[7], arp->addr[8], arp->addr[9]);
  fprintf(CONSOLE, "Destination MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", arp->addr[ARP_ADDR_DHA], arp->addr[11], arp->addr[12], arp->addr[13], arp->addr[14], arp->addr[15]);
  fprintf(CONSOLE, "Destination IP --> %d.%d.%d.%d\n", arp->addr[ARP_ADDR_DPA], arp->addr[17], arp->addr[18], arp->addr[19]);
  fprintf(CONSOLE, "my IP address is %d.%d.%d.%d\n", sIp[0], sIp[1], sIp[2], sIp[3]);
  fprintf(CONSOLE, "Ether Destination MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", pkt->dst[0], pkt->dst[1],pkt->dst[2], pkt->dst[3], pkt->dst[4], pkt->dst[5], pkt->dst[ETH_ADDR_LEN]);
  fprintf(CONSOLE, "Ether Dst as hex %x\n", pkt->dst);
  fprintf(CONSOLE, "Ether Source MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", pkt->src[0], pkt->src[1],pkt->src[2], pkt->src[3], pkt->src[4], pkt->src[5], pkt->src[ETH_ADDR_LEN]);
  fprintf(CONSOLE, "ETYPE = %d\n", ntohs(pkt->type));


  if(0 == mem)
  {

    // fprintf(CONSOLE, "%s\n", "This packet is for me!");
    if(ARP_RQST == op)
    {
      arpReply(pkt);
      int l = (arpLookUp(rIp));
      if(!arpLookUp(rIp))
      {
        arpAlloc(rIp, sMac);
      }
    }
    else if(ARP_REPLY == op)
    {
      fprintf(CONSOLE, "%s\n", "Receiving arp reply in arp recv");
      arpAlloc(rIp, sMac);
    }
  }


  fprintf(CONSOLE, "\n\n");

}
