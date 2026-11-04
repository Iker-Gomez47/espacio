#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/types.h>
#include <sys/sem.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <proj_id>\n", argv[0]);
        exit(1);
    }

    // Semilla única por proceso
    srand(time(NULL) ^ getpid());

    int proj_id = atoi(argv[1]);
    key_t clave = ftok("/etc", proj_id);

    int sem_id = semget(clave, 0, 0);
    int shm_id = shmget(clave, 0, 0);
    if (shm_id == -1) {
        perror("Error en shmget");
        exit(1);
    }
    semctl(sem_id, 0, SETVAL, 1);

    struct sembuf acquire = { .sem_num = 0, .sem_op = -1, .sem_flg = 0 };
    struct sembuf release = { .sem_num = 0, .sem_op =  1, .sem_flg = 0 };

    long *banco = (long *) shmat(shm_id, NULL, 0);
    if (banco == (void *) -1) {
        perror("Error en shmat");
        exit(1);
    }

    for (int i = 0; i < 100000; i++) {

        semop(sem_id, &acquire, 1);

        int origen  = rand() % 3; // Cuentas 0, 1 o 2
        int destino = rand() % 3;
        int cantidad = (rand() % 201) - 100; // Entre -100 y 100

        // Sección crítica desprotegida (condición de carrera)
        banco[origen]  -= cantidad;
        banco[destino] += cantidad;
        sleep(1);

        semop(sem_id, &release, 1);
    }

    shmdt(banco);
    return 0;
}
