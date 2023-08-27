#ifndef ESTRUTURAS_H_
#define ESTRUTURAS_H_

// Verdadeiro = 1    FALSO = 0
typedef enum boleano_t{
  FALSE = 0,
  TRUE = 1
}Boolean;

//Definindo nossa struct
// Criando um campo minado que contem o campo principal, campo Auxiliar e diferentes marcações de posições
typedef struct campo_minado_t{
    int **campoPrincipal;
    int **campoAuxiliar;
    int X_posicao;
    int Y_posicao;
}CAMPO_MINADO; 

#endif