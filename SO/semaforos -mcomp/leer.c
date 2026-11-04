#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <proj_id> <n>\n", argv[0]);
        exit(1);
    }


    int proj_id = atoi(argv[1]);
    int pos = atoi(argv[2]);

    key_t clave = ftok("/etc", proj_id);
    int shm_id = shmget(clave, 0, 0);

    int *array = (int*)shmat(shm_id, NULL, 0);

    printf("%d \n", array[pos]);

    shmdt(array);
    return 0;

}
