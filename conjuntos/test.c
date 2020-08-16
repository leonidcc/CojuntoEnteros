#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operacion.h"

int main(int argc, char const *argv[]) {
  CNJ c1 = cnj_crear();
  CNJ c2 = cnj_crear();
  c1 = cnj_add(c1,"10","20");
  c1 = cnj_add(c1,"30","40");
  c1 = cnj_add(c1,"50","60");
  c1 = cnj_add(c1,"103","103");
  c1 = cnj_add(c1,"105","105");
  c2 = cnj_add(c2,"15","30");
  c2 = cnj_add(c2,"45","100");
  c2 = cnj_add(c2,"80","90");

  // cnj_imprimir(c1);printf("\n");
  // cnj_imprimir(c2);printf("\n");
  //
  // CNJ i = cnj_interseccion(c1,c2);
  // cnj_imprimir(i);printf("\n");
  // CNJ r = cnj_resta(c1,c2);
  // cnj_imprimir(r);printf("\n");


  CNJ i = cnj_interseccion(c1,c2);
  cnj_imprimir(i);printf("\n");

  // CNJ c1Uc2 = cnj_union(c1,c2);
  // cnj_imprimir(c1Uc2);printf("\n");
  //
  // CNJ con = cnj_complemento(c1Uc2);
  // // cnj_imprimir(con);printf("\n");
  cnj_destruir(c1);
  cnj_destruir(c2);
  cnj_destruir(i);
  // cnj_destruir(c1Uc2);
  // cnj_destruir(con);

  return 0;
}
