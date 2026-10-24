#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){


    int padre_a_hijo[2];
    int hijo_a_padre[2];

    pipe(padre_a_hijo);
    pipe(hijo_a_padre);

    int pid = fork();

    if(pid > 0){

        close(padre_a_hijo[0]);
        close(hijo_a_padre[1]);
        int i = 1;
        write(padre_a_hijo[1], &i, sizeof(int));
        printf("[%d] envia %d\n", getpid(), i);

        while(read(hijo_a_padre[0], &i, sizeof(int )) > 0 && i < 10 ){
            printf("[%d] recibe %d de %d -> envia %d \n",getpid(), i, pid, i+1);
            i ++;
            write(padre_a_hijo[1], &i, sizeof(int));

        }
        printf("[%d] recibe %d de %d \n", getpid(), i, pid);
        close(padre_a_hijo[1]);
        close(hijo_a_padre[0]);
        wait(NULL);
        printf("[%d] termina \n", getpid());
        return 0;
    }
    else if(pid == 0){

        close(padre_a_hijo[1]);
        close(hijo_a_padre[0]);
        int i;
        while(read(padre_a_hijo[0], &i, sizeof(int)) > 0 && i < 10){
            printf("[%d] recibe %i de %d -> envia %d \n", getpid(), i, getppid(),i +1);
            i ++;
            write(hijo_a_padre[1], &i, sizeof(int));
        }

        close(padre_a_hijo[0]);
        close(hijo_a_padre[1]);
        printf("[%d] termina \n", getpid());
        exit(0);
    }
}
