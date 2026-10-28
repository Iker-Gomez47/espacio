// maxMonticulo.h
#include <stdbool.h>

typedef int tipoElementoMaxMonticulo;

typedef struct tMM {
    tipoElementoMaxMonticulo* array;
    int pos; // Siguiente posición libre (y número de elementos actuales)
    int numEl; // Capacidad máxima del array
} tipoMaxMonticulo;

// 0.5 ptos: Reserva la memoria para el array con la capacidad indicada e inicializa los campos.
void nuevoMaxMonticulo(tipoMaxMonticulo *m, int cap);

// 0.5 ptos: Devuelven el estado del montículo.
bool esVacio(tipoMaxMonticulo m);
bool estaLleno(tipoMaxMonticulo m);

// 2.0 ptos: Inserta un elemento manteniendo la propiedad de max-montículo (flotar).
void insertarMaxMonticulo(tipoMaxMonticulo *m, tipoElementoMaxMonticulo e);

// NUEVO: Elimina un elemento específico en lugar de solo la raíz
void eliminarElemento(tipoMaxMonticulo *m, tipoElementoMaxMonticulo e);

// 0.5 ptos: Devuelve el valor de la raíz sin eliminarla. Si está vacío, devuelve -1.
tipoElementoMaxMonticulo devolverRaiz(tipoMaxMonticulo m);
