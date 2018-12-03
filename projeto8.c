//Alunos: Joao Pedro Mota Jardim       16/0031982

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/* definicao de variaveis globais */

int destino, origem;
int *custos = NULL;

void printarCidade(int codigo){
  switch (codigo) {
    case 1:
      printf("Ceilandia");
      break;
      case 2:
        printf("Vicente Pires");
        break;
      case 3:
        printf("Taguatinga");
        break;
      case 4:
        printf("Aguas Claras");
        break;
      case 5:
        printf("Riacho Fundo 1");
        break;
      case 6:
        printf("Zoologico");
        break;
      case 7:
        printf("Brasilia");
        break;
  }
}

void dijkstra(int vertices,int origem,int destino,int *custos)
{
  int i,v, cont = 0;
  int *ant, *tmp;
  int *z; /* vertices para os quais se conhece o caminho minimo */
  double min;
  double dist[vertices]; /* vetor com os custos dos caminhos */


  /* aloca as linhas da matriz */
  ant = calloc (vertices, sizeof(int *));
  tmp = calloc (vertices, sizeof(int *));
  if (ant == NULL) {
    printf ("** Erro: Memoria Insuficiente **");
    exit(-1);
  }

  z = calloc (vertices, sizeof(int *));
  if (z == NULL) {
    printf ("** Erro: Memoria Insuficiente **");
    exit(-1);
  }

  for (i = 0; i < vertices; i++) {
    if (custos[(origem - 1) * vertices + i] !=- 1) {
      ant[i] = origem - 1;
      dist[i] = custos[(origem-1)*vertices+i];
    }
    else {
      ant[i]= -1;
      dist[i] = HUGE_VAL;
    }
    z[i]=0;
  }
  z[origem-1] = 1;
  dist[origem-1] = 0;

  /* Ciclo principal */
  do {
    /* Encontra o vertice que deve entrar em z */
    min = HUGE_VAL;
    for (i=0;i<vertices;i++)
      if (!z[i])
        if (dist[i]>=0 && dist[i]<min) {
          min=dist[i];v=i;
        }

    /* Calcula distancias dos novos vizinhos de z */
    if (min != HUGE_VAL && v != destino - 1) {
      z[v] = 1;
      for (i = 0; i < vertices; i++)
        if (!z[i]) {
          if (custos[v*vertices+i] != -1 && dist[v] + custos[v*vertices+i] < dist[i]) {
            dist[i] = dist[v] + custos[v*vertices+i];
            ant[i] =v;
          }
        }
    }
  } while (v != destino - 1 && min != HUGE_VAL);

  /* Mostra o Resultado da procura */
  printf("\tDe ");
  printarCidade(origem);
  printf(" para ");
  printarCidade(destino);
  printf(":\n");
  printf("\t");
  if (min == HUGE_VAL) {
    printf("Nao Existe\n");
    printf("\tCusto: \t- \n");
  }
  else {
    i = destino;
    i = ant[i-1];
    while (i != -1) {
      // printf("<-%d",i+1);
      tmp[cont] = i+1;
      cont++;
      i = ant[i];
    }
    for (i = cont; i > 0 ; i--) {
      printarCidade(tmp[i-1]);
      printf(" -> ");
    }
    printarCidade(destino);

    printf("\n\tCusto: %d\n",(int) dist[destino-1]);
  }
}

void geraGrafo(int arestas,int vertices, int *origens,int *destinos, int *distancias)
{
  int i,custo;
  if (!custos)
    free(custos);
  custos = (int *) malloc(sizeof(int)*vertices*vertices);
  for (i = 0; i <= vertices * vertices; i++)
    custos[i] = -1;

  for(i = 0; i < arestas; i ++){
    origem = origens[i];
    destino = destinos[i];
    custo = distancias[i];
    custo = custo + (rand() % 11);
    custos[(origem-1) * vertices + destino - 1] = custo;
  }
}

void mostraTodosCaminhos(int vertices)
{
  printf("Lista de todas as rotas possiveis e seus precos no momento: \n");
  for (int i = 1; i <= vertices; i++) {
    for (int j = 1; j <= vertices; j++)
      if(i != j){
        dijkstra(vertices, i,j, custos);
        printf("\n");
      }
  }
}

void mostraCidades(){
  printf("1 - Ceilandia\n");
  printf("2 - Vicente Pires\n");
  printf("3 - Taguatinga\n");
  printf("4 - Aguas Claras\n");
  printf("5 - Riacho Fundo 1\n");
  printf("6 - Zoologico\n");
  printf("7 - Brasilia\n");
}

void mostraCaminhoEspecifico(int vertices)
{
    int origem, destino;
    printf("Escolha sua origem: \n");
    mostraCidades();
    printf("Sua opcao: ");
    scanf("%d",&origem);
    printf("\n");
    printf("Escolha seu destino: \n");
    mostraCidades();
    printf("Sua opcao: ");
    scanf("%d",&destino);
    printf("\n\n");
    dijkstra(vertices, origem, destino, custos);
    printf("\n\n");
}

void mostraMenu(){
  //system("clear");
  printf("\n");
  printf(" ========================================\n");
  printf("|   Simulacao de servico de carona pago  |\n");
  printf("|         >>>>>>>>> Menu <<<<<<<<<       |\n");
  printf("| 1 - mostrar todos os precos            |\n");
  printf("| 2 - Escolher origem e destino          |\n");
  printf("| 3 - Alterar horario aleatorio(preco)   |\n");
  printf("| 0 - Sair                               |\n");
  printf(" ========================================\n");
  printf("Sua opcao: ");
}
int main(int argc, char **argv) {
  srand(time(NULL));
  int vertices = 7;
  int arestas = 20;
  int origens[20] = {1,1,2,2,2,2,3,3,3,3,4,4,4,5,5,5,6,6,7,7};
  int destinos[20] ={2,3,1,3,4,7,1,2,4,5,2,3,5,3,4,6,5,7,2,6};
  int distancias[20]= {15,7,15,8,8,20,7,8,6,10,8,6,5,10,5,11,11,10,20,10};
  int opcao;
  //char opcao[3], l[50];
  geraGrafo(arestas,vertices,origens,destinos,distancias);
  do {
    mostraMenu();
    scanf("%d",&opcao);
    printf("\n\n");
    switch (opcao) {
      case 1:
        mostraTodosCaminhos(vertices);
        break;
      case 2:
        mostraCaminhoEspecifico(vertices);
        break;
      case 3:
        geraGrafo(arestas,vertices,origens,destinos,distancias);
        break;
    }
  } while (opcao != 0);

  printf("\nFinalizando o Programa\n\n");

  return 0;
}
