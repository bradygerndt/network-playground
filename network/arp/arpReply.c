#include <xinu.h>

syscall arpReply(struct ethergram *pkt)
{
  struct arpgram *arp;
  uchar *dIp, *buf;
  dIp = (uchar *) malloc(IP_ADDR_LEN);
  buf = (uchar *) malloc(PKTSZ);
  //arp = (struct arpgram *) malloc(sizeof(struct arpgram) + 20);

  if(NULL == pkt)
  {
    return SYSERR;
  }
  /*need to allocate memory for the arp packet!!!!!!*/
  arp = (struct arpgram *)pkt->data;
  //Hold the a spot for the source IP
  memcpy(dIp, &arp->addr[ARP_ADDR_DPA], IP_ADDR_LEN);

  /*build the ARP reply header*/
  arp->op = htons(ARP_OP_REPLY);
  /*set DHA*/
  memcpy(&arp->addr[ARP_ADDR_DHA], &arp->addr[ARP_ADDR_SPA], arp->hwalen);
  /*Set DPA*/
  memcpy(&arp->addr[ARP_ADDR_DPA], &arp->addr[ARP_ADDR_SPA], arp->pralen);
  /*Set SHA*/
  memcpy(&arp->addr[ARP_ADDR_SHA], &pkt->dst, arp->hwalen);
  /*Set SPA*/
  memcpy(&arp->addr[ARP_ADDR_SPA], dIp, arp->pralen);

  /*Set up ethergram*/
  memcpy(&pkt->src, &arp->addr[ARP_ADDR_SHA], ETH_ADDR_LEN);
  memcpy(&pkt->dst, &arp->addr[ARP_ADDR_DHA], ETH_ADDR_LEN);




  /*check packet contents*/
  //  fprintf(CONSOLE, "\n\n");
  //  fprintf(CONSOLE, "%s\n", "Sending Arp Reply");
  //  fprintf(CONSOLE, "Hardware type --> %d\n", htons(arp->hwtype));
  //  fprintf(CONSOLE, "Protocol type --> %04x\n", htons(arp->prtype));
  //  fprintf(CONSOLE, "Hardware length --> %d\n", arp->hwalen);
  //  fprintf(CONSOLE, "Protocol length --> %d\n", arp->pralen);
  //  fprintf(CONSOLE, "Op --> %04x\n", htons(arp->op));
  //  fprintf(CONSOLE, "Source MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", arp->addr[0], arp->addr[1],arp->addr[2], arp->addr[3], arp->addr[4], arp->addr[5], arp->addr[ETH_ADDR_LEN]);
  //  fprintf(CONSOLE, "Source IP --> %d.%d.%d.%d\n", arp->addr[ARP_ADDR_SPA], arp->addr[7], arp->addr[8], arp->addr[9]);
  //  fprintf(CONSOLE, "Destination MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", arp->addr[ARP_ADDR_DHA], arp->addr[11], arp->addr[12], arp->addr[13], arp->addr[14], arp->addr[15]);
  //  fprintf(CONSOLE, "Destination IP --> %d.%d.%d.%d\n", arp->addr[ARP_ADDR_DPA], arp->addr[17], arp->addr[18], arp->addr[19]);
  //  fprintf(CONSOLE, "Ether Destination MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", pkt->dst[0], pkt->dst[1],pkt->dst[2], pkt->dst[3], pkt->dst[4], pkt->dst[5], pkt->dst[ETH_ADDR_LEN]);
  //  fprintf(CONSOLE, "Ether Source MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", pkt->src[0], pkt->src[1],pkt->src[2], pkt->src[3], pkt->src[4], pkt->src[5], pkt->src[ETH_ADDR_LEN]);
  //
  // fprintf(CONSOLE, "\n\n");

  /*Set ARP to ethergram payload*/
  memcpy(&pkt->data, &arp, sizeof(arp));

  /*Copy ethergram to buf*/
  memcpy(buf, &pkt, PKTSZ);

  if((write(ETH0, buf, PKTSZ)) == SYSERR)
  {
    fprintf(CONSOLE, "%s\n", "Packet failed to send");
  }

  free(dIp);
  free(buf);
  //Check the memory address of the arp pointer.
  //Seems like I'm trying to free a null
  //free(arp);
  return OK;

}
