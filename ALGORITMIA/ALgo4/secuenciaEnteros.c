#include "secuenciaEnteros.h"
#include <stdio.h>
#include<stdlib.h>

void nuevaSecuencia(tipoSecuencia* sec){
    nuevaPila(&sec->pilaIzq);
    nuevaPila(&sec->pilaIzq);

}

void insertarDelantePunto(tipoSecuencia* sec, tipoElementoPila e){

    apilar(&sec->pilaIzq, e);
}

void insertarEnPunto(tipoSecuencia* sec, tipoElementoPila e) {

    apilar(&sec->pilaDcha, e);
}

void eliminarEnPunto(tipoSecuencia* sec){

    desapilar(&sec->pilaDcha);
}

tipoElementoPila consultarEnPunto(tipoSecuencia sec){

    return cima(sec.pilaDcha);
}

void avanzarPunto (tipoSecuencia* sec){
    tipoElementoPila e = consultarEnPunto(*sec);
    desapilar(&sec->pilaDcha);
    apilar(&sec->pilaIzq, e);

void moverPuntoAlPrincipio (tipoSecuencia* sec){

    while(!(esNulaPila(sec->pilaIzq))){
        tipoElementoPila x =   cima(sec->pilaIzq);
        desapilar(&sec->pilaIzq);
        apilar(&sec->pilaDcha, x);
    }
}

bool esPuntoUltimo(tipoSecuencia sec){

    return esNulaPila(sec.pilaDcha);

}

bool esVaciaSecuencia(tipoSecuencia){

    return (     esNulaPila(sec.pilaDcha) && esNulaPila(sec.pilaIzq));
}
