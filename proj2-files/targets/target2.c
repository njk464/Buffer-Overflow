#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void nstrcpy(char *out, int outl, char *in)
{
  int i, len;

  len = strlen(in);
  if (len > outl)
    len = outl;

  for (i = 0; i <= len; i++)
    out[i] = in[i];
}

void bar(char *arg)
{
  char buf[80];

  nstrcpy(buf, sizeof buf, arg);
}

void foo(char *arg)
{
  bar(arg);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      fprintf(stderr, "target2 takes exactly one argument\n");
      exit(EXIT_FAILURE);
    }
  foo(argv[1]);
  return 0;
}
