// Projeto Final de ITP
// Alunos: ALLYSON GUSTAVO SILVA DO CARMO e RAQUEL BRENA SILVA DE LIMA

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// ------Nossas Dependencias------
#include "estruturas.h"
#include "funcoes.h"
// -------------------------------

int main() {
  CAMPO_MINADO campoMinado;
  
  alocarCampos(&campoMinado);
  inicializarTabuleiro(&campoMinado, 0, 0);

  //printTabuleiro(&campoMinado);
  
  //imprimirCampo(campoMinado , m, n, perdeu, ganhou);
  // jogo(&campoMinado, m, n, z, &perdeu, &ganhou);

  return 0;
}