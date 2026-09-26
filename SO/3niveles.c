#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    // 1. RAMA A
    pid_t pidA = fork();
    if (pidA == 0) {
        pid_t pidIzq = fork();
        if (pidIzq == 0) {
            sleep(5); // Se mantiene vivo para salir en la foto de pstree
            exit(1);
        }

        pid_t pidDer = fork();
        if (pidDer == 0) {
            sleep(5);
            exit(2);
        }

        waitpid(pidIzq, NULL, 0);
        waitpid(pidDer, NULL, 0);
        exit(3);
    }

    // 2. RAMA B
    pid_t pidB = fork();
    if (pidB == 0) {
        pid_t pidIzq2 = fork();
        if (pidIzq2 == 0) {
            sleep(5);
            exit(4);
        }

        pid_t pidDer2 = fork();
        if (pidDer2 == 0) {
            sleep(5);
            exit(5);
        }

        waitpid(pidIzq2, NULL, 0);
        waitpid(pidDer2, NULL, 0);
        exit(6);
    }

    // --- PROCESO RAÍZ ---
    // Pausa breve para garantizar que A, B y los 4 nietos ya se crearon
    sleep(1);

    // Convertimos el PID de la raíz a texto para execlp
    char pid_str[16];
    snprintf(pid_str, sizeof(pid_str), "%d", getpid());

    // Creamos un hijo inspector para que ejecute pstree
    pid_t pid_inspector = fork();
    if (pid_inspector == 0) {
        printf("\n=== ÁRBOL DE PROCESOS CAPTURADO POR PSTREE ===\n");
        execlp("pstree", "pstree", "-p", pid_str, NULL);

        // Si execlp falla:
        perror("Error al ejecutar pstree");
        exit(EXIT_FAILURE);
    }

    // El proceso raíz recoge a todos sus hijos
    waitpid(pid_inspector, NULL, 0); // Espera a que pstree termine de imprimir
    waitpid(pidA, NULL, 0);          // Espera a la rama A
    waitpid(pidB, NULL, 0);          // Espera a la rama B

    printf("\nTodos los procesos han finalizado correctamente.\n");
    return 0;
}
