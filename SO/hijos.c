#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    // Proceso A (el original) crea al proceso B
    int pidB = fork();

    if (pidB == 0) {
        // --- PROCESO B ---
        printf("[Hijo B | PID: %d] Mi padre (A) es: %d\n", getpid(), getppid());

        int pidC = fork(); // B crea a C

        if (pidC == 0) {
            // --- PROCESO C ---
            printf("[Hijo C | PID: %d] Mi padre (B) es: %d\n", getpid(), getppid());

            int pidD = fork(); // C crea a D

            if (pidD == 0) {
                // --- PROCESO D ---
                printf("[Hijo D | PID: %d] Mi padre (C) es: %d\n", getpid(), getppid());

                // D no tiene hijos: termina directamente
                exit(4);
            }

            // --- C RECUPERA A D ---
            waitpid(pidD, NULL, 0); // C espera a que D termine
            printf("[Hijo C | PID: %d] D ha terminado. Yo también termino.\n", getpid());
            exit(3); // C termina después de que D acabó
        }

        // --- B RECUPERA A C ---
        waitpid(pidC, NULL, 0); // B espera a que C termine
        printf("[Hijo B | PID: %d] C ha terminado. Yo también termino.\n", getpid());
        exit(2); // B termina después de que C acabó
    }

    // --- A RECUPERA A B ---
    waitpid(pidB, NULL, 0); // A espera a que B termine
    printf("[Padre A | PID: %d] Mi hijo B (y toda su descendencia) ha terminado.\n", getpid());

    return 0; // A finaliza el programa
}
