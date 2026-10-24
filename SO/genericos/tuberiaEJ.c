


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
    char nombre[32];
    char apellido[32];
    int edad;
    char telefono[10];
} contacto_t;

int main(void) {
    int tuberia[2];
    pipe(tuberia);

    if (fork() == 0) { // rama hijo
        close(tuberia[0]); // cierra lectura, solo escribe
        contacto_t agenda[3] = {
            {"Ana",   "Garcia", 30, "645111222"},
            {"Luis",  "Perez",  21, "633333444"},
            {"Marta", "Lopez",  41, "612555666"}
        };
        write(tuberia[1], agenda, sizeof(agenda));
        exit(0);
    }

    // rama padre
    close(tuberia[1]); // cierra escritura, solo lee
    for (contacto_t p; read(tuberia[0], &p, sizeof(p)) > 0;) {
        printf("%s %s, %d años, tel. %s\n",
               p.nombre, p.apellido, p.edad, p.telefono);
    }
}
