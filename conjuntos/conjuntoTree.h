
// ****************************************
// implementacion por leonid chancC
// ****************************************

#ifndef __CONJUNTOTREE_H__
#define __CONJUNTOTREE_H__

// long int es el long de 32 bits
#define INFPOS 2147483647
#define INFNEG 	-2147483648

// Representamos un conjunto de intevalos disjuntos
// [x,y] con x<=y con  un arbol de busqueda
typedef struct _CNJNodo{
  int start;
  int end;
  struct _CNJNodo* left;
  struct _CNJNodo* right;
}CNJNodo;
typedef CNJNodo* CNJtree;


typedef void (*visit)(int x, int y);

// Arbol binario de intervalos
// ***************************

// crea un CNJtre vacio
CNJtree cnjtree_crear();

// retorna 1 si el conjunto es vacio
int cnjtree_es_vacio(CNJtree t);

//recorre el arbol {t} inorder y aplica la funcion {f} a cada elemnto
void cnjtree_recorrer(CNJtree t,visit f);

// crear un nodo intervalo que representa [start,end]
CNJNodo* cnjtree_nodo_crear(int start,int end);


// INSERTAR

// auxiliares
CNJtree cnjtree_min_left(CNJtree t);
CNJtree cnjtree_max_right(CNJtree t);

// implementacion anterior
CNJtree cnjtree_consumir_left(CNJtree t,int start, int* p);
CNJtree cnjtree_consumir_right(CNJtree t,int end, int* p);

// implementacion actual
CNJtree cnjtree_destruir_menores(CNJtree t,int n);
CNJtree cnjtree_destruir_mayores(CNJtree t,int n);
CNJtree cnjtree_consumir_left_v2(CNJtree t,int start, int* p);
CNJtree cnjtree_consumir_right_v2(CNJtree t,int end, int* p);

// inserta el intervalo [start,end] en el arbol {t}
CNJtree cnjtree_insertar(CNJtree t, int start, int end);


// ELIMINAR
// Elimina el intervalo [star, end] del arbol{t}
CNJtree cnjtree_eliminar(CNJtree t, int start, int end);

// elimna un arbol por completo
void cnjtree_destruir(CNJtree t);



// BUSCAR
int cnjtree_pertenece(int start,int end);



// Funciones sobre los intervalos
// ******************************

/*
compara el intervalo A = [y1,y2] respecto el B = [x1,x2]
 retornando:
  1: si A ésta contenido en B
 -1: si A contiene a B
  2: si no existe interseccion, A esta a la derecha de B
 -2: si no existe interseccion, A ésta a la izquierda de B
  3: si existe interseccion, A ésta a la derecha de B
 -3: si existe interseccion, A ésta a la izquierda de B
  0: si x1 > x2 o y1 > y2
*/
int interval_cmp(int x1,int x2,int y1,int y2);



#endif /* __CONJUNTOTREE_H__ */
