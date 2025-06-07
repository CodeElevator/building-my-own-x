#include <stdio.h>
#include <stdint.h>

typedef struct {
  float x;
  float y;
} nice;

int condition() {
  nice a;
  a.x = 10.0;
  a.y = 15.0;
  if ( a.x == 10 ) {
    puts("a is equal to 10");
  } else {
    printf("%f\n", a.y);
  }
  return 0;
}

int hello(int n) {
  int s = 0;
  while (s < n) {
    puts("Heya!");
    s = s + 1;
  };
  return 0;
}

int main () {
  int i = 0;
  condition();
  while (i < 5) {
    puts("hello, world!");
    i = i + 1;
  };
  for (int d = 0; d < 5; d++) {
    printf("this has been printed %d times\n", d);
  };
  hello(5);
}
