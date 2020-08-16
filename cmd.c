#include <string.h>
#include <stdio.h>
#include "cmd.h"



// OPERACIONES
// =======================================

void cmd_imprimir(THash dic, char* cmd){
  char str1[9], str2[100];
  sscanf(cmd, "%s %s", str1, str2);

  Nodo*  cjn = th_buscar(dic,str2);
  if(cjn != NULL)
    cnj_imprimir(cjn->dato);
  else
    interprete_undefined(str2);
 printf("\n");
}

void cmd_evaluar_complemento(THash dic, char* cmd){
  char var[10], b[2], alias[100];
  sscanf(cmd,"%s %s %s",var,b,alias);

  // buscamos el conjunto
  Nodo*  viejo = th_buscar(dic,alias+1);
  if(viejo == NULL ){
    interprete_undefined(alias);
    return;
  }

  // creamos el nuevo conjunto complemento
  CNJ nuevo = cnj_crear();
  nuevo = cnj_complemento(viejo->dato);

  // buscamos si existe un conjunto para la var a definir
  Nodo* temp = th_buscar(dic,var);
  if(temp != NULL ){ // ya ésta definido
    cnj_destruir(temp->dato);
    temp->dato = nuevo;
  }
  else th_insertar(dic,var,nuevo);
}


void cmd_evaluar_operacion(THash dic, char* cmd){
  char var[50],asig[2],alias1[50],op[2],alias2[50];
  sscanf(cmd,"%s %s %s %s %s",var, asig, alias1, op, alias2);

  // buscamos el conjunto
  Nodo*  op1 = th_buscar(dic,alias1);
  if(op1 == NULL ){
    interprete_undefined(alias1);
    return;
  }
  // buscamos el conjunto
  Nodo*  op2 = th_buscar(dic,alias2);
  if(op2 == NULL ){
    interprete_undefined(alias2);
    return;
  }

  // creamos el nuevo conjunto
  CNJ nuevo = cnj_crear();

  // realizamos la operacion entre op1 y op2
  if(strcmp(op,"|")== 0)
    nuevo = cnj_union(op1->dato,op2->dato);
  else if(strcmp(op,"&") == 0)
    nuevo = cnj_interseccion(op1->dato,op2->dato);
  else if(strcmp(op,"-") == 0)
    nuevo = cnj_resta(op1->dato,op2->dato);

  Nodo*  viejo = th_buscar(dic,var);
  if(viejo != NULL ){ // ya ésta definido
    cnj_destruir(viejo->dato);
    viejo->dato = nuevo;
  }
  else th_insertar(dic,var,nuevo);
}



void cmd_asignar_por_comprension(THash dic, char* cmd){
  char alias[50],b[10],init[100],end[100];
  sscanf(cmd,"%s %s %s %s %s %s %s %s %s",
              alias,b,b,b,init,b,b,b,end);
  end[strlen(end)] = '\0';

  CNJ nuevo = cnj_crear();
  nuevo = cnj_add(nuevo,init,end);

  // buscamos si existe un conjunto para la misma variable
  Nodo*  viejo = th_buscar(dic,alias);
  if(viejo != NULL ){ // ya ésta definido
    cnj_destruir(viejo->dato);
    viejo->dato = nuevo;
  }
  else th_insertar(dic,alias,nuevo);
}


void cmd_asignar_por_extencion(THash dic, char* cmd){
  char alias[50], asig[2], conjunto[1000];
  sscanf(cmd,"%s %s %s",alias,asig,conjunto);

  // creamos el nuevo conjunto
  CNJ nuevo = cnj_crear();
  int i = 1, j = 0;
  char numero[20];

  //insertamos los elementos
  if(conjunto[i] != '}'){
    while (conjunto[i] != '}'){
      if(conjunto[i] == ','){
        numero[j] = '\0';
        nuevo = cnj_add(nuevo,numero,numero);
        j=0;i++;
      }
      numero[j] = conjunto[i];
      i++;j++;
    }
    numero[j] = '\0';
    nuevo = cnj_add(nuevo,numero,numero);
  }

  // buscamos si existe un conjunto para el mismo alias
  Nodo*  viejo = th_buscar(dic,alias);
  if(viejo != NULL ){
    cnj_destruir(viejo->dato);
    viejo->dato = nuevo;
  }
  else th_insertar(dic,alias,nuevo);
}

///GENERAL
// =======================================
THash cmd_init(){
  return th_crear(100,fhash);
}

void cmd_limpiar(char* cmd){
  int i=0;
  int j=0;
  while (cmd[j]==' ')j++;
  while (cmd[j]!='\0') {
    if(cmd[j]!=' ' || (cmd[j]==' ' && cmd[j+1]!=' ')){
      cmd[i]=cmd[j];
      i++;
    }
    j++;
  }
  cmd[i]='\0';
}

void cmd_destruir(THash h){
  th_destruir(h,cnj_destruir);
}

//SALIDAS POR PANTALLA
// =======================================
void interprete_init(){
  printf("INTC-i, version 1.0 by Leonid Chancc,\e[36m?\e[0m for help\n");
}
void interprete_help(){
  printf("\n* Intérprete para operar con conjuntos numéricos\n");
  printf("* Utilizaremos la palabra ALIASX para denotar una cadena \n arbitraria y k para denotar un número entero arbitrario");
    printf("\e[36m \n\nDEFINICION \e[0m\n");
    printf("\e[36m  ALIAS = {k0,k1,...,kn} \e[0m \t conjunto definido por comprension \n");
    printf("\e[36m  ALIAS = {x: k0 <= x <= k1} \e[0m \t conjunto definido por extencion \n");
    printf("\e[36m  \e[0m\n");
    printf("\e[36m OPERACION \e[0m\n");
    printf("\e[36m  ALIAS1 = ALIAS2 | ALIAS3 \e[0m \t computa la unión de los conjuntos \n");
    printf("\e[36m  ALIAS1 = ALIAS2 & ALIAS3 \e[0m \t computa la interseción de los conjuntos \n");
    printf("\e[36m  ALIAS1 = ALIAS2 - ALIAS3 \e[0m \t computa la resta de los conjuntos \n");
    printf("\e[36m  ALIAS1 = ~ALIAS2 \e[0m \t\t computa el complemento del conjunto \n");
    printf("\e[36m  \e[0m\n");
    printf("\e[36m  imprimir ALIAS  \e[0m \t\t imprime  el conjunto \n");
    printf("\e[36m  cls  \e[0m \t\t\t Limpiar pantalla\n");
    printf("\e[36m  salir   \e[0m \t\t\t Salir del programa\n");
}
void interprete_cls(){
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}
void interprete_error(char* error,char* cmd,char* msj,int n){
  printf("\e[31m%s error:\e[0m %s",error,cmd);
  printf("              ");
  while (n!=0) {
    printf(" ");n--;
  }
  printf("\e[31m^~~~\e[0m %s",msj);
}
void interprete_undefined( char* var){
  printf("\e[33mUndefined error:\e[0m ");
  printf("no se encontro %s\n",var);
}



// VALIDACION
// =======================================

int cmd_validar_conjunto(char* cmd, char* msj){
  int res;
  if(cmd[1]=='x'){
    res =autm_is_cnj_cmp(cmd);
    if(res >=0 ){
      strcpy(msj,ERR_CJ_COM);
      return res;
    }
    return -4;
  }

  res = autm_is_cnj_ext(cmd);
  if(res >=0 ){
    strcpy(msj,ERR_CJ_EXT);
    return res;
  }
  return -5;

}

int cmd_validar_asignation(char* cmd, char* msj){
  int res=0;
  int indexError = 0;
  if(cmd[0]=='{'){
    res = cmd_validar_conjunto(cmd,msj);
    if(res >= 0) return res;
    else return res;
  }
  if(cmd[0] >=  65 && cmd[0] <= 90){
    res = autm_is_alias(cmd);
    if(res >=0 ){
      strcpy(msj,ERR_ALIAS);
      return res;
    }
    indexError += (res*-1);
    res = autm_is_operation(cmd+indexError);
    if(res >=0 ){
      strcpy(msj,ERR_CMD_DES);
      return indexError + res;
    }
    indexError += (res*-1);
    res = autm_is_alias(cmd+indexError);
    if(res >=0 ){
      strcpy(msj,ERR_ALIAS);
      return indexError + res;
    }
    return -3;
  }
  if(cmd[0]=='~'){
    res = autm_is_alias(cmd+1);
    if(res >=0 ){
      strcpy(msj,ERR_ALIAS);
      return res+1;
    }
    return -2;
  }
  strcpy(msj,ERR_AL_ASIG);
  return 0;
}

int cmd_validar(char* cmd, char* msj){
  int indexError = 0;
  int res;
  // IMPRIMIR ??
  if(cmd[0]=='i'){
    res = autm_is_imprimir(cmd);
    if(res >=0 ){
      strcpy(msj,ERR_EN_IMPR);
      return res;
    }
    else return -1; // comando Imprimir valido
  }
  // ACIGNACION ??
  if(cmd[0] >=  65 && cmd[0] <= 90){
    res = autm_is_alias(cmd);
    if(res >=0 ){
      strcpy(msj,ERR_ALIAS);
      return res;
    }

    indexError += (res*-1);
    // se puede implemetnar exclusivamente para el =
    res = autm_is_operation(cmd+indexError);
    if(res >=0 ){
      strcpy(msj,ERR_ASIGNA);
      return indexError + res;
    }
    indexError += (res*-1);

    res = cmd_validar_asignation(cmd+indexError,msj);
    if(res >= 0) return indexError + res;
    else return res;

  }
  strcpy(msj,ERR_CMD_I);
  return 0;
}
