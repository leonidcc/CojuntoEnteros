// ****************************************
// implementacion por leonid chancC
// ****************************************

#ifndef __OPERACION_H__
#define __OPERACION_H__

#include "conjuntoTree.h"

typedef CNJtree CNJ; // para mejor comprension

// long int es el long de 32 bits
#define INFPOSSTR "2147483647"
#define INFNEGSTR "-2147483648"

// mantener S representa el numero fuera de rango
#define MSJRANGO  "fuera de rango %s\n"


// Salidas por pantalla
//*********************

// imprimri un intervalo [x,Y]
void mostrar_intevalo(int x,int y);

// recorre el arbol inorder aplicando mostrar_intevalo a cada elemento
void cnj_imprimir(CNJ a);


// Auxiliares
//*********************
// retorna 1 si el string n es un numero dentro del rango [INFNEGSTR:INFPOSSTR]
// ademas imprime en pantalla MSJ_RANGO si este esta fuera del rango
int n_range_validar(char* n);

// determina si un conjunto es vacio
int cnj_es_vacio(CNJ a);

// Conjuntos
// *********
// Todas las operaciones retornan un nuevo conjunto

// crear un conjunto vacio
CNJ cnj_crear();

// añade el elemnto [i,f] al conjunto
CNJ cnj_add(CNJ a,char* i,char* f);

// Operaciones entre conjuntos
CNJ cnj_union(CNJ a,CNJ b);
CNJ cnj_interseccion(CNJ a,CNJ b);
CNJ cnj_resta(CNJ a,CNJ b);
CNJ cnj_complemento(CNJ a);

void cnj_destruir(void* c);

#endif /* __OPERACION_H__ */
