#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>

int sem_id = -1;
int es_creador = 0;

void manejar_sigint(int sig) {
    (void)sig;
    if (es_creador && sem_id != -1) {
        semctl(sem_id, 0, IPC_RMID);
        printf("\nSemáforo destruido por el creador.\n");
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    // Validar argumentos: 1 parámetro (argc=2) o 2 parámetros (argc=3)
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Uso: %s <proj_id> [valor_inicial]\n", argv[0]);
        exit(1);
    }

    signal(SIGINT, manejar_sigint);

    int proj_id = atoi(argv[1]);
    key_t clave = ftok("/etc", proj_id);

    // Obtener o crear el array de 1 semáforo
    sem_id = semget(clave, 1, 0600 | IPC_CREAT);
    if (sem_id == -1) {
        perror("Error en semget");
        exit(1);
    }

    // Solo si el usuario pasó valor_inicial (argc == 3), se inicializa
    if (argc == 3) {
        es_creador = 1;
        int valor_inicial = atoi(argv[2]);
        if (semctl(sem_id, 0, SETVAL, valor_inicial) == -1) {
            perror("Error al inicializar semáforo con SETVAL");
            exit(1);
        }
        printf("[Creador] Semáforo inicializado a: %d (semid: %d)\n", valor_inicial, sem_id);
    } else {
        printf("[Cliente] Conectado al semáforo existente (semid: %d)\n", sem_id);
    }

    struct sembuf acquire = { .sem_num = 0, .sem_op = -1, .sem_flg = 0 };
    struct sembuf release = { .sem_num = 0, .sem_op =  1, .sem_flg = 0 };

    // Bucle continuo para probar el aforo
    while (1) {
        printf("[PID %d] Entrando...\n", getpid());

        // Comprobar retorno de semop directamente
        if (semop(sem_id, &acquire, 1) == -1) {
            perror("Error en acquire (¿el semáforo fue borrado?)");
            break;
        }

        printf("[PID %d] Dentro. Pulsa Intro para salir...", getpid());
        fflush(stdout);
        getchar();

        semop(sem_id, &release, 1);
        printf("[PID %d] Fuera.\n\n", getpid());
    }

    return 0;
}
