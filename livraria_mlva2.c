#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Livro {
  char Titulo[50];
  char Autor[50];
  int NumReg;
  double Preco;
  struct Livro* prox; // Ponteiro para o próximo livro na lista
} Livro;


Livro* criarLivro(char titulo[], char autor[], int numReg, double preco);
Livro* inserirLivro(Livro* lista, Livro* novoLivro);
Livro* buscarLivro(Livro* lista, char chave[]);
Livro* removerLivro(Livro* lista, char chave[]);
void liberarLista(Livro* lista);

Livro GetLivro();
void PrintLivro(Livro livro);
void listarLivros(Livro* lista);
void salvarEmArquivo(Livro* lista);

int main(void) {
  Livro* lista = NULL;
  char opcao;

  do {
    printf("\nMENU");
    printf("\n1. Inserir livro");
    printf("\n2. Buscar livro");
    printf("\n3. Remover livro");
    printf("\n4. Salvar em arquivo");
    printf("\n5. Sair");
    
    printf("\nEscolha uma opcao/número: ");
    scanf(" %c", &opcao);

    switch (opcao) {
      case '1':
        lista = inserirLivro(lista, criarLivro("", "", 0, 0.0));
        break;
      
      case '2':
        printf("Digite o título ou número de registro para buscar o livro desejado: ");
        char buscar[50];
        scanf("%s", buscar);
        Livro* livroEncontrado = buscarLivro(lista, buscar);
        
        if (livroEncontrado == NULL) {
          printf("Livro não encontrado.\n");
        } else {
          printf("\nLivro encontrado:\n");
          PrintLivro(*livroEncontrado);
        }
        break;
      
      case '3':
        printf("Digite o título ou número de registro para remover o livro desejado: ");
        char remover[50];
        scanf(" %s", remover);
        lista = removerLivro(lista, remover);
        break;
      
      case '4':
        salvarEmArquivo(lista);
        break;
      
      case '5':
        liberarLista(lista);
        return 0;
      
      default:
        printf("Opcão invalida. Tente novamente!"); //tratamento de erro
    }
  } while (1);

  return 0;
}

Livro* criarLivro(char titulo[], char autor[], int numReg, double preco) {
  Livro* novoLivro = (Livro*)malloc(sizeof(Livro));
  if (novoLivro == NULL) {
    printf("Houve um erro para inserir este livro.\n");
    exit(1);
  }
  //comparar para colocar em ordem alfabética
  //preencher os campos da struct Livro
  strcpy(novoLivro->Titulo, titulo); 
  strcpy(novoLivro->Autor, autor); 
  novoLivro->NumReg = numReg; 
  novoLivro->Preco = preco;
  novoLivro->prox = NULL;
  return novoLivro;
}

Livro* inserirLivro(Livro* lista, Livro* novoLivro) {
  printf("Digite o titulo: ");
  getchar(); // Limpar o buffer do teclado para evitar falhas nas próximas inserções de livros
  fgets(novoLivro->Titulo, 50, stdin); //conseguir pegar os espaços na string do título
  printf("Digite o nome do autor: ");
  fgets(novoLivro->Autor, 50, stdin);
  printf("Digite o numéro do registro: ");
  scanf("%d", &novoLivro->NumReg);
  printf("Digite o preço do livro: ");
  scanf("%lf", &novoLivro->Preco);

  //Inserir em ordem alfabética: lista vazia ou títuolo menor que o anterior
  if (lista == NULL || strcmp(novoLivro->Titulo, lista->Titulo) < 0) {
    novoLivro->prox = lista;
    return novoLivro;
  }
  //percorre a lista até achar onde o livro se encaixa 
  Livro* atual = lista;
  while (atual->prox != NULL && strcmp(novoLivro->Titulo, atual->prox->Titulo) > 0) {
    atual = atual->prox;
  }
  //inserido no local encontrado
  novoLivro->prox = atual->prox;
  atual->prox = novoLivro;

  return lista;
}

Livro* buscarLivro(Livro* lista, char buscar[]) {
  Livro* atual = lista;
  while (atual != NULL) {
    if (strcmp(atual->Titulo, buscar) == 0 || atual->NumReg == atoi(buscar)) { //atoi = conversão para inteiro
      return atual;
    }
    atual = atual->prox;
  }
  return NULL;
}

Livro* removerLivro(Livro* lista, char remover[]) {
  if (lista == NULL) {
    printf("Lista vazia. Nada poderá ser removido.\n");
    return NULL;
  }

  if (strcmp(lista->Titulo, remover) == 0 || lista->NumReg == atoi(remover)) { //se encontrar o livro na cabeça da lista
    Livro* temp = lista;
    lista = lista->prox;
    free(temp);
    printf("Livro removido.\n");
    return lista;
  }

  Livro* atual = lista; 
  while (atual->prox != NULL && (strcmp(atual->prox->Titulo, remover) != 0 && atual->prox->NumReg != atoi(remover))) { //percorrer a lista até achar o livro desejado
    atual = atual->prox;
  }

  if (atual->prox == NULL) { //chegou ao fim da lista 
    printf("Livro não encontrado.\n");
    return lista;
  }

  //ajuste da lista
  Livro* temp = atual->prox;
  atual->prox = atual->prox->prox;
  free(temp);
  printf("\nLivro removido com sucesso.\n");
  return lista;
}

void liberarLista(Livro* lista) {
  Livro* atual = lista;
  //percorrer a lista e ir liberando o espaço de memória
  //armazena o ponteiro atual e o move para o próximo, assim liberando a posição passada
  while (atual != NULL) {
    Livro* temp = atual;
    atual = atual->prox;
    free(temp);
  }
}

void salvarEmArquivo(Livro* lista) {
  FILE* fptr = fopen("livros.dat", "wb"); //escrita binária
  
  if (fptr == NULL) {
    printf("Não foi possível abrir o arquivo.\n");
    return;
  }

  Livro* atual = lista;
  while (atual != NULL) {
    if (fwrite(atual, sizeof(Livro), 1, fptr) != 1) { //!= 1 : se não escrever extamente um elemento --->
      printf("Não fio possível salvar o livro.\n");
      fclose(fptr);
      return;
    }
    atual = atual->prox;
  }

  fclose(fptr);
  printf("Livros armazenados!\n");
}
