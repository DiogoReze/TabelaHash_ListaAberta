#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// constante repesenta o tamanho da tabela
#define M 16

// estrutura com os itens para compra de cavalos
typedef struct compraCavalos{
  int id;
  char nome[50];
  float preco;
  int idade;
  float velocidade;
  int temperamento;
}CompraCavalos;

// tabela hash do tipo Compra de cavalos
CompraCavalos tabelaHash[M];
CompraCavalos tempTabelaHash[M];

// iniciar a tabela com o valor 0 para demonstrar que ela esta vazia
void iniciarTabela(){
  int i;
  for(i = 0; i < M; i++)
    tabelaHash[i].id = 0;
}

// função de espalhamento (vai gerar um código a ser utilizado como índice de acesso na tabela)
int funcEspalhamento(int chave){
  return chave % M;
}

void printTemperamento(){
  printf("\n---------------------------TEMPERAMENTO---------------------------\n");
  printf("1 - sangue quente: ativos, nervosos, alertas, melhor montabilidade\n");
  printf("2 - sangue morno: mistura dos sangues frios com os sangues quentes\n");
  printf("3 - sangue frio: calmos e mais faceis de serem domesticados\n");
}

// função para entrada de dados e retornar um cavalo que foi comprado
CompraCavalos entradaDados(){
  CompraCavalos c;
  printf("Digite o ID: ");
  scanf("%d", &c.id);
  printf("Digite o nome: ");
  scanf("%s", c.nome);
  printf("Digite o preco: ");
  scanf("%f", &c.preco);
  printf("Digite a idade: ");
  scanf("%d", &c.idade);
  printf("Digite a velocidade: ");
  scanf("%f", &c.velocidade);
  do{
  	printTemperamento();
    printf("\nDigite o numero do temperamento: ");
    scanf("%d", &c.temperamento);
    printf("\n");

    if(c.temperamento > 3 || c.temperamento < 1)
    	printf("\nNumero invalido! Selecione um valor da tabela:\n");
  } while (c.temperamento > 3 || c.temperamento < 1);

  return c;
}

// inserir um cavalo na tabela
void inserirCavalo(){
  CompraCavalos cavalo = entradaDados();
  int indice = funcEspalhamento(cavalo.id);
  int contador = 1, acumulador = 1;

  while(tabelaHash[indice].id != 0){
  	indice = funcEspalhamento(funcEspalhamento(cavalo.id) + acumulador);
  	contador++;
  	acumulador+= contador;
  }

  tabelaHash[indice] = cavalo;
  printf("Cavalo comprado com sucesso!\n");
}

//Buscando um cavalo pelo seu id (nossa chave)
CompraCavalos* buscarCavalo(int chave){
  int indice = funcEspalhamento(chave);
  int contador = 1, acumulador = 1;

  while(tabelaHash[indice].id != 0){
    if(tabelaHash[indice].id == chave){
      return &tabelaHash[indice]; //retorna o end. de memoria em que o cavalo esta
    }
    else{
	  //caso possua colisão e o valor que estamos procurando esta em outra posicao
      indice = funcEspalhamento(funcEspalhamento(chave) + acumulador);
  	  contador++;
  	  acumulador+= contador;
    }
  }
  return NULL; //O elemento nao esta na tabela
}

//imprimir toda a tabela Hash
void imprimirCavalos(){
  printf("\n---------------ESTABULO COM NOVOS CAVALOS-----------------\n");
  printf("     ID | Nome | Preco | Idade | Velocidade | Temperamento\n");

  int i;
  for(i = 0; i < M; i++){
    if(tabelaHash[i].id != 0)
      printf("%d = %d | %s | %.2f | %d | %.1f | %d\n", i, tabelaHash[i].id, tabelaHash[i].nome, tabelaHash[i].preco, tabelaHash[i].idade, tabelaHash[i].velocidade, tabelaHash[i].temperamento);
    else
      printf("%d =\n", i);
  }
  printf("\n----------------------------------------------------------\n");
}

//imprimir cavalos por temperamento
void imprimirCavalosPorTemperamento(){
  int temperamento;
  printTemperamento();
  printf("\nVoce gostaria de listar os cavalos por qual temperamento?\n");
  scanf("%d", &temperamento);

  int i;
  for(i = 0; i < M; i++)
  {
    if(tabelaHash[i].temperamento == temperamento) {
        printf("%d = %d | %s | %.2f | %d | %.1f | %d\n", i, tabelaHash[i].id, tabelaHash[i].nome, tabelaHash[i].preco, tabelaHash[i].idade, tabelaHash[i].velocidade, tabelaHash[i].temperamento);
    }
  }
}

// funcao de remover um cavalo do estabulo
void remover(int pos) {
  int i, verificador = 0;
  if ((tabelaHash[pos].id != 0) && ((tabelaHash[pos].id) != 0) ){
      printf("\n-> Dados HASH[%d] estao sendo apagados...\n",pos);
      printf("%2d = %3d | %s | %.2f | %d | %.1f | %d\n", pos, tabelaHash[pos].id, tabelaHash[pos].nome,
              tabelaHash[pos].preco, tabelaHash[pos].idade, tabelaHash[pos].velocidade, tabelaHash[pos].temperamento);
      tabelaHash[pos] = tempTabelaHash[pos];
      printf("-> Dados HASH[%d] apagados\n",pos);
      printf("%2d = %3d | %s | %.2f | %d | %.1f | %d\n", pos, tabelaHash[pos].id, tabelaHash[pos].nome,
              tabelaHash[pos].preco, tabelaHash[pos].idade, tabelaHash[pos].velocidade, tabelaHash[pos].temperamento);
  } else {
      printf("\nA posicao esta vazia\n");
  }
}

int main() {
  int option, chave, pos;
  CompraCavalos *c; //criamos um ponteiro pois a funcao buscarCavalo retorna um ponteiro

  iniciarTabela();

  do{
  	printf("\n0 - Sair\n1 - Inserir\n2 - Buscar\n3 - Imprimir\n4 - Imprimir por temperamento\n5 - Remover\n");
    scanf("%d", &option);

    switch(option){
    case 0:
      printf("Saindo...\n");
      break;

    case 1:
      inserirCavalo();
      break;

    case 2:
      printf("Digite o ID que sera buscado: ");
      scanf("%d", &chave);
      c = buscarCavalo(chave);

      if(c){ //c != NULL
        printf("\nO ID foi encontrado na tabela:");
        printf("\nID: %d | Nome: %s | Preco: %.2f | Idade: %d | Velocidade: %.1f | Temperamento: %d\n", c->id, c->nome, c->preco, c->idade, c->velocidade, c->temperamento);
      }
      else
        printf("\nID nao foi encontrado!\n");
      break;

    case 3:
      imprimirCavalos();
      break;

    case 4:
      imprimirCavalosPorTemperamento();
      break;

    case 5:
      printf("Digite a posicao a ser apagada: ");
      scanf("%d", &pos);
      remover(pos);
      break;

    default:
      printf("Opcao invalida!\n");
    }

  } while(option != 0);

  return 0;
}
