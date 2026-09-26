#include "colaDobleCaracteres.h"
#include<stdio.h>
#include<stdlib.h>

void nuevaColaDoble(tipoColaDoble *cola){

    cola-> ini = NULL;
    cola-> fin = NULL;
}

void encolarPrimero(tipoColaDoble *cola, tipoElementoColaDoble e){

    celdaColaDoble *nuevo = (celdaColaDoble*)malloc(sizeof(celdaColaDoble));
    nuevo->elem = e;
    nuevo->ant = NULL;

    if (cola->ini == NULL){

        nuevo->sig = NULL;
        cola->ini = nuevo;
        cola->fin = nuevo;

    }
    else{

        nuevo->sig = cola->ini;
        cola->ini->ant = nuevo;
        cola->ini = nuevo;
    }
}

void encolarUltimo(tipoColaDoble *cola, tipoElementoColaDoble e)
{

    celdaColaDoble *nuevo = (celdaColaDoble*)malloc(sizeof(celdaColaDoble));
    nuevo->elem = e;
    nuevo->sig = NULL;

    if(cola->ini == NULL){

        cola->ini = nuevo;
        cola->fin = nuevo;
        nuevo->ant = NULL;
    }
    else{




        nuevo->ant = cola->fin;
        cola->fin->sig = nuevo;
        cola->fin = nuevo;

    }

}

void desencolarPrimero(tipoColaDoble *cola){

    if(cola->ini == NULL){
        printf("La cola ya esta vacia ");
    }
    else if(cola->ini->sig == NULL){

        free(cola->ini);
        cola-> ini = NULL;
        cola-> fin = NULL;

    }
    else{

        celdaColaDoble *aux = cola->ini;
        cola->ini = cola->ini->sig;
        cola->ini->ant = NULL;
        free(aux);
    }

}

void desencolarUltimo(tipoColaDoble *cola){

    if(cola->ini == NULL){
        printf("La cola ya esta vacia ");
    }
    else if(cola->ini->sig == NULL){

        free(cola->ini);
        cola-> ini = NULL;
        cola-> fin = NULL;

    }
    else{

        celdaColaDoble *aux = cola->fin;
        cola->fin = cola->fin->ant;
        cola->fin->sig = NULL;
        free(aux);
    }

}

tipoElementoColaDoble elemPrimero(tipoColaDoble cola){

    if(esNulaColaDoble(cola)){
        printf("la cola es nula ");
        exit(-1);
    }
    return cola.ini->elem;
}

tipoElementoColaDoble elemUltimo(tipoColaDoble cola ){
    if(esNulaColaDoble(cola)){
        printf("la cola es nula ");
        exit(-1);
    }
    return cola.fin->elem;
}

bool esNulaColaDoble(tipoColaDoble cola ){

    return cola.ini == NULL;
}
