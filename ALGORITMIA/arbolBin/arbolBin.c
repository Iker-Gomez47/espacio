#include "arbolBin.h"
#include <stdio.h>
#include<stdlib.h>


void nuevoArbolBin(tipoArbolBin *a){

    *a = NULL;
}

bool esVacio(tipoArbolBin a){

    return a == NULL;
}

tipoArbolBin construir(tipoElementoArbolBin e, tipoArbolBin a1, tipoArbolBin a2){

    tipoArbolBin a = (tipoArbolBin)malloc(sizeof(celdaArbolBin));
    a->elem = e;
    a->izda = a1;
    a->dcha = a2;
    return a;
}

tipoElementoArbolBin devolverRaiz(tipoArbolBin a){

    return a->elem;
}

void preorden(tipoArbolBin a){

    if (!esVacio(a)){
        printf("%d ", a->elem);
        preorden(a->izda);
        preorden(a->dcha);

    }
}





void inorden(tipoArbolBin a){

    if (!esVacio(a)){
        inorden(a->izda);
        printf("%d ", a->elem);
        inorden(a->dcha);

    }
}

void postorden(tipoArbolBin a){

    if (!esVacio(a)){
        postorden(a->izda);
        preorden(a->dcha);
        printf("%d ", a->elem);

    }
}
