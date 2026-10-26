#include <stdio.h>
#include <stdlib.h>
#include "arbolinventario.h"

// 0.25 ptos: Inicializa el árbol a nulo
void nuevoArbolInventario(tipoArbolInventario *a){
    *a = NULL;
}

// 0.25 ptos: Comprueba si el árbol está vacío
bool esVacio(tipoArbolInventario a){
    return a == NULL;
}

// 2.0 ptos: Busca el id. Si no existe, crea el nodo con el stock indicado.
// Si existe, suma la cantidad al stock actual.
void anadirStock(tipoArbolInventario *a, tipoIdProducto id, tipoStock cantidad){
    if(esVacio(*a)){
        celdaArbolInventario *nuevo = (celdaArbolInventario*)malloc(sizeof(celdaArbolInventario));
        nuevo->izda = NULL;
        nuevo->dcha = NULL;
        nuevo->id = id;
        nuevo->stock = cantidad;
        *a = nuevo;
    }
    else{
        if((*a)->id == id){
            (*a)->stock += cantidad;
        }
        else if(id < (*a)->id){
            anadirStock(&((*a)->izda), id, cantidad);
        }
        else{
            anadirStock(&((*a)->dcha), id, cantidad);
        }
    }
}

// 2.5 ptos: Busca el id. Si existe, resta la cantidad indicada.
// ATENCIÓN: Si tras restar, el stock es <= 0, debe aplicar el algoritmo
// de borrado de ABB para eliminar el nodo completamente.
void consumirStock(tipoArbolInventario *a, tipoIdProducto id, tipoStock cantidad){
    if(esVacio(*a)){
        return;
    }
    else{
        if((*a)->id == id){
            if((*a)->stock - cantidad <= 0){

                if((*a)->izda == NULL && (*a)->dcha == NULL){ // hoja
                    free(*a);
                    *a = NULL;
                }
                else if((*a)->izda != NULL && (*a)->dcha == NULL){ // solo tiene hijo izquierdo
                    celdaArbolInventario *aux = *a;
                    *a = (*a)->izda;
                    free(aux);
                }
                else if((*a)->izda == NULL && (*a)->dcha != NULL){ // solo tiene hijo der
                    celdaArbolInventario *aux = *a;
                    *a = (*a)->dcha;
                    free(aux);
                }
                else{ // tiene los dos hijos
                    celdaArbolInventario *aux = (*a)->dcha;
                    while(aux->izda != NULL){
                        aux = aux->izda;
                    }

                    (*a)->id = aux->id;
                    (*a)->stock = aux->stock; // Copiar también el stock del sucesor

                    // Forzar el borrado del sucesor pasando su propio stock
                    consumirStock(&((*a)->dcha), aux->id, aux->stock);
                }
            }
            else{
                (*a)->stock -= cantidad;
            }
        }
        else if(id < (*a)->id){
            consumirStock(&((*a)->izda), id, cantidad);
        }
        else{
            consumirStock(&((*a)->dcha), id, cantidad);
        }
    }
}

// 0.5 ptos: Imprime el inventario ordenado de menor a mayor ID.
// Formato: "Producto: %d - Stock: %d\n"
void mostrarInventario(tipoArbolInventario a){
    if(!esVacio(a)){
        mostrarInventario(a->izda);
        printf("Producto: %d - Stock: %d\n", a->id, a->stock);
        mostrarInventario(a->dcha);
    }
}

// 0.5 ptos: Devuelve el número total de nodos (tipos de productos distintos) en el árbol.
int contarProductosDistintos(tipoArbolInventario a){
    if(esVacio(a)){
        return 0;
    }
    return 1 + contarProductosDistintos(a->izda) + contarProductosDistintos(a->dcha);
}
