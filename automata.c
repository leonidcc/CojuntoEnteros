// ****************************************
// implementacion por leonid chancC
// ****************************************

#include <string.h>
#include "automata.h"

int  autm_is_imprimir(char* cmd){
  int i=0;
  autm_is_imprimir_q0(cmd,&i);
  return i;
}
void autm_is_imprimir_q0(char* cmd,int* i) {
    if(cmd[(*i)]=='i')(*i)++; else return;
    if(cmd[(*i)]=='m')(*i)++; else return;
    if(cmd[(*i)]=='p')(*i)++; else return;
    if(cmd[(*i)]=='r')(*i)++; else return;
    if(cmd[(*i)]=='i')(*i)++; else return;
    if(cmd[(*i)]=='m')(*i)++; else return;
    if(cmd[(*i)]=='i')(*i)++; else return;
    if(cmd[(*i)]=='r')(*i)++; else return;
    if(cmd[(*i)]==' '){(*i)++; is_alias_q0(cmd,i);}
}

// =====================
int autm_is_cnj_cmp(char* cmd){
  int i=0;
  autm_is_cnj_cmp_q00(cmd,&i);
  return i;
}
void autm_is_cnj_cmp_q00(char* cmd,int* i) {
    if(cmd[(*i)]=='{')(*i)++; else return;
    if(cmd[(*i)]=='x')(*i)++; else return;
    if(cmd[(*i)]==' ')(*i)++; else return;
    if(cmd[(*i)]==':')(*i)++; else return;
    if(cmd[(*i)]==' '){(*i)++; autm_is_cnj_cmp_q0(cmd,i);}
}

void autm_is_cnj_cmp_q6(char* cmd,int* i) {
    if(cmd[(*i)] == ' ' || cmd[(*i)] == '\n' || cmd[(*i)] == '\0' ) {(*i)++; autm_acc(cmd, i);}
}
void autm_is_cnj_cmp_q5(char* cmd,int* i) {
    if(cmd[(*i)]>= 49 && cmd[(*i)]<=57){(*i)++; autm_is_cnj_cmp_q4(cmd,i);}  // in {1-9}
}
void autm_is_cnj_cmp_q4(char* cmd,int* i) {
    if(cmd[(*i)]>= 48 && cmd[(*i)]<=57){(*i)++; autm_is_cnj_cmp_q4(cmd,i);}  // in {0-9}
    else if(cmd[(*i)]=='}'){(*i)++;autm_is_cnj_cmp_q6(cmd,i);}  // }
}
void autm_is_cnj_cmp_q3(char* cmd,int* i) {
    if(cmd[(*i)]>= 48 && cmd[(*i)]<=57){(*i)++; autm_is_cnj_cmp_q4(cmd,i);}  // in {0-9}
    else if(cmd[(*i)]=='-'){(*i)++;autm_is_cnj_cmp_q5(cmd,i);}  // -
}

void autm_is_cnj_cmp_q2(char* cmd,int* i) {
    if(cmd[(*i)]>= 48 && cmd[(*i)]<=57){(*i)++; autm_is_cnj_cmp_q2(cmd,i);}  // in {0-9}

    if(cmd[(*i)]==' ')(*i)++; else return;
    if(cmd[(*i)]=='<')(*i)++; else return;
    if(cmd[(*i)]=='=')(*i)++; else return;
    if(cmd[(*i)]==' ')(*i)++; else return;
    if(cmd[(*i)]=='x')(*i)++; else return;
    if(cmd[(*i)]==' ')(*i)++; else return;
    if(cmd[(*i)]=='<')(*i)++; else return;
    if(cmd[(*i)]=='=')(*i)++; else return;
    if(cmd[(*i)]==' '){(*i)++; autm_is_cnj_cmp_q3(cmd,i);}
}
void autm_is_cnj_cmp_q1(char* cmd,int* i) {
    if(cmd[(*i)]>= 49 && cmd[(*i)]<=57){(*i)++; autm_is_cnj_cmp_q2(cmd,i);}  // in {1-9}
}
void autm_is_cnj_cmp_q0(char* cmd,int* i) {
    if(cmd[(*i)]>= 48 && cmd[(*i)]<=57){(*i)++; autm_is_cnj_cmp_q2(cmd,i);}  // in {0-9}
    else if(cmd[(*i)]=='-'){(*i)++; autm_is_cnj_cmp_q1(cmd,i);}
}

// =====================
int autm_is_cnj_ext(char* cmd){
  int i=0;
  autm_is_cnj_ext_q00(cmd,&i);
  return i;
}
void autm_is_cnj_ext_q4(char* cmd,int* i) {
    if(cmd[(*i)] == ' ' || cmd[(*i)] == '\n' || cmd[(*i)] == '\0' ) {(*i)++; autm_acc(cmd, i);}
}
void autm_is_cnj_ext_q3(char* cmd,int* i) {
    if(cmd[(*i)]=='-'){(*i)++; autm_is_cnj_ext_q1(cmd,i);}  // in {"-"}
    else if(cmd[(*i)]>= 48 && cmd[(*i)]<=57){(*i)++; autm_is_cnj_ext_q2(cmd,i);}  // in {0-9}
}
void autm_is_cnj_ext_q2(char* cmd,int* i) {
    if(cmd[(*i)]==','){(*i)++; autm_is_cnj_ext_q3(cmd,i);}  // in {"-"}
    else if(cmd[(*i)]>= 48 && cmd[(*i)]<=57){(*i)++; autm_is_cnj_ext_q2(cmd,i);}  // in {0-9}
    else if(cmd[(*i)]=='}'){(*i)++; autm_is_cnj_ext_q4(cmd,i);}  // in {" "}
}

void autm_is_cnj_ext_q1(char* cmd,int* i) {
    if(cmd[(*i)]>= 49 && cmd[(*i)]<=57){(*i)++; autm_is_cnj_ext_q2(cmd,i);}  // in {1-9}
}
void autm_is_cnj_ext_q0(char* cmd,int* i) {
    if(cmd[(*i)]=='-'){(*i)++; autm_is_cnj_ext_q1(cmd,i);}  // in {"-"}
    else if(cmd[(*i)]>= 48 && cmd[(*i)]<=57){(*i)++; autm_is_cnj_ext_q2(cmd,i);}  // in {0-9}
    else if(cmd[(*i)]=='}'){(*i)++; autm_is_cnj_ext_q4(cmd,i);}  // in {" "}
}

void autm_is_cnj_ext_q00(char* cmd,int* i) {
    if(cmd[(*i)]=='{'){(*i)++; autm_is_cnj_ext_q0(cmd,i);}  // in {" "}
}

// =====================
int autm_is_operation(char* cmd){
  if (cmd[0] != '=' && cmd[0] != '&' && cmd[0] != '|' && cmd[0] != '-') return 0;
  if (cmd[1] != ' ' &&  cmd[1] != '\n' && cmd[1] != '\0') return 1;
  return -2;
}

// =====================
int autm_is_alias(char* cmd){
  int i=0;
  is_alias_q0(cmd,&i);
  return i;
}

void is_alias_q2(char* cmd,int* i) {
    if(cmd[(*i)] >=  48 && cmd[(*i)] <= 57) {(*i)++; is_alias_q2(cmd, i);}  // in {0,1..9}
    else if(cmd[(*i)] == ' ' || cmd[(*i)] == '\n' || cmd[(*i)] == '\0' ) {(*i)++; autm_acc(cmd, i);}

}
void is_alias_q1(char* cmd,int* i) {
    if((cmd[(*i)] >=  65 && cmd[(*i)] <= 90) || (cmd[(*i)] >=  97 && cmd[(*i)] <= 122) )      {(*i)++; is_alias_q1(cmd, i);}  // in {A,B..Z}
    else if(cmd[(*i)] >=  48 && cmd[(*i)] <= 57) {(*i)++; is_alias_q2(cmd, i);}  // in {0,1..9}
    else if(cmd[(*i)] == ' ' || cmd[(*i)] == '\n' || cmd[(*i)] == '\0' ) {(*i)++; autm_acc(cmd, i);}
}
void is_alias_q0(char* cmd,int* i) {
    if(cmd[(*i)] >=  65 && cmd[(*i)] <= 90)  {(*i)++; is_alias_q1(cmd, i);}  // in {A,B..Z}
}

///
void autm_acc(char* cmd,int* i){
  (*i)*=-1;
}
