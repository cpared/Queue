#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VOLUMEN 1000
#define MAX_ELEMENTOS 500
#define CANT_CARACTERES_ASCII 255
#define CANT_DATOS_NULL 10
#define LARGO_VEC_NULL 5
#define LARGO_VEC 10

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

//Creo la función para destruir los datos de Bárbara
void destruir_dato(void* valor){
    free(valor);
}

//Creo un puntero a un entero dinámico con un valor
int* crear_entero_dinamico(void){
    int* entero_dinamico = malloc(sizeof(int));
    if (entero_dinamico == NULL){
        return NULL;
    }
    *entero_dinamico = 2;
    return entero_dinamico;
}

//Creo un puntero a un caracter dinámico con un valor
char* crear_caracter_dinamico(void){
    char* caracter_dinamico = malloc(sizeof(char));
    if (caracter_dinamico == NULL){
        return NULL;
    }
    *caracter_dinamico = 'C';
    return caracter_dinamico;
}

void pruebas_crear_cola(void){
    cola_t* cola = cola_crear();

    print_test("La cola fue creada exitosamente", cola != NULL);
    print_test("La cola está vacía", cola_esta_vacia(cola));
    print_test("La cola no tiene elementos", cola_ver_primero(cola) == NULL);
    print_test("No se puede desacolar una cola vacia", cola_desencolar(cola) == NULL);

    cola_destruir(cola,NULL);
}

void pruebas_volumen(void){
    cola_t* cola = cola_crear();

    int vector_enteros[MAX_ELEMENTOS];
    char vector_caracteres[MAX_ELEMENTOS];
    void* valor_prueba;
    bool ok = true;

    //Lleno el vector con enteros
    for (int i = 0; i < MAX_ELEMENTOS; i++){
        vector_enteros[i] = i;
    }

    //Lleno el vector con cadenas
    for (int i = 0; i < MAX_ELEMENTOS; i++){
        vector_caracteres[i] = (char)(i % CANT_CARACTERES_ASCII);
    }

    for (int i = 0; ok && i < MAX_VOLUMEN; i++){
        //Encolo enteros 
        if (i < MAX_ELEMENTOS){
            cola_encolar(cola,&vector_enteros[i]);
        }
        //Encolo caracteres
        else {
            cola_encolar(cola,&vector_caracteres[i - MAX_ELEMENTOS]);
        }
        valor_prueba = cola_ver_primero(cola);
        ok = valor_prueba == &vector_enteros[0];
        }
    
    print_test("Prueba encolar vector enteros y caracteres",ok);

    // Desencolo y voy validando que lo que saco corresponda al vector
    // enteros o caracteres dato por dato
    ok = true;
    for (int i = 0; ok && i < MAX_VOLUMEN; i++){
        valor_prueba = cola_desencolar(cola);
        if (i < MAX_ELEMENTOS){
            ok = valor_prueba == &vector_enteros[i];
        }
        else {
            ok = valor_prueba == &vector_caracteres[i - MAX_ELEMENTOS];
        }
    }
    print_test("Prueba desencolar vector enteros y caracteres",ok);

    //Compruebo que la cola quede vacía
    //Compruebo que no tenga primero
    print_test("La cola esta vacia nuevamente", cola_esta_vacia(cola));
    print_test("La cola no tiene elementos", cola_ver_primero(cola) == NULL);

    cola_destruir(cola,NULL);
}

void pruebas_encola_null(void){
    cola_t* cola = cola_crear();
    void* valor_prueba;
    bool ok = true;

    //Creo un vector de NULLs
    void* vector_null[] = {NULL,NULL,NULL,NULL,NULL};

    //Encolo los valores y valido que el primero siempre sea el mismo
    for (int i = 0; i < LARGO_VEC_NULL; i++){
        cola_encolar(cola,&vector_null[i]);
        valor_prueba = cola_ver_primero(cola);
        ok = valor_prueba == &vector_null[0];
    }

    print_test("Prueba encolar NULL",ok);
    print_test("La cola NO está vacía",cola_esta_vacia(cola) == false);
    print_test("La cola tiene elementos", cola_ver_primero(cola) != NULL);


    //Desencolo y voy validando que correspondan a los datos del vector
    for (int i = 0; i < LARGO_VEC_NULL; i++){
        valor_prueba = cola_desencolar(cola);
        ok = valor_prueba == &vector_null[i];
    }

    print_test("Prueba desencolar vector NULL",ok);
    print_test("La cola esta vacia nuevamente", cola_esta_vacia(cola));
    print_test("La cola no tiene elementos", cola_ver_primero(cola) == NULL);

    cola_destruir(cola,NULL);
}

void prueba_encola_arreglos(void){
    cola_t* cola = cola_crear();
    void* valor_prueba;
    bool ok = true;
    //Creo vector de enteros y caracteres
    int vector_enteros2[] = {0,-1,2,5,-29,100,7,20,-150,50};
    char vector_caracteres2[] = "riverplate";

    //Encolo vector_enteros2
    for (int i = 0; i < LARGO_VEC; i++){
        cola_encolar(cola,&vector_enteros2[i]);
        valor_prueba = cola_ver_primero(cola);
        ok = valor_prueba == &vector_enteros2[0];
    }

    print_test("Prueba encolar enteros",ok);

    //Encolo vector_caracteres2
    ok = true;
    for (int i = 0; i < LARGO_VEC; i++){
        cola_encolar(cola,&vector_caracteres2[i]);
        valor_prueba = cola_ver_primero(cola);
        ok = valor_prueba == &vector_enteros2[0]; //Sigue siendo el 1er de vector_enteros2
    }

    print_test("Prueba encolar caracteres",ok);

    //Desencolo y valido los valores encolados
    ok = true;
    int j = 0;
    while(!cola_esta_vacia(cola) && ok){
        valor_prueba = cola_ver_primero(cola);
        if (j < LARGO_VEC){
            ok = valor_prueba == &vector_enteros2[j];
        }
        else {
            ok = valor_prueba == &vector_caracteres2[j - LARGO_VEC];
        }
        cola_desencolar(cola);
        j++;
    }

    print_test("Prueba desencolar y comparar",ok);
    print_test("La cola esta vacia nuevamente", cola_esta_vacia(cola));
    print_test("La cola no tiene elementos", cola_ver_primero(cola) == NULL);

    cola_destruir(cola,NULL);
}

void prueba_destruir_valor_dinamico(void){
    cola_t* cola2 = cola_crear();

    print_test("La cola fue creada exitosamente", cola2 != NULL);
    print_test("La cola está vacía", cola_esta_vacia(cola2));
    print_test("La cola no tiene elementos", cola_ver_primero(cola2) == NULL);

    //------------------------------------------------------------------

    //Creo dos variables dinámicas
    void* entero_dinamico = crear_entero_dinamico();
    void* caracter_dinamico = crear_caracter_dinamico();

    //Encolo las variables
    cola_encolar(cola2, entero_dinamico);
    cola_encolar(cola2, caracter_dinamico);

    //Paso la función destruir
    cola_destruir(cola2, destruir_dato);
    print_test("Prueba destruir cola sin elementos",true);

}

void pruebas_cola_alumno(void){

    pruebas_crear_cola();
    pruebas_volumen();
    prueba_encola_arreglos();
    prueba_destruir_valor_dinamico();
}