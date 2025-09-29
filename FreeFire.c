#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.
#define QUANT_ITENS 10
#define TAM_STRING 100

typedef struct{
    char item[QUANT_ITENS][TAM_STRING];
    char tipo[QUANT_ITENS][TAM_STRING];
    int quant;
    int total_itens;
}freefire;

//DECLARANCO AS FUNÇÕES
void limparBuffer();
void menuPrincipal();
void inicializarLista(freefire *lista);
void inserirItem(freefire *lista, const char *texto, const char *tipos, int *quantidade);
void listarItens(freefire *lista);


int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair
    int opcao, quantidade;
    char itens[TAM_STRING], tipos[TAM_STRING];

    freefire mochila;

    inicializarLista(&mochila);

    do{
        menuPrincipal();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
            case 1:
                printf("\n\n--- ADICIONAR NOVO ITEM ---\n");
                printf("Nome do item: ");
                fgets(itens, TAM_STRING, stdin);

                printf("Digite o tipo (arma, munição, cura, etc): ");
                fgets(tipos, TAM_STRING, stdin);

                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                
                //excluindo o \n
                itens[strcspn(itens, "\n")] = 0;
                tipos[strcspn(itens, "\n")] = 0;
                
                inserirItem(&mochila, itens, tipos, quantidade);
            break;

            case 3:
                listarItens(&mochila);
            break;
            case 0:
                printf("\nClique no Enter para continuar...\n");
                while(getchar() != '\n');
                getchar();
        }
        
    }while(opcao != 0);

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

//limparBuffer()
void limparBuffer()
{
    while(getchar() != '\n');
}
// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
void menuPrincipal()
{
    printf("=========================================\n");
    printf(" MOCHILA DE SOBREVIVENCIA - CODIGO ILHA\n");
    printf("=========================================\n");

    printf("1 - Inserir item (LOOT) \n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens da Mochila\n");
    printf("0 - Sair do sistema\n");
    printf("-------------------------------------------\n");
    printf("Escolha a sua opção: ");
}

//inicializarLista
void inicializarLista(freefire *lista)
{
    lista->total_itens = 0;
}

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
void inserirItem(freefire *lista, const char *texto, const char *tipos, int *quantidade)
{
    if(lista->total_itens == QUANT_ITENS)
    {
        printf("\nA mochila esta cheia! Tire algum item de quiser adicionar outro...");
        while(getchar() != '\n');
        getchar();
    }

    strcpy(lista->item[lista->total_itens], texto);
    strcpy(lista->tipo[lista->total_itens], tipos);
    lista->quant = quantidade;

    lista->total_itens++;
    printf("\nItens \"%s\" cadastrado com sucesso!\n", texto);
    printf("-------------------------------------------\n\n");

}

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
void removerItem(freefire *lista, char *texto)
{
    int pos = -1;

    for(int i = 0; i < QUANT_ITENS; i++)
    {
        if(strcmp(lista->item[i], texto) == 0)
        {
            pos = i;
            break;
        }

        if(pos == -1)
        {
            printf("O item \"%s\" não existe!", texto);
            return;
        } 

        for(i = pos; i < lista->total_itens; i++)
        {
            strcpy(lista->item[i], lista->item[i+1]);
            strcpy(lista->tipo[i], lista->tipo[i+1]);
            lista->quant[i] = lista->quant[i+1];
        }

        lista->total_itens--;
        printf("Item removido com sucesso!\n");
    }
}

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens(freefire *lista)
{
     if(lista->total_itens == 0)
     {
        printf("Não há itens na lista!\n");
     }

     printf("\n\n--- ITENS DA MOCHILA (%d/10) ---\n", lista->total_itens);
     printf("--------------------------------------------------\n");
     printf("NOME\t\t| TIPO\t\t| QUANTIDADE\n");
     printf("--------------------------------------------------\n");

     for(int i = 0; i < lista->total_itens; i++)
     {
        printf("%s\t\t| %s\t\t| %d\n", lista->item[i], lista->tipo[i], lista->quant);
        printf("--------------------------------------------------\n\n");

     }
}

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
