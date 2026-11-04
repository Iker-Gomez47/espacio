#ifndef MONTICULOPROCESOS_H
#define MONTICULOPROCESOS_H

#include <stdbool.h>

typedef struct {
    int idProceso;
    int cargaCPU; // Criterio de ordenación del Min-Montículo (menor carga = más arriba)
} tipoProceso;

typedef struct {
    tipoProceso* array;
    int pos;
    int numEl;
} tipoMonticuloProcesos;

// 0.5 ptos: Reserva memoria para 'cap' elementos e inicializa el montículo.
void nuevoMonticulo(tipoMonticuloProcesos *m, int cap);

// 0.5 ptos: Comprobaciones de estado.
bool esVacio(tipoMonticuloProcesos m);
bool estaLleno(tipoMonticuloProcesos m);

// 1.5 ptos: Inserta un nuevo proceso manteniendo el orden por 'cargaCPU' (menor arriba).
// Si el idProceso ya existe en el montículo, NO lo inserta y avisa por pantalla.
void insertarProceso(tipoMonticuloProcesos *m, int id, int carga);

// 1.5 ptos: Elimina un proceso buscando por su 'idProceso' y reequilibra el montículo.
void eliminarProceso(tipoMonticuloProcesos *m, int id);

// 1.5 ptos: ¡EL RETO! Busca el proceso con 'id'. Si existe, le suma 'variacion' a su 'cargaCPU'
// (ojo: 'variacion' puede ser positiva o negativa) y reequilibra el nodo (flotar o hundir).
void modificarCarga(tipoMonticuloProcesos *m, int id, int variacion);

// 0.25 ptos: Devuelve el proceso de la raíz (menor carga). Si está vacío, devuelve id=-1 y carga=-1.
tipoProceso devolverRaiz(tipoMonticuloProcesos m);

// 0.25 ptos: Muestra todos los procesos en anchura con formato: "[ID: %d | Carga: %d] "
void mostrarAnchura(tipoMonticuloProcesos m);

#endif
