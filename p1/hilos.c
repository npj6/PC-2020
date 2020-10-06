//usr/bin/gcc -o hilos $0 -lpthread && ./hilos && exit

//Autoejecutable :DDDD (si tienes gcc ahí....)

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_HILOS 3

typedef struct {
  int n;
  char c;
} input_t;

void *codigo_del_hilo (void *input) {
  int i;
  for (i=0; i<((input_t *)input)->n; i++) {
    printf("%c", ((input_t *)input)->c);
  }
  pthread_exit(NULL);
}

void error(int error) {
  if (error) {
    fprintf (stderr, "Error: %d: %s\n", error, strerror(error));
    exit(-1);
  }
}

int main() {
  int h;
  pthread_t hilos[NUM_HILOS];
  input_t inputs[NUM_HILOS];
  int *salida;
  
  inputs[0].n = 50; inputs[0].c = 'A';
  error(pthread_create(&hilos[0], NULL, codigo_del_hilo, &inputs[0]));

  inputs[1].n = 100; inputs[1].c = 'B';
  error(pthread_create(&hilos[1], NULL, codigo_del_hilo, &inputs[1]));

  inputs[2].n = 150; inputs[2].c = 'C';
  error(pthread_create(&hilos[2], NULL, codigo_del_hilo, &inputs[2]));


  for(h=0; h<NUM_HILOS; h++) {
    error(pthread_join(hilos[h], (void **)&salida));
  }

  return 0;
}
