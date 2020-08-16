// ****************************************
// implementacion por leonid chancC
// ****************************************

#ifndef __BSTREE_H__
#define __BSTREE_H__

// Nodo de un Bstree
typedef struct _Nodo{
  char* key;             // clave del dato tipo string
  void* dato;            // dato generico
  struct _Nodo* left;
  struct _Nodo* right;
  int height;
}Nodo;

typedef Nodo* BSTree;

// Funcion que permite operar con el tipo de dato geenrico
typedef void (*visitante)(void *d);


// Arbol binario de busqueda
// *************************
// crea un arbol vacio
BSTree bstree_crear();

// crea un nuevo nodo
Nodo* bstree_node_crear(char* key, void* dato);

// añade al arbol{t} un elemento{dato} generico asociado a la clave{key}
BSTree bstree_insertar(BSTree t, char* key,void* dato);

// retorna el nodo hoja izq del arbol
BSTree bstree_min_left(BSTree t);

// elimina del arbol{t} un elemento{dato} generico asociado a la clave{key}
// destruira el elemento de memoria con la funcion{f}
BSTree bstree_eliminar(BSTree t, char* key,visitante f);

// retorna el nodo del arbol{t} con clave{key}
Nodo* bstree_buscar(BSTree t, char* key);

// recorre el arbol{t} "inorder" y aplica la funcion{f} a cada elemento
void bstree_recorrer(BSTree t, visitante f);

// recorre "postOrden",destruye el arbol{t} de memoria
// y cada elemento con la funcion{f}
void bstree_destruir(BSTree t, visitante f);

// retorna la cantidad de elementos del arbol{t}
int bstree_nelems(BSTree t);


// Funciones de balanceado
// *************************
int bstree_height(BSTree t);

//Valanceo INIT
int bstree_balance_factor(BSTree t);

// rotacion a la derecha
BSTree bstree_rightRotate(BSTree a);

// Rotacíon a la izquierda
BSTree bstree_leftRotate(BSTree a);


// Funciones auxiliares
// ********************
// retorna el maximo entre dos enteros
int max(int a, int b);


#endif /* __BSTREE_H__ */
