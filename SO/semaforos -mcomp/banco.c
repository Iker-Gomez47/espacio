#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>

volatile sig_atomic_t salida = 0;

void manejador(){
    salida = 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <proj_id> \n", argv[0]);
        exit(1);
    }
    signal(SIGINT, manejador);

    int proj_id = atoi(argv[1]);

    key_t clave = ftok("/etc", proj_id);
    int shm_id = shmget(clave, 3*sizeof(long), 0600 | IPC_CREAT);
    printf("Id de la mc: %d\n", shm_id);

    long *banco = (long*)shmat(shm_id, NULL, 0);

    for(int i = 0; i < 3; i++){

        banco[i] = 1000;
    }

    while(salida == 0){

        int suma = 0;
        for(int i = 0; i < 3; i++){

            suma += banco[i];
        }
        printf("Suma: %d\n", suma);
        sleep(1);
    }

    shmdt(banco);
    shmctl(shm_id, IPC_RMID, NULL);
    printf("La memoria compartida fue liberada con exito\n");

    return 0;



}
