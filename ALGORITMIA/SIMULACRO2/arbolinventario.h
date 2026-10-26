#include "arbolInventario.h"
#include <stdio.h>

int main(){

    int opcion;
    // Declaración local más limpia y eficiente
    tipoArbolInventario arbol;
    nuevoArbolInventario(&arbol);

    do{
        printf("\n--- GESTIÓN DE INVENTARIO ---\n");
        printf("1. Recibir piezas\n");
        printf("2. Consumir piezas\n");
        printf("3. Cerrar jornada\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        if(opcion == 1){
            int id, cantidad;
            printf("ID Pieza: ");
            scanf("%d", &id);
            printf("Cantidad: ");
            scanf("%d", &cantidad);

            anadirStock(&arbol, id, cantidad);
        }
        else if(opcion == 2){
            int id, cantidad;
            printf("ID Pieza: ");
            scanf("%d", &id);
            printf("Cantidad: ");
            scanf("%d", &cantidad);

            consumirStock(&arbol, id, cantidad);
        }
        else if(opcion == 3){
            printf("\nCIERRE DE JORNADA\n");
            printf("Tipos de piezas en stock: %d\n", contarProductosDistintos(arbol));
            printf("Listado de inventario:\n");
            mostrarInventario(arbol);
        }

    } while(opcion != 3);

    return 0;
}
