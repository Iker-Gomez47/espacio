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

int main(int argc, char *argv[]){


    int proj_id = atoi(argv[1]);

    key_t llave = ftok("/etc", proj_id);
    int cola_id = msgget(llave, 0600 | IPC_CREAT);

    for(msg_t msg;;){

        msgrcv(cola_id, &msg, sizeof(msg_t) - sizeof(long), -2, 0 );
        printf("PRIORIDAD: %d\n", msg.numero);
        sleep(2);
    }
}
