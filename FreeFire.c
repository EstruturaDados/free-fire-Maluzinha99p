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
    int quant[QUANT_ITENS];
    int prioridade[QUANT_ITENS];
    int total_itens;
}freefire;

//DECLARANCO AS FUNÇÕES
void limparBuffer();
void menuPrincipal(freefire *lista);
void inicializarLista(freefire *lista);
void inserirItem(freefire *lista, const char *texto, const char *tipos, int quantidade, int p);
void listarItens(freefire *lista);
void removerItem(freefire *lista, char *texto);
void limparTela();


int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair
    int opcao, quantidade, p;
    char itens[TAM_STRING], tipos[TAM_STRING], item_remover[TAM_STRING];

    freefire mochila;

    inicializarLista(&mochila);

    do{
        menuPrincipal(&mochila);
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
            case 1:
                printf("\n\n--- Coletando novo Componente ---\n");
                printf("Nome do item: ");
                fgets(itens, TAM_STRING, stdin);

                printf("Digite o tipo (Estrutural, Eletrica, Eletronica): ");
                fgets(tipos, TAM_STRING, stdin);

                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);

                printf("Prioridade de Montagem (1-5): ");
                scanf("%d", &p);
    
                //excluindo o \n
                itens[strcspn(itens, "\n")] = 0;
                tipos[strcspn(itens, "\n")] = 0;
                
                inserirItem(&mochila, itens, tipos, quantidade, p);
                limparBuffer();

                listarItens(&mochila);
                printf("Pressione Enter para continuar...");
                limparBuffer();
                limparTela();
            break;

            case 2:
                printf("\n--- REMOVENDO ITEN ---\n");
                printf("Qual item deseja remover: ");
                fgets(item_remover, TAM_STRING, stdin);

                item_remover[strcspn(item_remover, "\n")] = 0;

                removerItem(&mochila, item_remover);
                listarItens(&mochila);
                printf("Clique Enter para continuar...");
                limparBuffer();
                limparTela();
            break;

            case 3:
                listarItens(&mochila);
                printf("\nClique Enter para continuar...");
                limparBuffer();
                limparTela();
            break;
            case 0:
                printf("\nClique Enter para continuar...");
                while(getchar() != '\n');
                getchar();
            break;

            default:
                printf("Item inexistente!\n");
            break;
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
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
void menuPrincipal(freefire *lista)
{
    printf("=========================================\n");
    printf(" MOCHILA DE SOBREVIVENCIA - CODIGO ILHA\n");
    printf("=========================================\n");
    printf("Itens da mochila %d/10\n\n", lista->total_itens);

    printf("1 - Inserir Componente) \n");
    printf("2 -Descartar Componente\n");
    printf("3 - Listar Componentes\n");
    printf("4 - Organizar Mochila (ordenar componentes)\n");
    printf("5 - Busca Binaria por Componente-Chave (por nome)");
    printf("0 - ATIVAR TORRE DE FULGA (sair)\n");
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
void inserirItem(freefire *lista, const char *texto, const char *tipos, int quantidade, int p)
{
    if(lista->total_itens == QUANT_ITENS)
    {
        printf("\nA mochila esta cheia! Tire algum item de quiser adicionar outro...\n\n");
        while(getchar() != '\n');
        getchar();
    }

    strcpy(lista->item[lista->total_itens], texto);
    strcpy(lista->tipo[lista->total_itens], tipos);
    lista->quant[lista->total_itens] = quantidade;
    lista->prioridade[lista->total_itens] = p;

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
    }

    if(pos == -1)
    {
        printf("O item \"%s\" não existe!\n", texto);
        return;
    } 

    for(int i = pos; i < lista->total_itens; i++)
    {
        strcpy(lista->item[i], lista->item[i+1]);
        strcpy(lista->tipo[i], lista->tipo[i+1]);
        lista->quant[i] = lista->quant[i+1];
    }

    lista->total_itens--;
    printf("Item removido com sucesso!\n");
}

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens(freefire *lista)
{
     if(lista->total_itens == 0)
     {
        printf("Não há itens na lista!\n");
     }

     printf("\n--- ITENS DA MOCHILA (%d/10) ---\n", lista->total_itens);
     printf("--------------------------------------------------\n");
     printf("NOME\t\t| TIPO\t\t| QUANTIDADE\n");
     printf("--------------------------------------------------\n");

     for(int i = 0; i < lista->total_itens; i++)
     {
        printf("%-15s| %-15s| %-10d\n", lista->item[i], lista->tipo[i], lista->quant[i]);
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
