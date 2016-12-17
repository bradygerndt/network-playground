#include <xinu.h>

syscall netwrite(uchar mac[ETH_ADDR_LEN], struct ipgram *ip)
{
  int sendSize;
  int lenWritten;
  uchar srcMac[ETH_ADDR_LEN];
  struct ethergram *egram = NULL;
  egram = (struct ethergram *) malloc(PKTSZ);

  sendSize = sizeof(struct ethergram) + ip->len;
  fprintf(CONSOLE, "Send size is %d\n", sendSize);
  control(ETH0, ETH_CTRL_GET_MAC, (ulong) srcMac, 0);

  memcpy(&egram->dst, mac, ETH_ADDR_LEN);
  memcpy(&egram->src, &srcMac, ETH_ADDR_LEN);
  egram->type = htons(ETYPE_IPv4);
  memcpy(egram->data, ip, sizeof(ip));

  fprintf(CONSOLE, "\n%s\n", "<------------Netwrite Eth Packet------------>");
  fprintf(CONSOLE, "Ether Destination MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", egram->dst[0], egram->dst[1],egram->dst[2], egram->dst[3], egram->dst[4], egram->dst[5], egram->dst[ETH_ADDR_LEN]);
  fprintf(CONSOLE, "Ether Source MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", egram->src[0], egram->src[1],egram->src[2], egram->src[3], egram->src[4], egram->src[5], egram->src[ETH_ADDR_LEN]);
  fprintf(CONSOLE, "ETYPE = %d\n", ntohs(egram->type));


  if((lenWritten = write(ETH0, egram, sendSize)) == SYSERR)
  {
    fprintf(CONSOLE, "%s\n", "Packet failed to send");
    return SYSERR;
  }
  fprintf(CONSOLE, "Length written: %d\n", lenWritten);

  return OK;

}
