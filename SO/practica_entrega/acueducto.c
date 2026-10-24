#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

int main(){

    int pid1 = fork();

    if (pid1 == 0){
        int fd = open("numeros.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd , 1);
        close(fd);
        execlp("./generador", "generador", NULL);
        exit(1);
    }
    waitpid(pid1, NULL, 0);

    int tuberia[2];
    pipe(tuberia);

    int pid2_0 = fork();
    if(pid2_0 == 0){
        close(tuberia[0]);
        int fd = open("numeros.txt", O_RDONLY);
        dup2(fd, 0);
        close(fd);

        dup2(tuberia[1], 1);
        close(tuberia[1]);
        execlp("./dec2rom", "dec2rom", NULL);
        exit(1);

    }

    int pid2_1 = fork();
    if (pid2_1 == 0){

        close(tuberia[1]);
        dup2(tuberia[0], 0);
        close(tuberia[0]);

        int fd = open("vuelta.txt",O_WRONLY | O_CREAT | O_TRUNC, 0644 );
        dup2(fd, 1);
        close(fd);
        execlp("./rom2dec", "rom2dec", NULL);
        exit(1);
    }

    close(tuberia[0]);
    close(tuberia[1]);
    waitpid(pid2_0, NULL, 0);
    waitpid(pid2_1, NULL, 0);

    int pid3 = fork();
    if(pid3 == 0){

        int fd = open("/dev/null", O_WRONLY);
        dup2(fd, 1);
        close(fd);

        execlp("diff", "diff", "vuelta.txt", "numeros.txt", NULL);
        exit(1);

    }

    int salida;
    waitpid(pid3, &salida, 0);

    if(WIFEXITED(salida) && WEXITSTATUS(salida) == 0 ){
        printf("Ambos documentos son identicos\n");
        return 0;
    }

    printf("Hay discrepancia entre documentos\n");
    return 1;



}
