#include <xinu.h>

syscall arpResolve (uchar *ipaddr, uchar *mac)
{
  struct arpgram *arpCast = NULL;
  struct ethergram *egram = NULL;
  uchar *sMac, *ip, *buf;
  int i, j;

  sMac = (uchar *) malloc(ETH_ADDR_LEN);
  ip = (uchar *) malloc(IP_ADDR_LEN);
  buf = (uchar *) malloc(PKSTZ);
  arpCast = (struct arpgram *) malloc(sizeof(struct arpgram) + 20);
  egram = (struct ethergram *) malloc(sizeof(struct ethergram) + sizeof(arpCast));

  sMac = control(ETH0, ETH_CTRL_GET_MAC, (ulong) mac, 0);
  dot2ip(nvramGet("lan_ipaddr\0"), &ip);

for(j = 0; j < 3; j++)
{
  wait(sem);
  for (i = 0; i < ARP_NUM_ENTRY; i++)
  {
    if(ipaddr == arptab[i].praddr)
    {
      mac == arptab[i].hwaddr;
      arptab[i].expires = clocktime + 1800;
      signal(sem);
      return OK;
    }
    signal(sem);
  }
  arpCast->hwtype = ARP_HW_ETHERNET;
  arpCast->prtype = ARP_PRTYPE_IPv4;
  arpCast->hwalen = ETH_ADDR_LEN;
  arpCast->pralen = IP_ADDR_LEN;
  arpCast->op = htons(ARP_OP_RQST);
  memcpy(&arpCast->addr[ARP_ADDR_SHA], &sMac, ETH_ADDR_LEN);
  memcpy(&arpCast->addr[ARP_ADDR_SPA], &ip, IP_ADDR_LEN);
  memcpy(&arpCast->addr[ARP_ADDR_DHA], ARP_BROADCAST_ADDR, sizeof(ARP_BROADCAST_ADDR));
  memcpy(&arpCast->addr[ARP_ADDR_DPA], &ipaddr, IP_ADDR_LEN);
  //Set up eth packet
  memcpy(&egram->src, &arpCast->addr[ARP_ADDR_SHA], ETH_ADDR_LEN);
  memcpy(&egram->dst, &arpCast->addr[ARP_ADDR_DHA], ETH_ADDR_LEN);
  egram->type = ETYPE_ARP;
  /*Set ARP to ethergram payload*/
  memcpy(&egram->data, &arpCast, sizeof(arpCast));
  /*Copy ethergram to buf*/
  memcpy(buf, &egram, PKTSZ);


  if((write(ETH0, buf, PKTSZ)) == SYSERR)
  {
    fprintf(CONSOLE, "%s\n", "Packet failed to send");
  }
  //Block with a time based while loop

}




free(mac);
free(ip);
free(arpCast);
free(egram);
free(buf);

  return OK;
}
