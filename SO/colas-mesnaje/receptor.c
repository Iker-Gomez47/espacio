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

    for (msg_t msg ;;) {
        // msgtyp = 0 para retirar el mensaje más antiguo de cualquier tipo
        msgrcv(id_cola, &msg, sizeof(msg) - sizeof(long), 0, 0);

        if (msg.mtype == 999) {
            msgctl(id_cola, IPC_RMID, NULL);
            printf("Cola destruida\n");
            break;
        }

        printf("Elemento del mensaje: %d\n", msg.numero);
        sleep(periodo);
    }

    return 0;
}
