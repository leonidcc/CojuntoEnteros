// ****************************************
// implementacion por leonid chancC
// ****************************************
#include <stdio.h>
#include <malloc.h>
#include "conjuntoTree.h"

// Arbol binario de intervalos
// ***************************
CNJtree cnjtree_crear(){
  return NULL;
}


int cnjtree_es_vacio(CNJtree t){
  return t == NULL;
}


void cnjtree_recorrer(CNJtree t,visit f){
  if(t != NULL){
    cnjtree_recorrer(t->left, f);
    f(t->start,t->end);
    cnjtree_recorrer(t->right, f);
  }
}


CNJNodo* cnjtree_nodo_crear(int start,int end){
  CNJNodo* n = malloc(sizeof(CNJNodo));
  n->start = start;
  n->end = end;
  n->left = NULL;
  n->right = NULL;
  return n;
}



// INSERTAR
CNJtree cnjtree_min_left(CNJtree t){
  if(t==NULL)
    return NULL;
  else if(t->left != NULL)
    return cnjtree_min_left(t->left);
  return t;
}


CNJtree cnjtree_max_right(CNJtree t){
  if(t==NULL)
    return NULL;
  else if(t->right != NULL)
    return cnjtree_max_right(t->right);
  return t;
}


// implementacion anterior
/////////////////////////////////////////////////////////////////
CNJtree cnjtree_consumir_left(CNJtree t,int start, int* p){
  CNJtree temp = cnjtree_max_right(t);
  while (temp != NULL && start < temp->start ) {
    t = cnjtree_eliminar(t,temp->start,temp->end);
    temp = cnjtree_max_right(t);
  }

  if(temp != NULL && start <= temp->end){
    (*p) = temp->start;
    return cnjtree_eliminar(t,temp->start,temp->end);
  }
  else{
    (*p) = start;
    return t;
  }
}

CNJtree cnjtree_consumir_right(CNJtree t,int end, int* p){
  CNJtree temp = cnjtree_min_left(t);

  while (temp != NULL && end > temp->end ) {
    t = cnjtree_eliminar(t,temp->start,temp->end);
    temp = cnjtree_min_left(t);
  }

  if(temp != NULL && end >= temp->start){
    (*p) = temp->end;
    return cnjtree_eliminar(t,temp->start,temp->end);
  }
  else{
    (*p) = end;
    return t;
  }
}

// implementacion actual
/////////////////////////////////////////////////////////////////
CNJtree cnjtree_destruir_menores(CNJtree t,int n){
  // Arbol NULL
  if(t == NULL) return NULL;
  if(t->end < n){
    cnjtree_destruir(t->left);
    free(t);
    t = cnjtree_destruir_menores(t->right,n);
  }
  else if(n < t->start){
    t->left = cnjtree_destruir_menores(t->left,n);
  }
  else{
    cnjtree_destruir(t->left);
    t->left = NULL;
  }
  return t;
}

CNJtree cnjtree_consumir_right_v2(CNJtree t,int end, int* p){
  t = cnjtree_destruir_menores(t,end);

  CNJtree temp = cnjtree_min_left(t);
  if(temp != NULL && end >= temp->start){
    (*p) = temp->end;
    return cnjtree_eliminar(t,temp->start,temp->end);
  }
  else{
    (*p) = end;
    return t;
  }
}



CNJtree cnjtree_destruir_mayores(CNJtree t,int n){
  // Arbol NULL
  if(t == NULL) return NULL;
  if(n < t->start){
    cnjtree_destruir(t->right);
    free(t);
    t = cnjtree_destruir_mayores(t->left,n);
  }
  else if(t->end < n){
    t->right = cnjtree_destruir_mayores(t->right,n);
  }
  else{
    cnjtree_destruir(t->right);
    t->right = NULL;
  }
  return t;
}

CNJtree cnjtree_consumir_left_v2(CNJtree t,int start, int* p){
  t = cnjtree_destruir_mayores(t,start);

  CNJtree temp = cnjtree_max_right(t);
  if(temp != NULL && start <= temp->end){
    (*p) = temp->start;
    return cnjtree_eliminar(t,temp->start,temp->end);
  }
  else{
    (*p) = start;
    return t;
  }
}




CNJtree cnjtree_insertar(CNJtree t, int start, int end){
  // Descartamos errores
  if((start == INFPOS  && end == INFPOS) ||
     (start == INFNEG && end == INFNEG))
    return t;
  if(start > end) return t;
  //podemos ingresar los datos
  if(t == NULL){
    CNJNodo* n = malloc(sizeof(CNJNodo));
    n->start = start;
    n->end = end;
    n->left = NULL;
    n->right = NULL;
    return n;
  }
  switch (interval_cmp(t->start,t->end,start,end)){
    case  2: t->right = cnjtree_insertar(t->right,start,end);
      break;
    case -2: t->left  = cnjtree_insertar(t->left,start,end) ;
      break;
    case  3: t->right = cnjtree_consumir_right_v2(t->right,end,&t->end);
      break;
    case -3: t->left  = cnjtree_consumir_left(t->left,start,&t->start);
      break;
    case -1: t->right = cnjtree_consumir_right(t->right,end,&t->end);
             t->left  = cnjtree_consumir_left(t->left,start,&t->start);
      break;
    case  1: return t;
    default: return NULL;
  }
}



// ELIMINAR
CNJtree cnjtree_eliminar(CNJtree t, int start, int end){
  if(t == NULL)
    return NULL;
  if(end > t->end)
    t->right = cnjtree_eliminar(t->right,start,end);
  else if(start < t->start)
    t->left = cnjtree_eliminar(t->left, start,end);
  else{
    // sin hijos
    if(t->left == NULL && t->right == NULL){
      // Destruimos el nodo
      free(t);
      return NULL;
    }
    // un hijo
    else if(t->left == NULL || t->right == NULL){
      CNJtree temp;
      if(t->left == NULL)
        temp = t->right;
      else
        temp = t->left;
      // Destruimos el nodo
      free(t);
      return temp;
    }
    // dos hijos
    else{
      CNJtree temp = cnjtree_min_left(t->right);

      t->start = temp->start;
      t->end = temp->end;
      t->right = cnjtree_eliminar(t->right ,start,end);
   }
  }
}

void cnjtree_destruir(CNJtree t){
  if(t != NULL){
    cnjtree_destruir(t->left);
    cnjtree_destruir(t->right);
    free(t);
  }
}



// BUSCAR

int cnjtree_pertenece(int start,int end){
  return 0;
}

// INTERVALO
int interval_cmp(int x1,int x2,int y1,int y2){
  if(x1<=x2 && y1<=y2){
    if(x1 <= y1 && y2 <= x2)
      return  1; // contenido
    if(y1 < x1  && x2 < y2 )
      return -1; // contiene
    // IMPORTANTE SE HIZO EL CAMBIO DE LOS SIGNO -1 y +1 para considerar los extremos
    if(x2 < ((y1 == INFNEG)? y1: y1-1))
      return  2; // a la derecha
    if((( y2 == INFPOS)? y2: y2+1) < x1)
      return -2; // a la izq
    if(x1<=y1 && x2<y2)
      return 3; //intercecado a la der
    return -3; //intersecado a la izq
  }
  return 0; //error
}
