#include<stdio.h>
#include "minMonticulo.h"
#include <stdbool.h>
#include<stdlib.h>

void intercambio(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
}

void nuevoMinMonticulo(tipoMinMonticulo* m, int cap){

    m->numEl = cap;

    m->array = (tipoElementoMinMonticulo *)malloc(cap * sizeof(tipoElementoMinMonticulo));
    m->pos = 0;
}

void insertarMinMonticulo(tipoMinMonticulo *m, tipoElementoMinMonticulo e){
    if(estaLleno(*m)){
        printf("El monticulo esta lleno y no se puede insertar\n");

    }
    else if(m->pos < m->numEl){

        int i = m->pos;
        m->array[i] = e;
        m->pos += 1;

        while(i > 0 && m->array[i] < m->array[(i - 1)/ 2]){

                tipoElementoMinMonticulo aux = m->array[i];
                m->array[i] = m->array[( i -1 )/2];
                m->array[(i -1)/2] = aux;
                i = (i-1)/2;


        }


    }
}

void eliminarElemento(tipoMinMonticulo *m, tipoElementoMinMonticulo e) {

    if (esVacio(*m)) {
        printf("esta vacio\n");
        return;
    }

    int i;
    for (i = 0; i < m->pos; i++) {
        if (m->array[i] == e) {
            break;
        }
    }

    if (i == m->pos) {
        printf("elemento a borrar no se encontro\n");
        return;
    }

    m->pos--;

    if (i == m->pos) {
        printf("el elemento eliminado era el ultimo\n");
        return;
    }

    // Traemos el último elemento al nodo que ha quedado libre
    m->array[i] = m->array[m->pos];

    // SUBIR: Comprobamos el flujo hacia el nodo de donde vengo (el padre)
    while (i > 0 && m->array[i] < m->array[(i - 1) / 2]) {
        intercambio(&(m->array[i]), &(m->array[(i - 1) / 2]));
        i = (i - 1) / 2;
    }

    // BAJAR: Comprobamos el flujo hacia los nodos a donde voy (los hijos)
    while (2 * i + 1 < m->pos) {
        int izq = 2 * i + 1;
        int der = 2 * i + 2;

        // Caso con dos hijos
        if (der < m->pos) {
            // El hijo izquierdo es el menor de las salidas
            if (m->array[izq] <= m->array[der] && m->array[izq] < m->array[i]) {
                intercambio(&(m->array[i]), &(m->array[izq]));
                i = izq;
            }
            // El hijo derecho es el menor de las salidas
            else if (m->array[der] < m->array[izq] && m->array[der] < m->array[i]) {
                intercambio(&(m->array[i]), &(m->array[der]));
                i = der;
            }
            else {
                // El nodo actual ya es menor que ambos, está equilibrado
                break;
            }
        }
        // Caso con solo hijo izquierdo
        else {
            if (m->array[izq] < m->array[i]) {
                intercambio(&(m->array[i]), &(m->array[izq]));
                i = izq;
            }
            else {
                break;
            }
        }
    }
}

tipoElementoMinMonticulo devolverRaiz(tipoMinMonticulo m){
    if(m.pos == 0){
        printf("no hay nada");
        return -1;
    }

    return m.array[0];
}

void mostrarAnchura(tipoMinMonticulo m){

    for(int i = 0; i < m.pos; i++){
        printf("%d ", m.array[i]);
    }
}

bool esVacio(tipoMinMonticulo m){

    return m.pos == 0;
}

bool estaLleno(tipoMinMonticulo m){

    return m.pos == m.numEl;
}
