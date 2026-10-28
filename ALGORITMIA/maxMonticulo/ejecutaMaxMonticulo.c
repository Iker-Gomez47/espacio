#include <stdio.h>
#include "maxMonticulo.h"

int main() {
    int capacidad, opcion;
    tipoElementoMaxMonticulo elem;
    tipoMaxMonticulo mon;

    printf("Introduce la capacidad maxima del monticulo: ");
    scanf("%d", &capacidad);
    nuevoMaxMonticulo(&mon, capacidad);

    do {
        printf("\n--------MENU PRUEBAS MAX-MONTICULO-------- \n");
        printf("1 - Insertar un elemento\n");
        printf("2 - Eliminar un elemento especifico\n");
        printf("3 - Mostrar la raiz (maximo)\n");
        printf("4 - Salir.\n");
        printf("Escoja una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Introduce el valor a insertar: ");
                scanf("%d", &elem);
                insertarMaxMonticulo(&mon, elem);
                break;
            case 2:
                printf("Introduce el valor a eliminar: ");
                scanf("%d", &elem);
                eliminarElemento(&mon, elem);
                printf("Se ha ejecutado la orden de eliminacion.\n");
                break;
            case 3:
                printf("El elemento maximo actual es: %d\n", devolverRaiz(mon));
                break;
        }
    } while (opcion < 4);

    return 0;
}
