#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "memoria_compartida.h"

int main(int argc, char *argv[]) {
    if (argc != 1) {
        printf("Forma de uso - %s [sin argumentos]", argv[0]);
        return -1;
    }

    if(destruye_bloque_memoria(NOMARCH_MEMCOMP)) {
        printf("Destruido el bloque: %s\n", NOMARCH_MEMCOMP);
    } else {
        printf("No pudo destruirse el bloque: %s\n", NOMARCH_MEMCOMP);
    }

    return 0;
}