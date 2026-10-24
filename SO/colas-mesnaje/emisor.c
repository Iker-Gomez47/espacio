#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct {
    long mtype;
    int  numero;
} msg_t;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <proj_id> <periodo>\n", argv[0]);
        return 1;
    }

    int proj_id = atoi(argv[1]);
    int periodo = atoi(argv[2]);

    key_t clave = ftok("/etc", proj_id);
    int id_cola = msgget(clave, 0600 | IPC_CREAT);

    // Manda los 10 mensajes normales
    for (int i = 1; i <= 10; i++) {
        msg_t msg = { .mtype = 1, .numero = i };
        msgsnd(id_cola, &msg, sizeof(msg) - sizeof(long), 0);
        sleep(periodo);
    }

    // Manda ADEMÁS el mensaje de fin
    msg_t fin = { .mtype = 999, .numero = 0 };
    msgsnd(id_cola, &fin, sizeof(fin) - sizeof(long), 0);

    return 0;
}
