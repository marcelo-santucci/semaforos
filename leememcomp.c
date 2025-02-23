#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/sem.h>
#include <semaphore.h>

#include <fcntl.h>           /* Para usar las constantes O_* */
#include <sys/stat.h>        /* Para usar constantes adicionales */

#include "memoria_compartida.h"

#define NUM_ITERATIONS 10

int main(int argc, char *argv[])
{
    if (argc != 1) {
        printf("Forma de uso - %s //sin argumentos", argv[0]);
        return -1;
    }

    //Limpiar los semáforos en caso ya existan para evitar inconsistencias
    sem_unlink(NOM_SEM_CONS);
    sem_unlink(NOM_SEM_PROD);

    //Crear los Semáforos
    //Operación Crear Semáforo "O_CREAT"
    //Permisos (Especial[0])(Dueño[6])(Grupo[6])(Otros[0])
    //Valor 0 significa que esta en estado "Wait"
    sem_t *sem_prod = sem_open(NOM_SEM_PROD, O_CREAT, 0660, 0);   //Permiso
    if(sem_prod == SEM_FAILED) {
        perror("/productor");
        exit(EXIT_FAILURE);
    }

    //Valor 1 significa que se permite decrementar para pasar al estado wait()
    sem_t *sem_cons = sem_open(NOM_SEM_CONS, O_CREAT, 0660, 1);
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

    while (true) {
        sem_wait(sem_prod);

        if (strlen(bloque) > 0) {
            printf("Leyendo: \"%s\"\n", bloque);
            bool done = (strcmp(bloque, "quit")==0);
            bloque[0]=0;
            if(done) { break; }
        }

        sem_post(sem_cons);
    }

    //Limpieza de variables
    sem_close(sem_cons);
    sem_close(sem_prod);
    sem_unlink(NOM_SEM_CONS);
    sem_unlink(NOM_SEM_PROD);
    des_adjuntar_bloque_memoria(bloque);

    return 0;
}

