#include <stdio.h>
#include <malloc.h>
#include "Thash.h"


// Estructura dato
// ==================
typedef struct _Elem{
  int n;
}*Elem;

Elem elem_crear(int n){
  Elem e= malloc(sizeof(struct _Elem));
  e->n=n;
}
void elem_destroy(void* e){
  free(e);
}
void elem_mostrar(void* e){
  if(e == NULL){
    printf("null\n");
  }
  else{
    Elem dat = (Elem)e;
    printf("%d ",dat->n);
  }
}


int main(int argc, char const *argv[]) {
  // BSTree t0 = bstree_crear();
  // t0 = bstree_insertar(t0,"20",elem_crear(20));
  // t0 = bstree_insertar(t0,"21",elem_crear(21));
  // t0 = bstree_insertar(t0,"22",elem_crear(22));
  // t0 = bstree_insertar(t0,"23",elem_crear(23));
  // t0 = bstree_insertar(t0,"24",elem_crear(24));
  // t0 = bstree_insertar(t0,"25",elem_crear(25));
  // t0 = bstree_insertar(t0,"10",elem_crear(10));
  // bstree_recorrer(t0,elem_mostrar);
  // printf(" h:%d ",bstree_height(t0));
  //
  // BSTree t1 = bstree_crear();
  // t1 = bstree_insertar(t1,"50",elem_crear(50));
  // t1 = bstree_insertar(t1,"60",elem_crear(60));
  // t1 = bstree_insertar(t1,"70",elem_crear(70));
  // t1 = bstree_insertar(t1,"80",elem_crear(80));
  // t1 = bstree_insertar(t1,"90",elem_crear(90));
  // t1 = bstree_insertar(t1,"91",elem_crear(91));
  // // t1 = bstree_insertar(t1,"130",elem_crear(11));
  // bstree_recorrer(t1,elem_mostrar);
  // printf(" h:%d ",bstree_height(t1));
  // t1 = bstree_eliminar(t1, "60", elem_destroy);
  // t1 = bstree_eliminar(t1, "91", elem_destroy);
  // t1 = bstree_eliminar(t1, "70", elem_destroy);
  // bstree_recorrer(t1,elem_mostrar);
  // printf(" h:%d ",bstree_height(t1));

    THash h1=th_crear(3,fhash);
    th_insertar(h1, "leonid",elem_crear(10));
    th_insertar(h1, "chancc",elem_crear(10));
    th_insertar(h1, "jajaj",elem_crear(10));
    th_insertar(h1, "12345",elem_crear(10));
    th_insertar(h1, "leonisdfd",elem_crear(10000));
    th_insertar(h1, "chsdfancc",elem_crear(10));
    th_insertar(h1, "jasdfjaj",elem_crear(10));
    th_insertar(h1, "12sdf345",elem_crear(10));
    th_insertar(h1, "leosdfnifd",elem_crear(10));
    th_insertar(h1, "chaffncc",elem_crear(10));
    th_insertar(h1, "jaasfjaj",elem_crear(10));
    th_insertar(h1, "12fff345",elem_crear(10));

    elem_mostrar(th_buscar(h1,"leonisdfd"));
    th_distribution_print(h1);
    th_destruir(h1,elem_destroy);

  return 0;
}
