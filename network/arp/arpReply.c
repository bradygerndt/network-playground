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
  arp->op = htons(ARP_REPLY);
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

  /*Set ARP to ethergram payload*/
  memcpy(&pkt->data, &arp, sizeof(arp));
  /*Copy ethergram to buf*/
  memcpy(buf, &pkt, PKTSZ);
//PKTSZ is too big. I think it's MTU + then some.
  if((write(ETH0, buf, 60)) == SYSERR)
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
