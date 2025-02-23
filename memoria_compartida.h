#ifndef MEMORIA_COMPARTIDA_H
#define MEMORIA_COMPARTIDA_H

#include <stdbool.h>

//Adjunta un bloque de memoria
//asociada con un nombre de archivo
//lo crea si no existe
char * adjuntar_bloque_memoria(char *nomarch, int tamanio);
bool des_adjuntar_bloque_memoria(char * bloque);
bool destruye_bloque_memoria(char *nomarch);

//Todos los programas comparten estos 3 valores
#define TAMANIO_BLOQUE 4096
#define NOMARCH_MEMCOMP "memcomp.c"
#define ERROR_RESULTADO_IPC (-1)

//Nombres de archivo para 2 semaforos
#define NOM_SEM_PROD "/productor"
#define NOM_SEM_CONS "/consumidor"

#endif

