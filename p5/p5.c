#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//--------------------------|
// gcc -o p5 p5.c -lpthread |
//--------------------------|



// numero lectores
int LEC_NUM = 10;
// numero escritores
int ESC_NUM = 5;

// veces que leen los lectores
int LEC_VECES = 10;
// veces que escriben los escritores
int ESC_VECES = 5;

pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t writer = PTHREAD_MUTEX_INITIALIZER;
int readers = 0;
// recurso
int libro = -1;

//sincronizacion
pthread_mutex_t start = PTHREAD_MUTEX_INITIALIZER;


void escritor_bloquear(void) {
  pthread_mutex_lock(&writer);
}
void escritor_desbloquear(void) {
  pthread_mutex_unlock(&writer);
}

void lector_bloquear(void) {
  pthread_mutex_lock(&mx);
  readers++;
  if (readers == 1) {
    pthread_mutex_lock(&writer);
  }
  pthread_mutex_unlock(&mx);
}
void lector_desbloquear(void) {
  pthread_mutex_lock(&mx);
  readers--;
  if (readers == 0) {
    pthread_mutex_unlock(&writer);
  }
  pthread_mutex_unlock(&mx);
}

void *lector(void *id) {
  //espera a la señal de comienzo
  pthread_mutex_lock(&start);
  pthread_mutex_unlock(&start);
  
  for(int i=0; i<LEC_VECES; i++) {
    lector_bloquear();
    printf("El lector %d ha leido un valor de %d\n", * (int*) id, libro);
    lector_desbloquear();
  }
  pthread_exit(id);
}

void *escritor(void *id) {
  //espera a la señal de comienzo
  pthread_mutex_lock(&start);
  pthread_mutex_unlock(&start);
  
  for (int i=0; i<LEC_VECES; i++) {
    escritor_bloquear();
    printf("El escritor %d ha actualizado el recurso\n", * (int*) id);
    libro = * (int*) id;
    escritor_desbloquear();
  }
  pthread_exit(id);
}

void crear_hilos(pthread_t hilos[], int id[], int tam, void *(*func) (void*)) {
  for(int h=0; h<tam; h++) {
    id[h] = h;
    int error = pthread_create(&hilos[h], NULL, func, &id[h]);
    if (error) {
      fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
      exit(-1);
    }
  }
}

void terminar_hilos(pthread_t hilos[], int tam, const char tipo[]) {
  int *salida;
  for(int h=0; h<tam; h++) {
    int error = pthread_join(hilos[h], (void **)&salida);
    if (error)
      fprintf(stderr, "Error: %d: %s\n", error, strerror(error));
    else
      printf("%s %d terminado\n", tipo, *salida);
  }
}

int main (void) {
  //adquiere la señal de comienzo
  pthread_mutex_lock(&start);
  
  pthread_t lectores[LEC_NUM];
  int lectores_id[LEC_NUM];
  
  pthread_t escritores[ESC_NUM];
  int escritores_id[ESC_NUM];
  
  crear_hilos(lectores, lectores_id, LEC_NUM, lector);
  crear_hilos(escritores, escritores_id, ESC_NUM, escritor);
  
  //libera la señal de comienzo
  pthread_mutex_unlock(&start);

  terminar_hilos(lectores, LEC_NUM, "Lector");
  terminar_hilos(escritores, ESC_NUM, "Escritor");
  
  pthread_mutex_destroy(&mx);
  pthread_mutex_destroy(&writer);
  pthread_mutex_destroy(&start);
  pthread_exit(NULL);
}
