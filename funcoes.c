#include "funcoes.h"
#include "constantes.h"
#include "estruturas.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void telainicial() {
  system("clear");
  printf("\n------------Campo Minado------------\n");
  printf("Desenvolvido por Raquel Brena e Allyson Gustavo");
}

void alocarCampos(CAMPO_MINADO *campoMinado) {
  campoMinado->campoPrincipal = malloc(sizeof(int *) * 10);
  campoMinado->campoAuxiliar = malloc(sizeof(int *) * 10);
  for (int i = 0; i < 10; i++) {
    campoMinado->campoPrincipal[i] = malloc(sizeof(int) * 20);
    campoMinado->campoAuxiliar[i] = malloc(sizeof(int) * 20);
  }
}

void inicializarTabuleiro(CAMPO_MINADO *campoMinado, int lin, int col) {
  printf("inicializando\n");
  
  while (lin < 10) {
    while (col < 20) {
      // printf("[%d][%d]\n", lin, col);
      campoMinado->campoAuxiliar[lin][col] = 0;
      campoMinado->campoPrincipal[lin][col] = 0;
      col++;
    }
    lin++;
    col = 0;
  }

  distribuirMinas(campoMinado, 40);
  distribuirQuantidades(campoMinado);

  /*if (lin < 10) {
    if (col < 20) {
      printf("%d ", campoMinado->campoPrincipal[lin][col]);
      col++;
    } else {
      printf ("\n");
      lin++;
      col = 0;
    }
  }*/
}

void distribuirMinas(CAMPO_MINADO *campoMinado, int BOMBAS) {
  srand(time(NULL));

  int randLinha;
  int randColuna;

  while (BOMBAS > 0) {
    randLinha = rand() % 10;  // Gerando n° aleatório entre 0 e 10
    randColuna = rand() % 20; // Gerando n° aleatório entre 0 e 20
    if (campoMinado->campoPrincipal[randLinha][randColuna] != MINA) {
      campoMinado->campoPrincipal[randLinha][randColuna] = MINA;
      BOMBAS--;
    }
  }
}

void imprimirElemento(CAMPO_MINADO campoMinado, int m, int n, int i, int j, Boolean perdeu, Boolean ganhou)
{
	if (i < m){
		if(j == n)  printf("|  %d", i+1);
		if (j < n){	
			if(j == 0)  printf("  %d  |", i+1);
			if(perdeu == TRUE)
				(campoMinado.campoPrincipal[i][j] == MINA) ? printf(" X ") :  printf(" %d ", campoMinado.campoPrincipal[i][j]);	
			else 
				if(ganhou == TRUE)
					(campoMinado.campoPrincipal[i][j] == MINA) ? printf(" * ") :  printf(" %d ", campoMinado.campoPrincipal[i][j]);	
				else 
					if(campoMinado.campoAuxiliar[i][j] == VAGA)  printf(" %d ", campoMinado.campoPrincipal[i][j]);
					else  
						if(campoMinado.campoAuxiliar[i][j] == VAGA)  printf(" * "); 
						else printf(" . "); 
			imprimirElemento(campoMinado, m, n, i, j + 1, perdeu, ganhou);
		}
		else{
			printf("\n                                      ");	
			imprimirElemento(campoMinado, m, n, i + 1 , 0, perdeu, ganhou);
		}	
	}	
}

//Impressão das Colunas
void Colunas(int i, int n){
	if(n >= i){
		printf("%d", i);
		Colunas(i+1, n);
	}	
}

//Impressão do campo minado
void Ocampo(CAMPO_MINADO campoMinado, int m, int n, Boolean perdeu, Boolean ganhou)
{
	telainicial();
	printf("\n");
	Colunas(1, n);
	printf("\n\n");
	imprimirElemento(campoMinado, m, n, 0 , 0, perdeu, ganhou);
	printf("\n");
	Colunas(1, n);
}

void distribuirQuantidades(CAMPO_MINADO *campoMinado) {
  int lin = 0, col = 0;
  int QUANTIDADE_MINAS;

  while (lin < 10){
    while (col < 20){
      if (campoMinado->campoPrincipal[lin][col] != MINA){
        QUANTIDADE_MINAS = quantidadeMinas(campoMinado, lin, col);
        campoMinado->campoPrincipal[lin][col] = QUANTIDADE_MINAS;

        campoMinado->campoPrincipal[lin][col];
        col++;
      }else{
        col++;
      }
    }
    lin++;
    col = 0;
  }
}

int quantidadeMinas(CAMPO_MINADO *campoMinado, int lin, int col) {

  int percorrerLin[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int percorrerCol[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  int linAux, colAux, i, QUANTIDADE_MINAS = 0;

  for (int i = 0; i < 8; i++) {
    linAux = lin + percorrerLin[i];

    colAux = col + percorrerCol[i];

    if (linAux >= 0 && colAux >= 0 && linAux < 10 && colAux < 20) {
      if (campoMinado->campoPrincipal[linAux][colAux] == MINA) {

        QUANTIDADE_MINAS++;
      }
    }
  }

  return QUANTIDADE_MINAS;
}

// Conseguir o numero de minas em volta de um local sem mina
int minas_laterais(CAMPO_MINADO *campoMinado, int a, int n, int i, int d, int lado_A[], int lado_B[], int n_minas, int contador){
	if(contador < 0){
    return n_minas;
  }
  int linha = i + lado_A[contador], coluna = d + lado_B[contador];     
	if(linha < a && coluna < n && campoMinado->campoPrincipal[linha][coluna] == MINA && linha >= 0 && coluna >= 0){
    n_minas++;
  }
	return minas_laterais(campoMinado, a, n, i, d, lado_A, lado_B, n_minas, --contador);
}

//Posição click do usuario
int posicao_click(int a, int b, int c, int d, int e,CAMPO_MINADO *campoMinado, Boolean *perdeu, Boolean *ganhou){
	if(campoMinado->campoPrincipal[a][b] == MINA){
	  *perdeu = true;
		return PERDEU;
	}
	else{
		campoMinado->campoAuxiliar[a][b] = VAGA;
		campoMinado->Y_posicao++;
		if(campoMinado->campoPrincipal[a][b] == 0){
      int lado_B[] =  {-1, 1, -1, 1, 0, 0, 1, -1},
      lado_A[] = {-1, 1, 1, -1, 1, -1, 0, 0};
			posicao_click(campoMinado, a, b, c, d, lado_A, lado_B, 7);			
		}
    
		if(campoMinado->Y_posicao == (c*d-e)){
      return GANHOU;
    }
    
		return CONTINUA;
	}
}

int usuario(CAMPO_MINADO *campoMinado, int m, int n,  int z, Boolean *perdeu, Boolean *ganhou)
{
	char operacao;
	int i = 0, j = 0;
	printf("\n\n\t\t\tProximo chute [letra] [linha] [coluna]: ");
	scanf("%c %d %d", &operacao, &i, &j);
	--i, --j;
	if(i < 0 || i >= m || j < 0 || j >= n || campoMinado->campoAuxiliar[i][j] == VAGA){
    return SEM_EFEITO;
  }
	if(operacao == 'A'  || operacao == 'a'){
    return posicao_click(campoMinado, i, j, m, n, z, perdeu, ganhou);
  }
	if(operacao == 'M'  || operacao == 'm'){
		if(campoMinado->X_posicao == z)	return SEM_EFEITO;
		campoMinado->campoAuxiliar[i][j] = SINALIZADA;
		campoMinado->X_posicao++;
	}
	else if(operacao == 'D'  || operacao == 'd'){
					if(campoMinado->campoAuxiliar[i][j] != SINALIZADA) return SEM_EFEITO;
					else campoMinado->campoAuxiliar[i][j] = NSINALIZADA;	
					campoMinado->X_posicao--;	
		}
		else return SEM_EFEITO;
	return CONTINUA;
}

//O Jogo de fato
void jogo(CAMPO_MINADO *campoMinado, int m, int n,  int z, Boolean *perdeu, Boolean *ganhou)
{
	int primeiro_valor = usuario(campoMinado, m, n, z, perdeu, ganhou);
	if(primeiro_valor == CONTINUA){
		Ocampo(*campoMinado, m, n, *perdeu, *ganhou);
		if(campoMinado->Y_posicao == (m*n-z)) *ganhou = TRUE;
		printf("\n\n\t\t\tPor enquanto: %d/%d marcadas, %d livres.\n", campoMinado->X_posicao, z, m*n - campoMinado->Y_posicao - campoMinado->X_posicao);
	}
	else if(primeiro_valor == PERDEU){
			*perdeu = TRUE;
			Ocampo(*campoMinado, m, n, *perdeu, *ganhou);
			printf("\n\nMina encontrada.\nVOCÊ PERDEU!");	
		}
		else if(primeiro_valor == GANHOU || *ganhou == TRUE){
				*ganhou = TRUE;
				Ocampo(*campoMinado, m, n, *perdeu, *ganhou);
	 			printf("\nNenhuma mina foi destruída \n           Ganhou!\n");
	 		}
	 		else if(primeiro_valor == SEM_EFEITO){
        printf("\n\t\t\t\tSem efeito!\n");
      }
   	if(*perdeu != TRUE && *ganhou != TRUE){
      jogo(campoMinado, m, n, z, perdeu, ganhou);
    }
}

