#define _DEFAULT_SOURCE
#include <stdio.h>      // fopen, fgets, printf, perror, stdin
#include <stdlib.h>     // atoi, exit
#include <string.h>     // strlen, strncmp, strcpy, strcspn
#include <unistd.h>     // usleep
#include <sys/types.h>  // key_t
#include <sys/ipc.h>    // ftok
#include <sys/msg.h>    // msgget, msgsnd
#include "procsched.h"  // RUTA_CLAVE, ID_PROJ, peticion_t









int main(int argc, char *argv[]) {
    FILE *origen = stdin;

    if (argc == 2) {
        origen = fopen(argv[1], "r");
        if (origen == NULL) {
            perror("Error al abrir el fichero");
            exit(1);
        }
    }
    else if (argc > 2) {
        perror("No se admiten mas de 2 arguentos");
        exit(1);
    }

    key_t clave = ftok(RUTA_CLAVE, ID_PROJ);
    if(clave == -1){
        perror("error ftok");
        exit(1);

    }


    int cola_id = msgget(clave, 0);
    if(cola_id == -1){
        perror("error al conectarse a la cola");
    }


    char linea[MAX_COMANDO + 64];

    while (fgets(linea, sizeof(linea), origen) != NULL) {
        linea[strcspn(linea, "\r\n")] = '\0';

        if (linea[0] == '\0' || linea[0] == '#') {
            continue;
        }



        int prio;
        char resto[MAX_COMANDO];

        if (sscanf(linea, "%d %[^\n]", &prio, resto) < 2) {
            continue; // Formato no válido
        }

        if (prio == 0) {
            int ms = 0;
            if (sscanf(resto, "espera %d", &ms) == 1) {
                usleep(ms * 1000); // usleep recibe microsegundos
            }
            continue;
        }

        if (prio >= 1 && prio <= 4) {
            peticion_t pet;
            pet.mtype = prio;
            strncpy(pet.comando, resto, MAX_COMANDO - 1);
            pet.comando[MAX_COMANDO - 1] = '\0';

            if (msgsnd(cola_id, &pet, sizeof(peticion_t) - sizeof(long), 0) == -1) {
                perror("Error en msgsnd");
                break;
            }
        }



    }
    return 0;











}
