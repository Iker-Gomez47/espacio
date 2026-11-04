#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <proj_id> <pos> <valor>\n", argv[0]);
        exit(1);
    }

    int proj_id = atoi(argv[1]);
    int pos     = atoi(argv[2]);
    int valor   = atoi(argv[3]);

    key_t clave = ftok("/etc", proj_id);

    // Obtener la memoria existente
    int shm_id = shmget(clave, 0, 0);
    if (shm_id == -1) {
        perror("Error en shmget (asegúrate de que ./memoria está corriendo)");
        exit(1);
    }

    // Adjuntar a nuestro espacio de direcciones
    int *array = (int *) shmat(shm_id, NULL, 0);
    if (array == (void *) -1) {
        perror("Error en shmat");
        exit(1);
    }

    // Modificar el dato compartido
    array[pos] = valor;

    // Solo desvincular, NUNCA destruir aquí
    shmdt(array);

    return 0;
}
