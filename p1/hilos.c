//usr/bin/gcc -o hilos $0 -lpthread && ./hilos && exit

//Autoejecutable :DDDD (si tienes gcc ahí....)

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_HILOS 5

int I = 0;

void *codigo_del_hilo (void *id) {
  int i;
  for (i=0; i<50; i++) {
    printf("Hilo %d: i = %d\n", *(int *)id, I++);
  }
  pthread_exit(id);
}

int main() {
  int h;
  pthread_t hilos[NUM_HILOS];
  int id[NUM_HILOS] = {1, 2, 3, 4, 5};
  int error;
  int *salida;
  
  for(h=0; h<NUM_HILOS; h++) {
    error = pthread_create(&hilos[h], NULL, codigo_del_hilo, &id[h]);
    if (error) {
      fprintf (stderr, "Error: %d: %s\n", error, strerror(error));
      exit(-1);
    }
  }


  for(h=0; h<NUM_HILOS; h++) {
    error = pthread_join(hilos[h], (void **)&salida);
    if (error) {
      fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
    } else {
      printf("Hilo %d terminado\n", *salida);
    }
  }

}
