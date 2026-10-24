#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TAMANO 10
#define MIN 1
#define MAX 3999




typedef int T_Tabla[TAMANO];


void generar_aleatorios(int *salida) {

    *salida = rand() % (MAX - MIN + 1) + MIN;

}

void imprime_romano(int decimal) {
    int valores[]     = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *simbolos[]  = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const int n_simbolos = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n_simbolos; i++) {
        for (; decimal >= valores[i]; decimal -= valores[i])
             printf("%s", simbolos[i]);
    }
    printf("\n");
}

int main(){





    int tuberia[2];
    pipe(tuberia);

    int pid = fork();

    if(pid != 0){

        int e,i; // aqui

        close(tuberia[0]);
        srand(time(NULL));

        for (i = 1 ; i <= TAMANO; i++){

            generar_aleatorios(&e);
            printf("%d genera %d \n", getpid(), e);
            write(tuberia[1], &e, sizeof(int));
            sleep(1);
        }

        close(tuberia[1]);
        wait(NULL);
        printf("termino soy el proceso padre %d\n",getpid());


    }

    else{

        close(tuberia[1]);
        for(int i = 0; i < TAMANO; i++){

            int p;
            read(tuberia[0], &p, sizeof(p));
            printf("%d recibe -> %d \n",getpid(), p);
            imprime_romano(p);
        }
        close(tuberia[0]);
        printf("termino soy el proceso hijo %d\n",getpid());
        exit(0);

    }
    return 0;
}

