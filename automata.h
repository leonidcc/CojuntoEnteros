// ****************************************
// implementacion por leonid chancC
// ****************************************

#ifndef __AUTOMATA_H__
#define __AUTOMATA_H__

// AUTOMATA aceptacion
void autm_acc(char* ,int* );

// AUTOMATA operation
int autm_is_operation(char*);

// AUTOMATA alias
int  autm_is_alias(char*);
void is_alias_q0(char*,int*);
void is_alias_q1(char*,int*);
void is_alias_q2(char*,int*);

// AUTOMATA conjunto por extencion
int autm_is_cnj_ext(char*);
void autm_is_cnj_ext_q00(char*,int*);
void autm_is_cnj_ext_q0(char*,int*);
void autm_is_cnj_ext_q1(char*,int*);
void autm_is_cnj_ext_q2(char*,int*);
void autm_is_cnj_ext_q3(char*,int*);
void autm_is_cnj_ext_q4(char*,int*);

// AUTOMATA  conjunto por comprension
int autm_is_cnj_cmp(char*);
void autm_is_cnj_cmp_q00(char*,int*);
void autm_is_cnj_cmp_q0(char*,int*);
void autm_is_cnj_cmp_q1(char*,int*);
void autm_is_cnj_cmp_q2(char*,int*);
void autm_is_cnj_cmp_q3(char*,int*);
void autm_is_cnj_cmp_q4(char*,int*);
void autm_is_cnj_cmp_q5(char*,int*);

//AUTOMATA ccomanddo imprimir
int  autm_is_imprimir(char*);
void  autm_is_imprimir_q0(char*,int*);

#endif /* __AUTOMATA_H__ */
