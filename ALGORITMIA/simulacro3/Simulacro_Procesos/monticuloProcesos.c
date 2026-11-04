#include <stdio.h>
#include <stdlib.h>
#include "monticuloProcesos.h"

// Intercambio directo de la estructura completa
void intercambio(tipoProceso *x, tipoProceso *y){
    tipoProceso aux = *x;
    *x = *y;
    *y = aux;
}

void nuevoMonticulo(tipoMonticuloProcesos *m, int cap) {
    m->array = (tipoProceso*)malloc(sizeof(tipoProceso) * cap);
    m->pos = 0;
    m->numEl = cap;
}

bool esVacio(tipoMonticuloProcesos m) {
    return m.pos == 0;
}

bool estaLleno(tipoMonticuloProcesos m) {
    return m.pos == m.numEl;
}

void insertarProceso(tipoMonticuloProcesos *m, int id, int carga) {
    if (estaLleno(*m)) {
        printf("El monticulo esta lleno\n");
        return;
    }

    for (int i = 0; i < m->pos; i++) {
        if (m->array[i].idProceso == id) {
            printf("El proceso ya estaba\n");
            return;
        }
    }

    int i = m->pos;
    m->array[i].idProceso = id;
    m->array[i].cargaCPU = carga;
    m->pos++;

    while (i > 0 && m->array[i].cargaCPU < m->array[(i - 1) / 2].cargaCPU) {
        intercambio(&(m->array[i]), &(m->array[(i - 1) / 2]));
        i = (i - 1) / 2;
    }
}

void eliminarProceso(tipoMonticuloProcesos *m, int id) {
    if (esVacio(*m)) {
        printf("ya esta vacio\n");
        return;
    }

    int i;
    for (i = 0; i < m->pos; i++) {
        if (m->array[i].idProceso == id) {
            break;
        }
    }

    if (i == m->pos) {
        printf("El proceso a eliminar no estaba\n");
        return;
    }

    m->pos--;
    if (i == m->pos) {
        printf("Elemento a eliminar era justo el ultimo\n");
        return;
    }

    m->array[i] = m->array[m->pos];

    // Reequilibrio hacia arriba si es menor que el padre
    if (i > 0 && m->array[i].cargaCPU < m->array[(i - 1) / 2].cargaCPU) {
        while (i > 0 && m->array[i].cargaCPU < m->array[(i - 1) / 2].cargaCPU) {
            intercambio(&(m->array[i]), &(m->array[(i - 1) / 2]));
            i = (i - 1) / 2;
        }
    }
    // Reequilibrio hacia abajo si no subió
    else {
        while (i * 2 + 1 < m->pos) {
            int izq = i * 2 + 1;
            int der = i * 2 + 2;
            int hijoMen = izq;

            if (der < m->pos && m->array[der].cargaCPU < m->array[izq].cargaCPU) {
                hijoMen = der;
            }

            if (m->array[i].cargaCPU > m->array[hijoMen].cargaCPU) {
                intercambio(&(m->array[i]), &(m->array[hijoMen]));
                i = hijoMen;
            } else {
                break;
            }
        }
    }
}

void modificarCarga(tipoMonticuloProcesos *m, int id, int variacion) {
    if (esVacio(*m)) {
        printf("ya esta vacio\n");
        return;
    }

    int i;
    for (i = 0; i < m->pos; i++) {
        if (m->array[i].idProceso == id) {
            break;
        }
    }

    if (i == m->pos) {
        printf("El proceso a modificar no estaba\n");
        return;
    }

    // Si la carga resultante es negativa, se elimina del sistema
    if (m->array[i].cargaCPU + variacion < 0) {
        eliminarProceso(m, id);
        return;
    }

    // Aplicar la variación antes de evaluar el reequilibrio
    m->array[i].cargaCPU += variacion;

    // Caso subir (la carga se redujo)
    if (variacion < 0) {
        while (i > 0 && m->array[i].cargaCPU < m->array[(i - 1) / 2].cargaCPU) {
            intercambio(&(m->array[i]), &(m->array[(i - 1) / 2]));
            i = (i - 1) / 2;
        }
    }
    // Caso bajar (la carga aumento)
    else if (variacion > 0) {
        while (i * 2 + 1 < m->pos) {
            int izq = i * 2 + 1;
            int der = i * 2 + 2;
            int hijoMen = izq;

            if (der < m->pos && m->array[der].cargaCPU < m->array[izq].cargaCPU) {
                hijoMen = der;
            }

            if (m->array[i].cargaCPU > m->array[hijoMen].cargaCPU) {
                intercambio(&(m->array[i]), &(m->array[hijoMen]));
                i = hijoMen;
            } else {
                break;
            }
        }
    }
}

tipoProceso devolverRaiz(tipoMonticuloProcesos m) {
    if (esVacio(m)) {
        printf("esta vacio\n");
        tipoProceso nulo = {-1, -1};
        return nulo;
    }
    return m.array[0];
}

void mostrarAnchura(tipoMonticuloProcesos m) {
    if (esVacio(m)) {
        printf("esta vacio\n");
        return;
    }
    for (int i = 0; i < m.pos; i++) {
        printf("[ID: %d | Carga: %d] ", m.array[i].idProceso, m.array[i].cargaCPU);
    }
    printf("\n");
}
