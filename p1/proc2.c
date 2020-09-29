#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>

void proc (char c) { for(int i=5;0<i;i--) printf("%c", c); }

int main (void) {
  if(fork() == 0) {
    proc('A');
  } else if (fork() == 0) {
    proc('B');
  } else {
    proc('C');
  }
  return 0;
}
