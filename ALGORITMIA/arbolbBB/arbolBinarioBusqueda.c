#include "arbolBinarioBusqueda.h"
#include <stdlib.h>
#include <stdio.h>
void nuevoArbolBB(tipoArbolBB *a){

    *a = NULL;
}

void insertar(tipoArbolBB *a, tipoElementoArbolBusqueda e){

    if(esVacio(*a)){

        *a = (celdaArbolBusqueda*)malloc(sizeof(celdaArbolBusqueda));
        (*a)->elem = e;
        (*a)->izda = NULL;
        (*a)->dcha = NULL;

    }
    else{

        if(e < (*a)->elem){

            insertar(&((*a)->izda), e);
        }
        else if(e > (*a)->elem){

            insertar(&((*a)->dcha), e);
        }
    }
}

void borrar(tipoArbolBB *a, tipoElementoArbolBusqueda e){

    // CORRECCIÓN 2: Caso base para evitar cuelgues si el elemento no existe
    if (esVacio(*a)) {
        return;
    }

    // CORRECCIÓN 1: Aplicación de paréntesis (*a)-> en todo el código
    if (e == (*a)->elem){

        if ((*a)->izda == NULL && (*a)->dcha == NULL){

            free(*a);
            *a = NULL; // CORRECCIÓN 3: Evitar el puntero colgante
        }
        else if((*a)->izda != NULL && (*a)->dcha == NULL){

            tipoArbolBB aux = *a;
            *a = (*a)->izda;
            free(aux);
        }
        else if ((*a)->izda == NULL && (*a)->dcha != NULL){

            tipoArbolBB aux = *a;
            *a = (*a)->dcha;
            free(aux);

        }
        else if((*a)->izda != NULL && (*a)->dcha != NULL){

            celdaArbolBusqueda *aux = (*a)->dcha; // Damos un paso a la derecha

            while (aux->izda != NULL) {           // Y bajamos todo lo posible a la izquierda
                aux = aux->izda;
            }

            // Colocar el sucesor en la posición del elemento a eliminar
            (*a)->elem = aux->elem;

            // Eliminar el sucesor de su posición original
            borrar(&((*a)->dcha), aux->elem);
        }

    }
    // Continuación de la búsqueda si no lo hemos encontrado aún
    else if (e < (*a)->elem){

        borrar(&((*a)->izda), e);
    }
    else if (e > (*a)->elem){

        borrar(&((*a)->dcha), e);
    }
}

// Recorrido en pre-orden (Raíz, Izquierda, Derecha)
void mostrarPreorden(tipoArbolBB a) {
    if (!esVacio(a)) {
        printf("%d ", a->elem);
        mostrarPreorden(a->izda);
        mostrarPreorden(a->dcha);
    }
}

// Recorrido en in-orden (Izquierda, Raíz, Derecha)
void mostrarInorden(tipoArbolBB a) {
    if (!esVacio(a)) {
        mostrarInorden(a->izda);
        printf("%d ", a->elem);
        mostrarInorden(a->dcha);
    }
}

// Recorrido en post-orden (Izquierda, Derecha, Raíz)
void mostrarPostorden(tipoArbolBB a) {
    if (!esVacio(a)) {
        mostrarPostorden(a->izda);
        mostrarPostorden(a->dcha);
        printf("%d ", a->elem);
    }
}

bool esVacio(tipoArbolBB a){

    return a == NULL;
}
