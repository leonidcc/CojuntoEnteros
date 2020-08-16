// ****************************************
// implementacion por leonid chancC
// ****************************************

#include "BSTree.h"
#include <malloc.h>
#include <string.h>


// Arbol binario de busqueda
// *************************
BSTree bstree_crear(){
  return NULL;
}


Nodo* bstree_node_crear(char* key, void* dato){
  Nodo* n = malloc(sizeof(Nodo));
  n->key = malloc(sizeof(char) * strlen( key ) + 1); // memoria para al key
  strcpy(n->key, key);
  n->dato = dato;
  n->left = NULL;
  n->right = NULL;
  n->height = 0;
  return n;
}


BSTree bstree_insertar(BSTree t, char* key,void* dato){

  // insertar nodo BSTree normal
  if(t == NULL)
    return bstree_node_crear(key,dato);

  if(strcmp(key, t->key) < 0)
    t->left = bstree_insertar(t->left, key, dato);

  else if (strcmp(key, t->key) > 0)
    t->right = bstree_insertar(t->right, key, dato);

  else // no se permite claves  duplicadas
    return t;

  // Actualizamos las alturas
  t->height = 1  + max(bstree_height(t->left),bstree_height(t->right));

  // Obtenemos el factor de balance
  int fb = bstree_balance_factor(t);
  // balanceamos si es necesario
  if(fb > 1 || fb < -1){
    // Left Left Case 1
    if (fb > 1 && (strcmp(key,t->left->key) < 0))
        return bstree_rightRotate(t);

    // Right Right Case 4
    if (fb < -1 && (strcmp(key, t->right->key) > 0))
        return bstree_leftRotate(t);

    // Left Right Case 2
    if (fb > 1 && (strcmp(key, t->left->key) > 0)){
        t->left =  bstree_leftRotate(t->left);
        return bstree_rightRotate(t);
    }

    // Right Left Case 3
    if (fb < -1 && (strcmp(key,t->right->key) < 0)){
        t->right = bstree_rightRotate(t->right);
        return bstree_leftRotate(t);
    }

  }
  return t;
}


BSTree bstree_min_left(BSTree t){
  if(t==NULL)
    return NULL;
  else if(t->left != NULL)
    return bstree_min_left(t->left);
  return t;
}


BSTree bstree_eliminar(BSTree t, char* key,visitante fDataElim){

  // eliminar nodo BSTree normal
  if(t == NULL)
    return NULL;

  if(strcmp(key, t->key) < 0)
    t->left = bstree_eliminar(t->left, key ,fDataElim);

  else if(strcmp(key, t->key) > 0)
    t->right = bstree_eliminar(t->right, key, fDataElim);

  else{
    // sin hijos
    if(t->left == NULL && t->right == NULL){
      // Destruimos el nodo
      fDataElim(t->dato);
      free(t->key);
      free(t);
      return NULL;
    }
    // un hijo
    else if(t->left == NULL || t->right == NULL){
      Nodo* temp;
      if(t->left == NULL)
        temp = t->right;
      else
        temp = t->left;
      // Destruimos el nodo
      fDataElim(t->dato);
      free(t->key);
      free(t);
      return temp;
    }
    // dos hijos
    else{
      Nodo* temp = bstree_min_left(t->right);
      void* swp;
      // Intercambiamos dato
      swp = t->dato;
      t->dato = temp->dato;
      temp->dato = swp;

      // Intercambiamos clave
      swp = t->key;
      t->key = temp->key;
      temp->key = swp;

      t->right = bstree_eliminar(t->right, key, fDataElim);
    }
  }

  // si el arbol tiene un solo nodo
  if(t == NULL)
    return NULL;

  // Actualizamos las alturas
  t->height = 1  + max(bstree_height(t->left),bstree_height(t->right));

  // Obtenemos el factor de balance
  int fb = bstree_balance_factor(t);
  // balanceamos si es necesario
  if(fb > 1 || fb < -1){
    // Left Left Case 1
    if (fb > 1 && (strcmp(key,t->left->key) < 0))
        return bstree_rightRotate(t);

    // Right Right Case 4
    if (fb < -1 && (strcmp(key, t->right->key) > 0))
        return bstree_leftRotate(t);

    // Left Right Case 2
    if (fb > 1 && (strcmp(key, t->left->key) > 0)){
        t->left =  bstree_leftRotate(t->left);
        return bstree_rightRotate(t);
    }

    // Right Left Case 3
    if (fb < -1 && (strcmp(key,t->right->key) < 0)){
        t->right = bstree_rightRotate(t->right);
        return bstree_leftRotate(t);
    }

  }
  return t;
}


Nodo* bstree_buscar(BSTree t, char* key){
  if(t == NULL || (strcmp(t->key, key) == 0)){
    return t;
  }
  else if(strcmp(key, t->key) < 0)
    return bstree_buscar(t->left, key);
  else
    return bstree_buscar(t->right, key);
}


void bstree_recorrer(BSTree t, visitante f){
  if(t != NULL){
    bstree_recorrer(t->left,f);
    f(t->dato);
    bstree_recorrer(t->right,f);
  }
}


void bstree_destruir(BSTree t, visitante fDataElim){
  if(t != NULL){
    bstree_destruir(t->left,fDataElim);
    bstree_destruir(t->right,fDataElim);
    fDataElim(t->dato);
    free(t->key);
    free(t);
  }
}


int bstree_nelems(BSTree t){
  if(t!=NULL){
    return bstree_nelems(t->left)+bstree_nelems(t->right)+1;
  }
  return 0;
}



// Funciones de balanceo
// *************************
int bstree_height(BSTree t){
  if (t == NULL)
    return -1;
  return t->height;
}


//Valanceo INIT
int bstree_balance_factor(BSTree t){
  if(t == NULL)
    return -1;
  return bstree_height(t->left) - bstree_height(t->right);
}


// rotacion a la derecha
BSTree bstree_rightRotate(BSTree a){
  BSTree b = a->left;
  BSTree t2 = b->right;

  // rotamos
  b->right = a;
  a->left = t2;

  // Actualizamos las alturas
  a->height = max(bstree_height(a->left), bstree_height(a->right)) + 1;
  b->height = max(bstree_height(b->left), bstree_height(b->right)) + 1;

  return b;
}


// Rotacíon a la izquierda
BSTree bstree_leftRotate(BSTree a){
  BSTree b = a->right;
  BSTree t2 = b->left;

  // rotamos
  b->left = a;
  a->right = t2;

  // Actualizamos las alturas
  a->height = max(bstree_height(a->left), bstree_height(a->right)) + 1;
  b->height = max(bstree_height(b->left), bstree_height(b->right)) + 1;

  return b;
}


// Funciones auxiliares
// ********************
int max(int a, int b){
  return (a > b)? a : b;
}
