#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int foo(char *arg)
{
  char buf[60];
  strcpy(buf, arg);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      fprintf(stderr, "target1 takes exactly one argument\n");
      exit(EXIT_FAILURE);
    }
  foo(argv[1]);
  return 0;
}
