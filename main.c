#include <stdio.h>
#include <string.h>
#include "cmd.h"


#define PROOMT ">>> "
// 1296 lineas

int main(){

  int n;
  char cmd[1024];
  char msj[100]="\n";
  THash dic = cmd_init();

  interprete_init(); // imprime una presentacion

  while(printf(PROOMT), fgets(cmd, 1024, stdin)){

    cmd_limpiar(cmd); // Eliminamos los espacios que esten de mas

    if(!strcmp(cmd, "salir\n")){      // Salir del interprete
      cmd_destruir(dic);
      return 0;
    }
    else if (!strcmp(cmd, "?\n"))     // cmds del interprete
      interprete_help();

    else if (!strcmp(cmd, "cls\n")){  // limpiar pantalla
      interprete_cls();
      interprete_init();
    }
    else if (!strcmp(cmd, "\n")){     // limpiar pantalla
      continue ;
    }
    else{
      n = cmd_validar(cmd,msj);
      if( n >= 0 ) // Error de sintaxis en la posicion n
        interprete_error("Syntax",cmd,msj,n);
      else{
        switch (n) {
        case -1: cmd_imprimir(dic, cmd);break;
        case -2: cmd_evaluar_complemento(dic, cmd);break;
        case -3: cmd_evaluar_operacion(dic, cmd);break;
        case -4: cmd_asignar_por_comprension(dic, cmd);break;
        case -5: cmd_asignar_por_extencion(dic, cmd);break;
        }
      }
    }
  }
}


// // TEST MANUAL
// INTC-i, version 1.0 by Leonid Chancc,? for help
// >>> A = {0,1,2,3}
// ok
// >>> B = {x : -3 <= x <= 5}
// ok
// >>> C = {x : 3 <= x <= 7}
// ok
// >>> imprimir C
// 3:7
// >>> imprimir B
// -3:5
// >>> imprimir A
// 0:3
// >>> AB = A | B
// ok
// >>> BA = B | A
// ok
// >>> imprimir AB
// -3:5
// >>> imprimir BA
// -3:5
// >>> AIB = A & B
// ok
// >>> BIA = B & A
// ok
// >>> imprimir AIB
// 0:3
// >>> imprimir BIA
// 0:3
// >>> CA = C | A
// ok
// >>> CB = C | B
// ok
// >>> CAIB = C | AIB
// ok
// >>> CAICB = CA & CB
// ok
// >>> imprimir CAIB
// 0:7
// >>> imprimir CAICB
// 0:7
// >>> RESTA1 = A - B
// ok
// >>> RESTA2 = A - RESTA1
// ok
// >>> imprimir RESTA2
// 0:3
// >>> imprimir AIB
// 0:3
// >>> COMPA = ~A
// ok
// >>> COMPB = ~B
// ok
// >>> CAUCB = COMPA | COMPB
// ok
// >>> COMPAIB = ~AIB
// ok
// >>> imprimir COMPAIB
// -OO:-1 4:+OO
// >>> imprimir CAUCB
// -OO:-1 4:+OO
// >>> COMPA = ~A
// ok
// >>> COMPB = ~B
// ok
// >>> CAICB = COMPA & COMPB
// ok
// >>> COMPAB = ~AB
// ok
// >>> imprimir COMPAB
// -OO:-4 6:+OO
// >>> imprimir CAICB
// -OO:-4 6:+OO
// >>>

// SUPERADO
