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
#include <sys/wait.h>
#include <time.h>
#include "cola.h"
#include"ventana.h"

void crearHijo(peticion_t pet, cola_t *cola_listos){

        printf("Petición recibida -> Tipo/Prioridad: %ld, Comando: %s\n", pet.mtype, pet.comando);

        int pid = fork();
        if(pid == -1){
            perror("error al crear el hijo\n");
            exit(-1);
        }
        else if(pid == 0){
            signal(SIGCONT, manejador_vacio);
            pause();

            // Trocear "pet.comando" en palabras (ej. "./arkanoid 0 0" -> {"./arkanoid", "0", "0", NULL})
            char copia_cmd[MAX_COMANDO];
            strncpy(copia_cmd, pet.comando, MAX_COMANDO - 1);
            copia_cmd[MAX_COMANDO - 1] = '\0';

            char *args[64];
            int i = 0;
            char *token = strtok(copia_cmd, " \t");
            while (token != NULL && i < 63) {
            args[i++] = token;
            token = strtok(NULL, " \t");
            }
            args[i] = NULL; // Obligatorio: marca el final del array para execvp

            // Sustituir este proceso hijo por el programa pedido
            if (args[0] != NULL) {
                execvp(args[0], args);
            }

            // Solo llega aquí si execvp falla (por ejemplo, el programa no existe)
            perror("Error en execvp");
            exit(127);



        }
        proceso_t proceso;
        proceso.pid = pid;
        proceso.prioridad = (int)pet.mtype;
        strncpy(proceso.comando, pet.comando, MAX_COMANDO - 1);
        proceso.comando[MAX_COMANDO - 1] = '\0';
        proceso.ultimo_ms = ahora_ms();

        cola_encolar(&cola_listos, proceso);

        if (proceso.prioridad == 1) {
            printf("URGENTE pid %d (%d) %s\n", proceso.pid, proceso.prioridad, proceso.comando);
        }
        else {
            printf("NUEVO   pid %d (%d) %s\n", proceso.pid, proceso.prioridad, proceso.comando);
        }
}



volatile sig_atomic_t salida = 0;

void manejador(int sig) {
    (void)sig;
    salida = 1;
}

void manejador_vacio(){

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
    cola_t cola_listos;
    cola_iniciar(&cola_listos);

    while (salida == 0) {
        peticion_t pet;
        int leidos;

        while(salida == 0 && esColaVacia(cola_listos)){

            leidos = msgrcv(cola_id, &pet, sizeof(peticion_t) - sizeof(long), -4, 0);
            if (leidos == -1) {
                if (errno == EINTR) {
                    // Interrumpido por SIGINT (Ctrl+C); el bucle evaluará salida == 1 y terminará
                    continue;
                }
                perror("Error en msgrcv");
                break;
            }
            else{
                crearHijo(&pet);

            }

        }



        printf("Petición recibida -> Tipo/Prioridad: %ld, Comando: %s\n", pet.mtype, pet.comando);

        int pid = fork();
        if(pid == -1){
            perror("error al crear el hijo\n");
            exit(-1);
        }
        else if(pid == 0){
            signal(SIGCONT, manejador_vacio);
            pause();

            // Trocear "pet.comando" en palabras (ej. "./arkanoid 0 0" -> {"./arkanoid", "0", "0", NULL})
            char copia_cmd[MAX_COMANDO];
            strncpy(copia_cmd, pet.comando, MAX_COMANDO - 1);
            copia_cmd[MAX_COMANDO - 1] = '\0';

            char *args[64];
            int i = 0;
            char *token = strtok(copia_cmd, " \t");
            while (token != NULL && i < 63) {
            args[i++] = token;
            token = strtok(NULL, " \t");
            }
            args[i] = NULL; // Obligatorio: marca el final del array para execvp

            // Sustituir este proceso hijo por el programa pedido
            if (args[0] != NULL) {
                execvp(args[0], args);
            }

            // Solo llega aquí si execvp falla (por ejemplo, el programa no existe)
            perror("Error en execvp");
            exit(127);



        }
        proceso_t proceso;
        proceso.pid = pid;
        proceso.prioridad = (int)pet.mtype;
        strncpy(proceso.comando, pet.comando, MAX_COMANDO - 1);
        proceso.comando[MAX_COMANDO - 1] = '\0';
        proceso.ultimo_ms = ahora_ms();

        cola_encolar(&cola_listos, proceso);

        if (proceso.prioridad == 1) {
            printf("URGENTE pid %d (%d) %s\n", proceso.pid, proceso.prioridad, proceso.comando);
        }
        else {
            printf("NUEVO   pid %d (%d) %s\n", proceso.pid, proceso.prioridad, proceso.comando);
        }


    }

    msgctl(cola_id, IPC_RMID, NULL);
    printf("\nCola destruida y programa finalizado.\n");
    return 0;
}
