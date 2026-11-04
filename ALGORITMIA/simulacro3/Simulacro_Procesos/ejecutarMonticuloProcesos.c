#include <stdio.h>
#include "monticuloProcesos.h"

int main() {
    int numEl, opcion, id, carga, variacion;
    tipoProceso proc;
    tipoMonticuloProcesos mon;

    printf("Introduce el numero maximo de procesos: ");
    scanf("%d", &numEl);
    nuevoMonticulo(&mon, numEl);

    do {
        printf("\n--------MENU PRUEBAS-------- \n");
        printf("1 - Insertar un proceso\n");
        printf("2 - Eliminar un proceso (por ID)\n");
        printf("3 - Modificar carga de un proceso\n");
        printf("4 - Mostrar proceso en la raiz\n");
        printf("5 - Mostrar monticulo en anchura\n");
        printf("6 - Salir.\n");
        printf("Escoja una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Introduce el ID del proceso: ");
                scanf("%d", &id);
                printf("Introduce la carga de CPU: ");
                scanf("%d", &carga);
                insertarProceso(&mon, id, carga);
                break;
            case 2:
                printf("Introduce el ID del proceso a eliminar: ");
                scanf("%d", &id);
                eliminarProceso(&mon, id);
                break;
            case 3:
                printf("Introduce el ID del proceso: ");
                scanf("%d", &id);
                printf("Introduce la variacion de carga (+ o -): ");
                scanf("%d", &variacion);
                modificarCarga(&mon, id, variacion);
                break;
            case 4:
                proc = devolverRaiz(mon);
                if (proc.idProceso != -1) {
                    printf("Raiz -> ID: %d | Carga: %d\n", proc.idProceso, proc.cargaCPU);
                }
                break;
            case 5:
                printf("Estado del monticulo:\n");
                mostrarAnchura(mon);
                printf("\n");
                break;
        }
    } while (opcion < 6);

    return 0;
}
