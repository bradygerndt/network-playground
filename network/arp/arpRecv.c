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

/*enable this if you want to see the packets*/
  //arpPrintPkt(pkt);

  if(0 == mem)
  {
//reply to arp requests
    if(ARP_RQST == op)
    {
      arpReply(pkt);

      if(SYSERR == arpLookUp(rIp))
      {
        arpAlloc(rIp, sMac);
      }
    }
//Add replying ip to arp entry table
    else if(ARP_REPLY == op)
    {
      if(SYSERR == arpLookUp(rIp))
      {
        arpAlloc(rIp, sMac);
      }
    }
  }
}
