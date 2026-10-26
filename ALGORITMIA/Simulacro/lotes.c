#include "colaPrioridades.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    tipoCola *cola = (tipoCola*)malloc(sizeof(tipoCola));
    nuevaCola(cola);

    int n_pedido = 1, opcion, lote = 1;
    do{
        printf("\nIntroduce pedido %d:\n", n_pedido); // Ajustado al formato del PDF
        printf("Pulsa 0 para pedido de plata\nPulsa 1 para pedido de oro\nPulsa 2 para no admitir nuevos pedidos hoy\n");
        printf("Opción: "); // Añadido para que sea igual al ejemplo
        scanf("%d", &opcion);

        if(opcion == 0){
            encolar(cola, n_pedido, 0);
            n_pedido++;
        }
        else if(opcion == 1){
            encolar(cola, n_pedido, 1);
            n_pedido++;
        }

        // Comprobamos si se ha llenado el lote normal
        if(nPrioritarios(*cola) == 3 || nPrioritarios(*cola) + nSecundarios(*cola) == 10){
            printf("Se ha producido el lote %d. Los pedidos producidos han sido:\n", lote);

            while(!esNulaCola(*cola)){
                printf("Pedido %d\n", frente(*cola)); // Quitados los dos puntos
                desencolar(cola);
            }
            lote++;
        }

    } while(opcion != 2);

    // NUEVO: Procesar el lote final al terminar el día
    if(!esNulaCola(*cola)){
        printf("Se ha producido el lote %d. Los pedidos producidos han sido:\n", lote);
        while(!esNulaCola(*cola)){
            printf("Pedido %d\n", frente(*cola));
            desencolar(cola);
        }
    }

    return 0;
}
