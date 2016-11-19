#include <xinu.h>

void arpPrintPkt(struct ethergram *pkt)
{

  struct arpgram *arp = NULL;
  arp = (struct arpgram *) pkt->data;

/*print in human*/
  fprintf(CONSOLE, "\n%s\n", "------Ethergram Packet------");
  fprintf(CONSOLE, "Ether Destination MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", pkt->dst[0], pkt->dst[1],pkt->dst[2], pkt->dst[3], pkt->dst[4], pkt->dst[5], pkt->dst[ETH_ADDR_LEN]);
  fprintf(CONSOLE, "Ether Source MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", pkt->src[0], pkt->src[1],pkt->src[2], pkt->src[3], pkt->src[4], pkt->src[5], pkt->src[ETH_ADDR_LEN]);
  fprintf(CONSOLE, "ETYPE = %d\n", ntohs(pkt->type));
  fprintf(CONSOLE, "Hardware type --> %d\n", arp->hwtype);
  fprintf(CONSOLE, "Protocol type --> %04x\n", arp->prtype);
  fprintf(CONSOLE, "Hardware length --> %d\n", arp->hwalen);
  fprintf(CONSOLE, "Protocol length --> %d\n", arp->pralen);
  fprintf(CONSOLE, "Op --> %04x\n", arp->op);
  fprintf(CONSOLE, "Source MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", arp->addr[0], arp->addr[1],arp->addr[2], arp->addr[3], arp->addr[4], arp->addr[5], arp->addr[ETH_ADDR_LEN]);
  fprintf(CONSOLE, "Source IP --> %d.%d.%d.%d\n", arp->addr[ARP_ADDR_SPA], arp->addr[7], arp->addr[8], arp->addr[9]);
  fprintf(CONSOLE, "Destination MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", arp->addr[ARP_ADDR_DHA], arp->addr[11], arp->addr[12], arp->addr[13], arp->addr[14], arp->addr[15]);
  fprintf(CONSOLE, "Destination IP --> %d.%d.%d.%d\n", arp->addr[ARP_ADDR_DPA], arp->addr[17], arp->addr[18], arp->addr[19]);

}
