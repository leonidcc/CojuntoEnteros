// ****************************************
// implementacion por leonid chancC
// ****************************************

#ifndef __CMD_H__
#define __CMD_H__

#include "automata.h" // requerido para poder identificar las palabras de cmd
#include "hash/Thash.h"
#include "conjuntos/operacion.h"

// COMANDO
// =======================================

void cmd_destruir(THash h);

THash cmd_init();
int cmd_validar(char*,char*);
void cmd_limpiar(char* cmd);

void cmd_imprimir(THash dic, char* cmd);
void cmd_evaluar_complemento(THash dic, char* cmd);

void cmd_evaluar_operacion(THash dic, char* cmd);

void cmd_asignar_por_comprension(THash dic, char* cmd);

void cmd_asignar_por_extencion(THash dic, char* cmd);


// VALIDACION
// =======================================
/*
Valida si el comando es correcto
retorna:
  -1: cmd tipo imprimir
  -2: cmd tipo evaluar_complemento
  -3: cmd tipo evaluar_operacion
  -4: cmd tipo asignar_por_comprension
  -5: cmd tipo asignar_por_extencion
   n >= 0: si el comando es invalido y n es el indice del primer error.
  ademas de copiar un msj de error en {msjError}
*/
// Puede personalizar los msj de error para una mejor comprension
#define ERR_CJ_COM  "hint: revisar notacion de cjt. por comprension \n"
#define ERR_CJ_EXT  "hint: con ?,revisar notacion de cjt. por extencion \n"
#define ERR_ALIAS   "hint: Mayusculas con terminacion en numero\n"
#define ERR_CMD_DES "hint: inténte con |, &, - \n"
#define ERR_AL_ASIG "hint: un ~, <ALIAS> o un conjunto\n"
#define ERR_EN_IMPR "hint: imprimir <ALIAS>\n"
#define ERR_ASIGNA  "hint: ' = '\n"
#define ERR_CMD_I   "hint: con mayuscula\n"
int cmd_validar(char* cmd, char* msjError);


//SALIDAS POR PANTALLA
// =======================================

void interprete_init();
void interprete_help();
void interprete_cls();
void interprete_error(char*,char*,char*,int);
void interprete_undefined( char* var);



#endif /* __CMD_H__ */
