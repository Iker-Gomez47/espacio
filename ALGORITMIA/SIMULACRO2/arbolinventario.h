// arbolInventario.h
#include <stdbool.h>

typedef int tipoIdProducto;
typedef int tipoStock;

typedef struct celdaInventario {
    tipoIdProducto id;
    tipoStock stock;
    struct celdaInventario* izda;
    struct celdaInventario* dcha;
} celdaArbolInventario;

typedef celdaArbolInventario* tipoArbolInventario;

// 0.25 ptos: Inicializa el árbol a nulo
void nuevoArbolInventario(tipoArbolInventario *a);

// 0.25 ptos: Comprueba si el árbol está vacío
bool esVacio(tipoArbolInventario a);

// 2.0 ptos: Busca el id. Si no existe, crea el nodo con el stock indicado.
// Si existe, suma la cantidad al stock actual.
void anadirStock(tipoArbolInventario *a, tipoIdProducto id, tipoStock cantidad);

// 2.5 ptos: Busca el id. Si existe, resta la cantidad indicada.
// ATENCIÓN: Si tras restar, el stock es <= 0, debe aplicar el algoritmo
// de borrado de ABB para eliminar el nodo completamente.
void consumirStock(tipoArbolInventario *a, tipoIdProducto id, tipoStock cantidad);

// 0.5 ptos: Imprime el inventario ordenado de menor a mayor ID.
// Formato: "Producto: %d - Stock: %d\n"
void mostrarInventario(tipoArbolInventario a);

// 0.5 ptos: Devuelve el número total de nodos (tipos de productos distintos) en el árbol.
int contarProductosDistintos(tipoArbolInventario a);
