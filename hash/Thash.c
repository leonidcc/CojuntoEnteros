// ****************************************
// implementacion por leonid chancC
// ****************************************

#include <stdio.h>
#include <malloc.h>
#include "Thash.h"

// Se puede modificar para obtener mejores resultados
// menos coliciones
int fhash(char* key,int capacidad){
  unsigned int hash = 5381;
  int c;
  while (c = *key++)
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash%capacidad;
}

THash th_crear(int capacidad,funcionHash fh){
  THash th=malloc(sizeof(TH));
  th->tabla=malloc(sizeof(BSTree)*capacidad);
  th->capacidad=capacidad;
  th->hash1=fh;
  for(int i=0; i<capacidad; i++){
    th->tabla[i] = bstree_crear();
  }
  return th;
}

void th_insertar(THash th,char* key,void* dato){
    int index = th->hash1(key,th->capacidad);
    th->tabla[index] = bstree_insertar(th->tabla[index],key,dato);
}

void th_eliminar(THash th,char* key,visitante f){
  int index = th->hash1(key,th->capacidad);
  th->tabla[index] = bstree_eliminar(th->tabla[index],key,f);
}

void* th_buscar(THash th,char* key){
  int index = th->hash1(key, th->capacidad);
  // Nodo* n = bstree_buscar(th->tabla[index], key);
  // if(n != NULL) return n->dato;
  // else return n;
  return bstree_buscar(th->tabla[index], key);
}

void th_destruir(THash th, visitante f){
  int capacidad = th->capacidad;
  for(int i=0; i<capacidad; i++){
    bstree_destruir(th->tabla[i],f);
  }
  free(th->tabla);
  free(th);
}

void th_recorrer(THash th,visitante f){
  int capacidad = th->capacidad;
  for(int i=0; i<capacidad; i++){
    bstree_recorrer(th->tabla[i],f);
  }
}

void th_distribution_print(THash th){
  int capacidad = th->capacidad;
  for(int i=0; i<capacidad; i++){
    printf("index:%d ",i);
    printf(" nelems:%d\n", bstree_nelems(th->tabla[i]));
  }
}
