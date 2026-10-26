#include "arbolinventario.h"
#include <stdio.h>
#include <stdlib.h>


int main(){

    int opcion;
    tipoArbolInventario *a = (tipoArbolInventario*)malloc(sizeof(tipoArbolInventario));
    nuevoArbolInventario(a);

    do{
        printf("--- GESTIÓN DE INVENTARIO ---\n");
        printf("1. Recibir piezas2.\nConsumir piezas\n3. Cerrar jornada");
        scanf ("%d", &opcion);

        if(opcion == 1){

            int id, cantidad;

            printf("Id Pieza: ");
            scanf("%d", &id);

            printf("\n Cantidad: ");
            scanf("%d", &cantidad);

            anadirStock(a, id, cantidad);
        }
        else if(opcion == 2){

            int id, cantidad;

            printf("Id Pieza: ");
            scanf("%d", &id);

            printf("\n Cantidad: ");
            scanf("%d", &cantidad);

            consumirStock(a, id, cantidad);

        }
        else if(opcion == 3){


            printf("\n Tipos de piezas en stock: %d\n", contarProductosDistintos(*a));

            mostrarInventario(*a);
        }


    }while(opcion != 3);
}
