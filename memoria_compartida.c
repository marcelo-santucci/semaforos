#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "memoria_compartida.h"

#define ERROR_RESULTADO_IPC (-1)

static int obtiene_bloque_compartido(char *nomarch, int tamanio) {
    key_t key;

    // Solicitar una llave
    // Esta llave eseta relacionada con el nombre del archivo
    key = ftok(nomarch, 0);
    if(key == ERROR_RESULTADO_IPC) {
        return ERROR_RESULTADO_IPC;
    }

    //Obtener el bloque compartido, creandolo si no existe
    return shmget(key, tamanio, 0644 | IPC_CREAT);
}

char * adjuntar_bloque_memoria(char *nomarch, int tamanio) {
    int shared_block_id = obtiene_bloque_compartido(nomarch, tamanio);
    char *result;

    if(shared_block_id == ERROR_RESULTADO_IPC){
        return NULL;
    }

    // Mapear el blocke compartido a la memoria del proceso
    // y devolver un puntero hacia él
    result = shmat(shared_block_id, NULL, 0);
    if(result == (char *)ERROR_RESULTADO_IPC) {
        return NULL;
    }

    return result;
}

bool des_adjuntar_bloque_memoria(char *bloque) {
    return (shmdt(bloque) != ERROR_RESULTADO_IPC);
}

bool destruye_bloque_memoria (char *nomarch) {
    int shared_block_id = obtiene_bloque_compartido(nomarch, 0);

    if (shared_block_id == ERROR_RESULTADO_IPC) {
        return NULL;
    }

    return (shmctl(shared_block_id, IPC_RMID, NULL) != ERROR_RESULTADO_IPC);
}