#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
  int i = -2147483648;
  for (i; i < 0; i++){
    unsigned int x = i*sizeof(struct widget_t);
    if (x > 2799 && x <= 2800)
      printf("i=%d, overflow=%u\n", i, x);
  }
  return 0;
}
