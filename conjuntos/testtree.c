#include <stdio.h>
#include "conjuntoTree.h"

void mostrar_intevalo_test(int x,int y){
  if(x == y){
    printf("%d ",x);
  }
  else{
    (x == -2147483648)? printf("-OO:"): printf("%d:",x);
    (y == 2147483647)? printf("+OO"): printf("%d ",y);
  }
}

int main(int argc, char const *argv[]) {

  // Testeo cnjtree_consumir_right y left v2
  CNJtree a = cnjtree_crear();
  cnjtree_recorrer(a,mostrar_intevalo_test); printf("\n");

  // se insertan intervalos disjuntos
  a = cnjtree_insertar(a,10,20);
  a = cnjtree_insertar(a,110,120);
  a = cnjtree_insertar(a,50,60);
  a = cnjtree_insertar(a,30,40);
  a = cnjtree_insertar(a,90,100);
  a = cnjtree_insertar(a,70,90);
  cnjtree_recorrer(a,mostrar_intevalo_test); printf("\n");

  // original
  // 10:20 30:40 50:60 70:100 110:120

  // a = cnjtree_destruir_menores(a,0);
  // 10:20 30:40 50:60 70:100 110:120

  // a = cnjtree_destruir_menores(a,30);
  // 30:40 50:60 70:100 110:120

  // a = cnjtree_destruir_menores(a,29);
  // 30:40 50:60 70:100 110:120

  // a = cnjtree_destruir_menores(a,150);
  //

  // a = cnjtree_destruir_menores(a,45);
  // 50:60 70:100 110:120

  // a = cnjtree_destruir_mayores(a,0);
  //

  // a = cnjtree_destruir_mayores(a,30);
  // 10:20 30:40

  // a = cnjtree_destruir_mayores(a,29);
  // 10:20

  // a = cnjtree_destruir_mayores(a,150);
  // 10:20 30:40 50:60 70:100 110:120


  a = cnjtree_destruir_mayores(a,45);
  // 10:20 30:40

  cnjtree_recorrer(a,mostrar_intevalo_test); printf("\n");
  // Testeo cnjtree_consumir_right_v2
  cnjtree_destruir(a);

  return 0;
}
