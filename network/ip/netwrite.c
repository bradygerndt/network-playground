#include <xinu.h>

syscall netwrite(uchar mac[ETH_ADDR_LEN], struct ipgram *ip)
{
  int lenWritten;
  uchar srcMac[ETH_ADDR_LEN];
  struct ethergram *egram = NULL;
  egram = (struct ethergram *) malloc(PKTSZ);

  control(ETH0, ETH_CTRL_GET_MAC, (ulong) srcMac, 0);

  memcpy(&egram->dst, &mac, ETH_ADDR_LEN);
  memcpy(&egram->src, &srcMac, ETH_ADDR_LEN);
  egram->type = ETYPE_IPv4;
  memcpy(egram->data, ip, sizeof(ip));

  if((lenWritten = write(ETH0, egram, ETH_MTU)) == SYSERR)
  {
    fprintf(CONSOLE, "%s\n", "Packet failed to send");
    return SYSERR;
  }

  return OK;

}
