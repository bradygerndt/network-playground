#include <xinu.h>

syscall netwrite(uchar mac[ETH_ADDR_LEN], struct ipgram *ip)
{

  fprintf(CONSOLE, "Netwrite MAC --> %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1],mac[2], mac[3], mac[4], mac[5], mac[ETH_ADDR_LEN]);


}
