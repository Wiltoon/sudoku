#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void BuscaDeQuantidade(int** sudoku, int t, int* vet, int tamanho) //contar quantas vezes os numeros aparecem
{
  int i,j;
  for(i = 0; i < tamanho; i++)
  {
    for(j = 0; j < tamanho; j++)
    {
      if(sudoku[i][j] == t)
      {
	vet[t-1] = vet[t-1] - 1;
      }
    }
  }
}
int ProcurarElemento(int el, int** sudoku, int n, int** verdadeiro, int qnt)
{
  int i, j;
  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++)
    {
      if(el == sudoku[i][j])
      {
	ApagarLinha(sudoku,i,n);
	ApagarColuna(sudoku,j,n);
	ApagarQuadrados(sudoku,i,j,n);
      }
    }
  }
  for(i = 0; i < n; i++)//beleza
  {
    PercorrerCompletar(i,verdadeiro,sudoku,n,el,qnt);//ele ira percorrer o quadrante e completar o que falta
  }
  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++)
    {
      sudoku[i][j] = verdadeiro[i][j];
    }
  }
  return;
}
void PercorrerCompletar(int quadrante, int** verdadeiro, int**sudoku,int n, int elemento, int qnt)
{
  int l, c, i, j, p, o, Q, V = 0;
  Q = sqrt(n);
  p = quadrante%Q;
  o = (quadrante%Q)*Q; 
  for(i = o; i < n; i++)
  {
    for(j = p; j < n; j++)
    {
      if(sudoku[i][j] == 0)
      {
	sudoku[i][j] = elemento;
	l = i;
	c = j;
	V = V + 1;
      }
    }
  }
  if(V == 1)
  {
    verdadeiro[l][c] = elemento;
    qnt = qnt - 1;
  }
  return;
}
void ApagarLinha(int** sudoku, int p, int n)//vai dar a localização e ira apagar o vetor
{
  for(int i = 0; i < n; i++)
  {
    sudoku[p][i] = -1;
  }
  return;
}
void ApagarColuna(int** sudoku, int p, int n)//apagar a coluna onde o elemento se encontra
{
  for(int i = 0; i < n; i++)
  {
    sudoku[i][p] = -1;
  }
  return;
}
void ApagarQuadrados(int** sudoku, int i, int j, int n)
{
  int /*aux*/, Q, w, p;
  Q = sqrt(n);
  //aux = i/Q + (j/Q)*Q + 1;
  for(w = (i/Q)*Q; w < (i/Q)*Q + Q; w++)
  {
    for(p = (j/Q)*Q; p < (j/Q)*Q + Q; p++)
    {
      sudoku[w][p] = -1;
    }
  }
  return;
}
void Reveroun(int el, int** sudoku, int qnt, int* vetor)//verificar se da para diminuir a quantidade novamente
{
  
}
int main(void)
{
  int n, **sud, i, j, **aux; //n = tamanho do sudoku
  printf("Digite o numero maximo do sudoku:\n"); 
  scanf("%d", &n);
  printf("\nDigite os numeros do sudoku:\n");
  sud = (int**)malloc(n*sizeof(int*));
  for(i = 0; i < n; i++)
  {
    sud[i] = (int*)malloc(n*sizeof(int));
  }
  aux = (int**)malloc(n*sizeof(int*));
  for(j = 0; j < n; j++)
  {
    aux[j] = (int*)malloc(n*sizeof(int));
  }
  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++)
    {
      scanf("%d", &sud[i][j]);
      aux[i][j] = sud[i][j];
    }
  }
  int *vet = (int*)malloc(n*sizeof(int));
  for(i = 0; i < n; i++)
  {
    vet[i] = n;
    BuscaDeQuantidade(sud, i+1, vet, n);
    if(vet[i] < 0)
    {
      printf("NÃO HÁ SOLUÇÃO\n");
      return 0;
    }
  }
  for(i = 1; i <= n; i++)//fixos de sudoku
  {
    for(j = 0; j < n; j++)
    {
      if(vet[j] == i)
      {
	ProcurarElemento(j+1,aux,n,sud,vet[j]);//achou elemento e apagou as alternativas apresentadas a ela
	
      }
    }
  }
  
    
  return 0;
}
