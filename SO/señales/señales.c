#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

volatile sig_atomic_t estado = 0;

void manejador_usr(int sig) {
    (void)sig;
    estado = 1;
}

void manejador_alarm(int sig) {
    (void)sig; // Solo despierta el pause()
}

int main(void) {
    int pid = fork();

    if (pid == 0) {
        signal(SIGUSR1, manejador_usr);

        struct sigaction act = { .sa_handler = manejador_alarm, .sa_flags = 0 };
        sigaction(SIGALRM, &act, NULL);

        alarm(3);
        pause(); // Se bloquea hasta que llegue SIGUSR1 o SIGALRM

        if (estado == 1) {
            alarm(0); // Cancela la cuenta atrás si llegó a tiempo
            printf("Hijo: ¡Señal recibida a tiempo! Empiezo a trabajar.\n");
            exit(0);
        }

        printf("Hijo: El padre tardó demasiado, me canso de esperar.\n");
        exit(1);
    }

    // Código del Padre
    sleep(5); // Cambia esto a sleep(4) para probar el timeout
    int status;

    kill(pid, SIGUSR1); // Primero a QUIÉN (pid), luego QUÉ (señal)
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        printf("El hijo acabo con: %d\n", WEXITSTATUS(status));
    } else {
        printf("El hijo acabo mal\n");
    }

    return 0;
}
