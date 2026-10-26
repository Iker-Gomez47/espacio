#include <stdio.h>
#include "arbolInventario.h"

int main() {
    tipoArbolInventario arbol;
    tipoIdProducto id;
    tipoStock cantidad;
    int opcion;

    nuevoArbolInventario(&arbol);

    do {
        printf("\n--------MENU PRUEBAS LIBRERIA-------- \n");
        printf("1 - Anadir stock a un producto\n");
        printf("2 - Consumir stock de un producto\n");
        printf("3 - Mostrar inventario completo (in-orden)\n");
        printf("4 - Contar tipos de productos distintos\n");
        printf("5 - Salir.\n");
        printf("Escoja una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Introduce el ID del producto: ");
                scanf("%d", &id);
                printf("Introduce la cantidad a anadir: ");
                scanf("%d", &cantidad);
                anadirStock(&arbol, id, cantidad);
                printf("Stock actualizado.\n");
                break;
            case 2:
                printf("Introduce el ID del producto: ");
                scanf("%d", &id);
                printf("Introduce la cantidad a consumir: ");
                scanf("%d", &cantidad);
                consumirStock(&arbol, id, cantidad);
                printf("Consumo registrado.\n");
                break;
            case 3:
                printf("--- ESTADO DEL INVENTARIO ---\n");
                if (esVacio(arbol)) {
                    printf("El inventario esta vacio.\n");
                } else {
                    mostrarInventario(arbol);
                }
                break;
            case 4:
                printf("Tipos de productos distintos en el arbol: %d\n", contarProductosDistintos(arbol));
                break;
        }
    } while (opcion < 5);

    return 0;
}
