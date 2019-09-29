#include "cola.h"
#include <stdlib.h>

/* Definición de Nodo
 */
typedef struct nodo {
    void* dato;
    struct nodo* prox;
} nodo_t;

struct cola {
    nodo_t* primero;
    nodo_t* ultimo;
};

cola_t* cola_crear(void){
    cola_t* cola = malloc(sizeof(nodo_t));
    if (cola == NULL) return NULL;
    
    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}

bool cola_esta_vacia(const cola_t *cola){
    return cola->primero == NULL;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
    nodo_t* actual;
    while(!cola_esta_vacia(cola)){
        if (destruir_dato){
            destruir_dato(cola->primero->dato);
        }
        actual = cola->primero;
        cola->primero = cola->primero->prox;
        free(actual);
    }
    free(cola);
}

nodo_t* crear_nodo(void* dato){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (nodo == NULL) return NULL;

    nodo->dato = dato;
    nodo->prox = NULL;
    return nodo;
}

bool cola_encolar(cola_t *cola, void* valor){
    nodo_t* nodo = crear_nodo(valor);

    //si la cola no tiene elementos
    if (cola_esta_vacia(cola)){
        cola->primero = nodo;
        cola->ultimo = nodo;
        return true;
    }

    cola->ultimo->prox = nodo;
    cola->ultimo = nodo;
    return true;
}

void* cola_ver_primero(const cola_t *cola){
    if (cola_esta_vacia(cola)){
        return NULL;
    }
    return cola->primero->dato;
}

void* cola_desencolar(cola_t *cola){
    if (cola_esta_vacia(cola)) return NULL; 
    nodo_t* actual = cola->primero;
    void* valor = cola->primero->dato;
    cola->primero = cola->primero->prox;
    if (cola->primero == NULL) cola->ultimo = NULL;
    free(actual);
    return valor;
}