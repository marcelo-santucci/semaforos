#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/sem.h>
#include <semaphore.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

#include "memoria_compartida.h"

#define ITERACIONES 10

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Forma de uso - %s [lo que desea escribir]", argv[0]);
        return -1;
    }

    //Crear los emáforos
    sem_t *sem_prod = sem_open(NOM_SEM_PROD, 0);
    if(sem_prod == SEM_FAILED) {
        perror("/productor");
        exit(EXIT_FAILURE);
    }

    sem_t *sem_cons = sem_open(NOM_SEM_CONS, 0);
    if(sem_cons == SEM_FAILED) {
        perror("/consumidor");
        exit(EXIT_FAILURE);
    }

    //Intentar "conectar" con el bloque de memoria
    char *bloque = adjuntar_bloque_memoria(NOMARCH_MEMCOMP, TAMANIO_BLOQUE);
    if(bloque == NULL) {
        printf("Error: No se pudo obtener un bloque\n");
        return -1;
    }
  
    for (int i=0; i<ITERACIONES; i++) {
        sem_wait(sem_cons); //Esperando que el consumidor tenga un espacio disponible

        printf("Escribiendo: \"%s\"\n", argv[1]);
        strncpy(bloque, argv[1], TAMANIO_BLOQUE);

        sem_post(sem_prod); //Informar al lector que existe algo escrito en la memoria para que lea
    }

    sem_close(sem_cons);
    sem_close(sem_prod);
    des_adjuntar_bloque_memoria(bloque);

    return 0;
}
