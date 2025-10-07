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

//VARIAVEL GLOBAL DE VERIFICACAO
int verificacao = 0;

typedef struct {
    char item[TAM_STRING];
    char tipo[TAM_STRING];
    int quant;
    int prioridade;
} Item;

typedef struct {
    Item lista[QUANT_ITENS];
    int total_itens;
} freefire;

//DECLARANCO AS FUNÇÕES
void limparBuffer();
void menuPrincipal(freefire *lista);
void inicializarLista(freefire *lista);
void inserirItem(freefire *lista, const char *texto, const char *tipos, int quantidade, int p);
void listarItens(freefire *lista);
void removerItem(freefire *lista, char *texto);
void limparTela();
void menuDeOrdenacao();
int insertionSort(freefire *lista, int op);


int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair
    int opcao, quantidade, p, op;
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

                printf("Digite o tipo (Estrutural, Eletronico, Eletrica): ");
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
                printf("Pressione Enter para continuar...");
                limparBuffer();
                limparTela();
                break;

            case 3:
                listarItens(&mochila);
                printf("\nPressione Enter para continuar...");
                limparBuffer();
                limparTela();
                break;

            case 4:
                menuDeOrdenacao();
                printf("Escolha sua opcao: ");
                scanf("%d", &op);
                insertionSort(&mochila, op);

                listarItens(&mochila);
                printf("\nPressione enter para sair...");
                limparBuffer();
                limparTela();
                break;

            case 0:
                printf("\nPressione Enter para continuar...");
                while(getchar() != '\n');
                getchar();
                break;

            default:
                printf("Opção inválida!\n");
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
    while (getchar() != '\n');
}
// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.
void limparTela() {
    for(int i = 0; i <= 10; i++)
    {
        printf("\n\n\n\n");
    }
}


// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
void menuPrincipal(freefire *lista)
{
    printf("=========================================\n");
    printf(" MOCHILA DE SOBREVIVENCIA - CODIGO ILHA\n");
    printf("=========================================\n");
    printf("Itens da mochila %d/%d\n\n", lista->total_itens, QUANT_ITENS);

    printf("1 - Inserir Componente\n");
    printf("2 - Descartar Componente\n");
    printf("3 - Listar Componentes\n");
    printf("4 - Organizar Mochila (ordenar componentes)\n");
    printf("5 - Busca Binaria por Componente-Chave (por nome)\n");
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
    if (lista->total_itens == QUANT_ITENS)
    {
        printf("\nA mochila está cheia! Tire algum item antes de adicionar outro...\n\n");
        while (getchar() != '\n');
        getchar();
        return;
    }

    strcpy(lista->lista[lista->total_itens].item, texto);
    strcpy(lista->lista[lista->total_itens].tipo, tipos);
    lista->lista[lista->total_itens].quant = quantidade;
    lista->lista[lista->total_itens].prioridade = p;

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

    for (int i = 0; i < lista->total_itens; i++)
    {
        if (strcmp(lista->lista[i].item, texto) == 0)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("O item \"%s\" não existe!\n", texto);
        return;
    }

    for (int i = pos; i < lista->total_itens - 1; i++)
    {
        lista->lista[i] = lista->lista[i + 1];
    }

    lista->total_itens--;
    printf("Item removido com sucesso!\n");
}

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens(freefire *lista)
{
    if (lista->total_itens == 0)
    {
        printf("Não há itens na lista!\n");
        return;
    }

    printf("\n--- ITENS DA MOCHILA (%d/%d) ---\n", lista->total_itens, QUANT_ITENS);
    printf("----------------------------------------------------------------------------------\n");
    printf("NOME\t\t| TIPO\t\t| QUANTIDADE\t\t| PRIORIDADE\n");
    printf("----------------------------------------------------------------------------------");

    for (int i = 0; i < lista->total_itens; i++)
    {
        printf("\n%-50s| %-50s| %-50d | %-50d", lista->lista[i].item, lista->lista[i].tipo, lista->lista[i].quant, lista->lista[i].prioridade);
    }
    printf("\n");
}


// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).
void menuDeOrdenacao()
{
    printf("--- Estratégia de Oranizaçõa ---\n");
    printf("Como deseja organizar os componentes? ");
    printf("1 - Por Nome\n");
    printf("2 - Por Tipo\n");
    printf("3 - Por Prioridade de Montagem\n");
    printf("0 - Cancelar\n");
    printf("------------------------------------\n");
}

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)
int insertionSort(freefire *lista, int op)
{
    int i, j;
    Item chave;

    for (i = 1; i < lista->total_itens; i++)
    {
        chave = lista->lista[i];
        j = i - 1;

        // Por nome
        if (op == 1)
        { 
            while (j >= 0 && strcmp(lista->lista[j].item, chave.item) > 0)
            {
                lista->lista[j + 1] = lista->lista[j];
                j--;
            }

            verificacao = 1;
        }

        // Por tipo
        else if (op == 2)
        { 
            while (j >= 0 && strcmp(lista->lista[j].tipo, chave.tipo) > 0)
            {
                lista->lista[j + 1] = lista->lista[j];
                j--;
            }
        }

        // Por prioridade
        else if (op == 3)
        {
            while(j >= 0 && lista->lista[j].prioridade < chave.prioridade)
            {
                lista->lista[j + 1] = lista->lista[j];
                j--;
            }
        }

        lista->lista[j + 1] = chave;
    }
}


// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
int buscaBinariaPorNome(freefire *lista, char valor[TAM_STRING])
{
    if (verificacao == 0)
    {
        printf("ALERTA: A busca binária requer que a mochila esteja ordenada por NOME.\n");
        printf("Use a opção 4 para organizar a mochila primeiro.\n\n");
        return -1;
    }

    int inicio = 0;
    int fim = lista->total_itens - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;

        int cmp = strcmp(lista->lista[meio].item, valor);

        if (cmp == 0)
        {
            return meio; // encontrou
        }
        else if (cmp < 0)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    return -1; // não encontrou
}