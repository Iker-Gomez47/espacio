#include "colaPrioridades.h"
#include <stdio.h>
#include <stdlib.h>

void nuevaCola(tipoCola *c){
    c->ini = NULL;
    c->fin = NULL;
    // CORRECCIÓN: Inicialización correcta a NULL (antes ponía solo c->ultimo_prioritario;)
    c->ultimo_prioritario = NULL;
    c->n_prioritarios = 0;
    c->n_secundarios = 0;
}

bool hayPrioritarios(tipoCola c){
    return c.n_prioritarios > 0;
}

bool haySecundarios(tipoCola c){
    return c.n_secundarios > 0;
}

bool esNulaCola(tipoCola c){
    return c.ini == NULL;
}

void encolar(tipoCola * c, tipoValorElemento e, tipoPrioridadElemento p){

    if(p == 0){
        c->n_secundarios ++;
    }
    else{
        c->n_prioritarios ++;
    }

    celdaCola *nuevo = (celdaCola*)malloc(sizeof(celdaCola));
    nuevo->elem = e;
    nuevo->prioridad = p;

    if(esNulaCola(*c)){
        c->ini = nuevo;
        c->fin = nuevo;
        nuevo->sig = NULL;

        if(p == 1){
            c->ultimo_prioritario = nuevo;
        }
    }
    else{
        if(p == 1){
            if(c->ultimo_prioritario == NULL){
                nuevo->sig = c->ini;
                c->ini = nuevo;
                c->ultimo_prioritario = nuevo;
            }
            else if(c->fin->prioridad == 1){
                c->fin->sig = nuevo;
                nuevo->sig = NULL;
                c->fin = nuevo;
                c->ultimo_prioritario = nuevo;
            }
            else{
                nuevo->sig = c->ultimo_prioritario->sig;
                c->ultimo_prioritario->sig = nuevo;
                c->ultimo_prioritario = nuevo;
            }
        }
        else if(p == 0){
            c->fin->sig = nuevo;
            nuevo->sig = NULL;
            c->fin = nuevo;
        }
    }
}



void desencolar(tipoCola *c){

    if(esNulaCola(*c)){
        printf("No se puede desencolar en cola vacia\n");
    }
    else{
        celdaCola *aux = c->ini;
        c->ini = c->ini->sig ;

        // NUEVO: Si el elemento que estamos sacando era el último prioritario que quedaba,
        // debemos resetear su marcador a NULL.
        if (aux == c->ultimo_prioritario) {
            c->ultimo_prioritario = NULL;
        }

        // NUEVO: Si al sacar el elemento la cola se ha quedado completamente vacía,
        // el puntero de fin también debe resetearse a NULL.
        if (c->ini == NULL) {
            c->fin = NULL;
        }

        if(aux->prioridad == 0){
            c->n_secundarios --;
        }
        else{
            c->n_prioritarios --;
        }

        free(aux);
    }
}

tipoValorElemento frente(tipoCola c){

    if (esNulaCola(c)){
        printf("la cola esta vacia\n");
        exit(-1);
    }
    else{
        return c.ini->elem;
    }
}

int nPrioritarios(tipoCola c){
    return c.n_prioritarios;
}

int nSecundarios(tipoCola c){
    return c.n_secundarios;
}
