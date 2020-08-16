// ****************************************
// implementacion por leonid chancC
// ****************************************
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operacion.h"

// Salidas por pantalla
//*********************
void mostrar_intevalo(int x,int y){
  if(x == y){
    printf("%d ",x);
  }
  else{
    (x == -2147483648)? printf("-OO:"): printf("%d:",x);
    (y == 2147483647)? printf("+OO"): printf("%d ",y);
  }
}


void cnj_imprimir(CNJ a){
  if(cnj_es_vacio(a))
    printf("{}");
  else cnjtree_recorrer(a,mostrar_intevalo);
}



// Auxiliares
//*********************
int n_range_validar(char* n){
  int solv = 0;
  if(n[0] == '-'){
    if(strlen(n+1)<10) solv = 1;
    else if((strlen(n+1)==10) && strcmp(n+1, INFNEGSTR) <= 0) solv = 1;
  }
  else{
    if(strlen(n) < 10) solv =  1;
    else if ((strlen(n) == 10) && strcmp(n, INFPOSSTR) <= 0) solv = 1;
  }
  (solv)?:printf(MSJRANGO, n);

  return solv;
}

int cnj_es_vacio(CNJ a){
  return cnjtree_es_vacio(a);
}



// Conjuntos
// *********

CNJ cnj_crear(){
  return cnjtree_crear();
}


CNJ cnj_add(CNJ a,char* i,char* f){
  if(n_range_validar(i) && n_range_validar(f))
    return cnjtree_insertar(a,atoi(i),atoi(f));
  return a;
}

// *
// * UNION ====================================
// *
void recorrer_for_union(CNJtree t,CNJtree* n){
  if(t != NULL){
    recorrer_for_union(t->left,n);
    *n = cnjtree_insertar(*n,t->start,t->end);
    recorrer_for_union(t->right,n);
  }
}
CNJ cnj_union(CNJ a,CNJ b){
  CNJtree c = cnjtree_crear();
  recorrer_for_union(a,&c);
  recorrer_for_union(b,&c);
  return c;
}

// *
// * INTERSECCION ============================
// *

typedef struct SNodo{
  CNJ dato;
  struct SNodo* next;
}SNodo;
typedef SNodo* SList;

SList slist_crear(){
  return NULL;
}

SList slist_add_init(SList l,CNJ dato){
  SNodo* n = malloc(sizeof(SNodo));
  n->dato = dato;
  n->next = l;
  return n;
}

void slist_destruir(SList l){
  SList elim;
  for (; l != NULL;){
    elim = l;
    l = l->next;
    free(elim);
  }
}

void recorrer_for_interseccion(CNJ a,SList* l){
  if(a != NULL){
    recorrer_for_interseccion(a->right,l);
    *l =slist_add_init(*l,a);
    recorrer_for_interseccion(a->left,l);
  }
}

CNJ cnj_interseccion(CNJ a,CNJ b){
  CNJ c = cnj_crear();
  SList c1 = slist_crear();
  SList c2 = slist_crear();
  recorrer_for_interseccion(a,&c1);
  recorrer_for_interseccion(b,&c2);

  SList temp;
  for (;c2 != NULL && c1 != NULL;) {

    switch (interval_cmp(c1->dato->start,c1->dato->end,c2->dato->start,c2->dato->end)) {
      case  2:
        temp = c1;
        c1 = c1->next;
        break;

      case -2:
        temp = c2;
        c2 = c2->next;
        break;

      case  3:
        c = cnjtree_insertar(c,c2->dato->start,c1->dato->end);
        temp = c1;
        c1 = c1->next;
        break;

      case -3:
        c = cnjtree_insertar(c,c1->dato->start,c2->dato->end);
        temp = c2;
        c2 = c2->next;
        break;

      case  1:
        c = cnjtree_insertar(c,c2->dato->start,c2->dato->end);
        temp = c2;
        c2=c2->next;
        break;

      case -1:
        c = cnjtree_insertar(c,c1->dato->start,c1->dato->end);
        temp = c1;
        c1 = c1->next;
        break;
    }
    free(temp);
  }

  slist_destruir(c1);
  slist_destruir(c2);
  return c;
}

// *
// * RESTA ============================
// *

CNJ cnj_resta(CNJ a,CNJ b){
  CNJ com = cnj_complemento(b);
  CNJ resta = cnj_interseccion(a,com);
  cnj_destruir(com);
  return resta;
}


// *
// * COMPLEMTO ============================
// *
int fant(int n){
  if(n == INFNEG) return INFNEG;
  if(n == INFPOS) return INFPOS;
  return n-1;
}
int fsig(int n){
  if(n == INFNEG) return INFNEG; // explciar porque los 2
  if(n == INFPOS) return INFPOS;
  return n+1;
}

void recorrer_for_complemento(CNJtree c,int* ant,CNJtree* n){
  if(c!= NULL){
    recorrer_for_complemento(c->left,ant,n);
    *n = cnjtree_insertar(*n,fsig((*ant)),fant(c->start));
    *ant= c->end;
    recorrer_for_complemento(c->right,ant,n);
  }
}

CNJ cnj_complemento(CNJ a){
    int ant = INFNEG;
    CNJtree c = cnjtree_crear();
    recorrer_for_complemento(a,&ant,&c);
    c = cnjtree_insertar(c,fsig(ant),fant(2147483647));
    return c;
}


// /DESTRUIR
void cnj_destruir(void* c){
  cnjtree_destruir(c);
}
