// ****************************************
// implementacion por leonid chancC
// ****************************************

#ifndef __THASH_H__
#define __THASH_H__

#include "BSTree.h"

// Representacion de una estructura hash
// Se requiere la implemntacion de BStree
typedef int(*funcionHash)(char* key,int capacidad);
typedef struct{
  BSTree* tabla;
  int capacidad;
  int nelems;
  funcionHash hash1;
}TH;
typedef TH* THash;

// crea una structura hash
THash th_crear(int capacidad,funcionHash fh);

// inserta un elemento generico{dato} a la tabla hash
void th_insertar(THash th,char* key,void* dato);

// elimina un elemento generico de la tabla hash
// la fucion visitante{f} se debera de encargar de destruir el dato
void th_eliminar(THash th,char* key,visitante f);

// restorna el dato generico asociado a la clave{key}
void* th_buscar(THash th,char* key);

// detruye por completo la structura hash
// la fucion visitante{f} se debera de encargar de destruir el dato
void th_destruir(THash th,visitante f);

// aplica la funcion{f} a todos los elementos de la estructura hash
void th_recorrer(THash th,visitante f);

// funcion hash pode defecto
int fhash(char* key,int capacidad);


// Testeo
// imprime los indices y al la cantidad de elemtos para ese indice
void th_distribution_print(THash th);



#endif /* __THASH_H__ */
