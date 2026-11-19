#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include "procsched.h"

volatile sig_atomic_t salida = 0;

void manejador(int sig) {
    (void)sig;
    salida = 1;
}

int main(void) {
    signal(SIGINT, manejador);

    key_t clave = ftok(RUTA_CLAVE, ID_PROJ);
    if (clave == -1) {
        perror("Error en ftok");
        exit(1);
    }

    int cola_id = msgget(clave, 0600 | IPC_CREAT);
    if (cola_id == -1) {
        perror("Error en msgget");
        exit(1);
    }

    printf("Planificador esperando peticiones... (Ctrl+C para salir)\n");

    while (salida == 0) {
        peticion_t pet;

        int leidos = msgrcv(cola_id, &pet, sizeof(peticion_t) - sizeof(long), -4, 0);

        if (leidos == -1) {
            if (errno == EINTR) {
                // Interrumpido por SIGINT (Ctrl+C); el bucle evaluará salida == 1 y terminará
                continue;
            }
            perror("Error en msgrcv");
            break;
        }

        printf("Petición recibida -> Tipo/Prioridad: %ld, Comando: %s\n", pet.mtype, pet.comando);
    }

    msgctl(cola_id, IPC_RMID, NULL);
    printf("\nCola destruida y programa finalizado.\n");
    return 0;
}
