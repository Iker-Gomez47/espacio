#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>

// Variables globales para que el manejador pueda destruirlas
int shm_id;
int *array;

void manejador(int sig) {
    (void)sig;
    shmdt(array);
    shmctl(shm_id, IPC_RMID, NULL);
    printf("\nMemoria compartida liberada con éxito.\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <proj_id> <n>\n", argv[0]);
        exit(1);
    }

    signal(SIGINT, manejador);

    int proj_id = atoi(argv[1]);
    int n = atoi(argv[2]);

    key_t clave = ftok("/etc", proj_id);
    shm_id = shmget(clave, n * sizeof(int), 0600 | IPC_CREAT);
    if (shm_id == -1) {
        perror("Error en shmget");
        exit(1);
    }

    array = (int *) shmat(shm_id, NULL, 0);
    if (array == (void *) -1) {
        perror("Error en shmat");
        exit(1);
    }




    while (true){
        int suma = 0;
        for (int i = 0; i < n; i++) {
            suma += array[i];
        }
        printf("Suma: %d\n", suma);
        sleep(5);
    }

    return 0;
}
