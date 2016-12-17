#include <xinu.h>

void printICMP(struct icmpgram *icmp)
{
/*print in human*/
  fprintf(CONSOLE, "\n%s\n", "<---------------ICMP-------------->");
  fprintf(CONSOLE, "ICMP Type = %d\n", icmp->type);
  fprintf(CONSOLE, "Code = %d\n", icmp->code);
  fprintf(CONSOLE, "Checksum = %d\n", icmp->checksum);
  fprintf(CONSOLE, " = %d\n", icmp->checksum);
  fprintf(CONSOLE, "Checksum = %d\n", icmp->checksum);
  fprintf(CONSOLE, "%s\n\n","<---------------------------------->");
}
