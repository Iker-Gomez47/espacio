#include "maxMonticulo.h"
#include<stdio.h>
#include<stdlib.h>

void intercambio(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
}

// 0.5 ptos: Reserva la memoria para el array con la capacidad indicada e inicializa los campos.
void nuevoMaxMonticulo(tipoMaxMonticulo *m, int cap){
    m->array = (tipoElementoMaxMonticulo *)malloc(sizeof(tipoElementoMaxMonticulo)*cap);
    m->pos = 0;
    m->numEl = cap;
}

// 0.5 ptos: Devuelven el estado del montículo.
bool esVacio(tipoMaxMonticulo m){
    return m.pos == 0;
}
bool estaLleno(tipoMaxMonticulo m){
    return m.pos == m.numEl;
}

// 2.0 ptos: Inserta un elemento manteniendo la propiedad de max-montículo (flotar).
void insertarMaxMonticulo(tipoMaxMonticulo *m, tipoElementoMaxMonticulo e){
    if(estaLleno(*m)){
        printf("esta lleno \n");
    }
    else{
        m->array[m->pos] = e;
        int i = m->pos;
        m->pos ++;

        // CORRECCIÓN: 'i > 0' primero para evitar violaciones de segmento
        while(i > 0 && m->array[i] > m->array[(i -1)/2]){
            intercambio(&(m->array[i]), &(m->array[(i -1)/2]));
            i = (i-1)/2;
        }
    }
}

// NUEVO: Elimina un elemento específico en lugar de solo la raíz
void eliminarElemento(tipoMaxMonticulo *m, tipoElementoMaxMonticulo e){
    if(esVacio(*m)){
        printf("Esta vacio\n");
    }
    else{
        int i = 0;
        for(i = 0; i < m->pos; i++){
            if(m->array[i] == e){
                break;
            }
        }

        if(i == m->pos){
            printf("Elemento no encontrado \n");
        }
        else{
            m->pos --;
            if(i == m->pos){
                printf("El elemento a eliminar era justo el ultimo\n");
            }
            else{
                m->array[i] = m->array[m->pos];

                // 1. SUBIR (flotar)
                // CORRECCIÓN: Límites primero, y añadir la actualización de 'i'
                if(i > 0 && m->array[i] > m->array[(i -1)/2]){
                    while(i > 0 && m->array[i] > m->array[(i -1)/2]){
                        intercambio(&(m->array[i]), &(m->array[(i-1)/2]));
                        i = (i-1)/2;
                    }
                }
                // 2. BAJAR (hundir)
                // CORRECCIÓN: Comprobación segura de los hijos siguiendo tu lógica
                else{
                    while(2*i + 1 < m->pos){ // Mientras tenga al menos hijo izquierdo
                        int izq = 2*i + 1;
                        int der = 2*i + 2;
                        int mayorHijo = izq; // Asumimos por defecto que es el izquierdo

                        // Si tiene hijo derecho y es MAYOR que el izquierdo, el flujo fuerte va por la derecha
                        if(der < m->pos && m->array[der] > m->array[izq]){
                            mayorHijo = der;
                        }

                        // Comparamos la entrada con la salida más fuerte
                        if(m->array[i] < m->array[mayorHijo]){
                            intercambio(&(m->array[i]), &(m->array[mayorHijo]));
                            i = mayorHijo;
                        }
                        else{
                            // El nodo ya es mayor que sus hijos, está equilibrado
                            break;
                        }
                    }
                }
            }
        }
    }
}

// 0.5 ptos: Devuelve el valor de la raíz sin eliminarla. Si está vacío, devuelve -1.
tipoElementoMaxMonticulo devolverRaiz(tipoMaxMonticulo m){
    if(esVacio(m)){
        printf("esta vacio\n");
        return -1; // CORRECCIÓN: Faltaba devolver el código de error
    }
    else{
        return m.array[0];
    }
}
