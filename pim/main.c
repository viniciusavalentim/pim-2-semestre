#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//SAO CONSTANTES QUE JA INICIAM COM UM TAMANHO FIXO DE PRODUTOS/FORNECEDORES
#define MAX_PRODUTOS 100
#define MAX_ENTRADAS 100
#define MAX_FORNECEDORES 50


//CORES (FUNDO E LETRA)
//OF == PRETO E BRANCO
//1E == AZUL E AMARELO CLARO
//2E == VERDE E AMARELO CLARO
//4E == VERMELHO E AMARELO CLARO
//5E == ROXO E AMARELO CLARO
//6E == AMARELO E AMARELO CLARO
//3E == AZUL CLARO E AMARELO CLARO

typedef struct {
    int id;
    char nome[50];
    float preco;
    int quantidade;
} Produto;

typedef struct {
    int id;
    char nome[50];
    float preco;
    int quantidade;
    char dataValidade[11];
    char dataDeEntrada[11];
    int fornecedorId;
} Entradas;

typedef struct {
    int id;
    char nome[50];
    char contato[50];
    char cnpj[15];
    int totalEntregas;
    int entregasComAtraso;
    int problemasQualidade;
} Fornecedor;


//ONDE OS FORNECEDORES E PORODUTOS SAO INSTANCIADOS PARA A EXIBICAO E LOGICA
Produto produtos[MAX_PRODUTOS] = {
    {1, "Maca", 3.50, 20, "10/12/2024", 1},
    {2, "Banana", 2.00, 30, "15/11/2024", 2},
    {3, "Laranja", 4.25, 25, "20/12/2024", 3},
    {4, "Pera", 5.75, 15, "05/01/2025", 4},
    {5, "Abacaxi", 6.00, 10, "25/11/2024", 1},
    {6, "Uva", 7.50, 18, "30/12/2024", 2},
    {7, "Morango", 10.00, 12, "10/01/2025", 3},
    {8, "Manga", 4.50, 20, "18/12/2024", 4},
    {9, "Melancia", 8.25, 8, "08/01/2025", 1},
    {10, "Kiwi", 5.00, 14, "22/11/2024", 2}
};

Fornecedor fornecedores[MAX_FORNECEDORES] = {
    {1, "Vinicius", "vinicius@fornecedor.com", "12.345.678/0001-00", 50, 5, 2},
    {2, "Eduardo", "eduardo@fornecedor.com", "98.765.432/0002-11", 60, 3, 1},
    {3, "Joyce", "Joyce@fornecedor.com", "11.222.333/0003-44", 40, 4, 5},
    {4, "Ze", "ze@fornecedor.com", "55.666.777/0004-22", 30, 2, 3},
};

Entradas entradas[MAX_ENTRADAS];

int numProdutos = 10;
int numFornecedores = 4;
int numEntradas = 0;



//FUNCOES DESENVOILVIDAS PARA SEREM USADAS GLOBALEMNTE (TODO)
void alterarCorConsole(const char *codigoCor) {
    char comando[10];
    snprintf(comando, sizeof(comando), "color %s", codigoCor);
    system(comando);
}

void configurarTelaPrincipal() {
    system("cls");
    alterarCorConsole("0F");
}

void obterDataDeEntrada(char* dataAtual) {
    time_t agora = time(NULL);
    struct tm *tempoLocal = localtime(&agora);
    strftime(dataAtual, 11, "%d/%m/%Y", tempoLocal);
}


//FUNCOES DESENVOLVIDAS PARA SEREM USADAS NAS GESTOES DOS PRODUTOS
void cadastrarProduto() {
    alterarCorConsole("1F");
    system("cls");
    printf("==========Cadastro de Produto==========\n");

    if (numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }

    //O 49S FAZ COM QUE NAO CAUSE O FAMOSO BUFFER OVERFLOW
    produtos[numProdutos].id = numProdutos + 1;

    printf("Digite o nome do produto: ");
    scanf("%49s", produtos[numProdutos].nome);

    printf("Digite o preco do produto R$ ");
    scanf("%f", &produtos[numProdutos].preco);

    numProdutos++;
    printf("Produto cadastrado com sucesso!\n");
}

void registrarEntradaProduto() {
    alterarCorConsole("2E");
    system("cls");

    printf("Registro de Entrada de Produto:\n");

    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("Produtos cadastrados:\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("ID: %d | Nome: %s \n", produtos[i].id, produtos[i].nome);
    }

    int id, quantidade;
    float preco;
    printf("Digite o ID do produto para registrar a entrada: ");
    scanf("%d", &id);

    if (id <= 0 || id > numProdutos || !id) {
        printf("ID de produto invalido.\n");
        return;
    }

    printf("Digite a quantidade a ser adicionada (em KG): ");
    scanf("%d", &quantidade);

    printf("Digite o preco da entrada R$ ");
    scanf("%f", &entradas[numEntradas].preco);

    printf("Digite a data de validade (dd/mm/yyyy): ");
    scanf("%10s", entradas[numEntradas].dataValidade);

    printf("Digite o ID do fornecedor: \n\n");
    printf("==========Fornecedores cadastrados:==========\n");
    for (int i = 0; i < numFornecedores; i++) {
        printf("ID: %d | Nome: %s | CNPJ: %s \n", fornecedores[i].id, fornecedores[i].nome, fornecedores[i].cnpj);
    }

    scanf("%d", &entradas[numEntradas].fornecedorId);

    entradas[numEntradas].id = numEntradas + 1;
    strcpy(entradas[numEntradas].nome, produtos[id-1].nome);
    entradas[numEntradas].quantidade = quantidade;
    obterDataDeEntrada(entradas[numEntradas].dataDeEntrada);

    produtos[id-1].quantidade += quantidade;
    numEntradas++;
    printf("Entrada registrada com sucesso!\n");
}

void registrarSaidaProduto() {
    alterarCorConsole("4E");
    system("cls");
    printf("Registro de Saida de Produto:\n");

    int id, quantidade;
    printf("Digite o ID do produto para registrar a saida: ");
    scanf("%d", &id);

    if (id <= 0 || id > numProdutos) {
        printf("ID de produto invalido.\n");
        return;
    }

    printf("Digite a quantidade a ser removida: ");
    scanf("%d", &quantidade);

    if (produtos[id-1].quantidade < quantidade) {
        printf("Quantidade insuficiente em estoque.\n");
        return;
    }

    produtos[id-1].quantidade -= quantidade;
    printf("Saida registrada com sucesso!\n");
}

void gerarAlertas() {
    alterarCorConsole("6E");
    system("cls");
    printf("Alertas de produtos proximos do vencimento e com estoque critico:\n");

    for (int i = 0; i < numEntradas; i++) {
        if (produtos[i].quantidade < 5) {
            printf("Estoque baixo: Produto %s (ID: %d) - Quantidade: %d\n", produtos[i].nome, produtos[i].id, produtos[i].quantidade);
        }
        if (strcmp(entradas[i].dataValidade, "01/01/2025") == 0) {
            printf("Produto %s (ID: %d) esta proximo do vencimento.\n", produtos[i].nome, produtos[i].id);
        }
    }
}

void cadastrarFornecedor() {
    alterarCorConsole("3E");
    system("cls");
    printf("Cadastro de Fornecedor:\n");

    if (numFornecedores >= MAX_FORNECEDORES) {
        printf("Limite de fornecedores atingido.\n");
        return;
    }

    printf("Digite o nome do fornecedor: ");
    scanf("%49s", fornecedores[numFornecedores].nome);

    printf("Digite o contato do fornecedor: ");
    scanf("%49s", fornecedores[numFornecedores].contato);

    fornecedores[numFornecedores].id = numFornecedores + 1;
    fornecedores[numFornecedores].totalEntregas = 0;
    fornecedores[numFornecedores].entregasComAtraso = 0;
    fornecedores[numFornecedores].problemasQualidade = 0;
    numFornecedores++;

    printf("Fornecedor cadastrado com sucesso!\n");
}



//FUNCOES DESENVOLVIDAS PARA OS RELATORIOS
void relatorioProdutos() {
    alterarCorConsole("5E");  // Fundo roxo e texto amarelo claro
    system("cls");
    printf("Relatorio de Produtos:\n");

    for (int i = 0; i < numProdutos; i++) {
        printf("ID: %d | Nome: %s | Preco: %.2f | Quantidade: %d \n",
               produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }
}

void relatorioFornecedores() {
    alterarCorConsole("5E");
    system("cls");
    printf("Relatorio de Fornecedores:\n");

    for (int i = 0; i < numFornecedores; i++) {
        printf("==================================\n\n");
        printf("ID: %d | Nome: %s | Contato: %s \n",
                fornecedores[i].id, fornecedores[i].nome, fornecedores[i].contato);
        printf("        Total Entregas: %d | Entregas com Atraso: %d | Problemas de Qualidade: %d\n",
                fornecedores[i].totalEntregas, fornecedores[i].entregasComAtraso, fornecedores[i].problemasQualidade);
    }
}

//RELATORIOS DE ENTRADAS (TODO)

//MENU DE TODAS AS OPCOES DE NAVEGACAO
void menu() {
    int opcao;

    do {
        configurarTelaPrincipal();
        printf("==================== Bem vindo ao LITTLE BIRD ====================");
        printf("\n--- Menu de Controle de Estoque ---\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Registrar Entrada de Produto\n");
        printf("3. Registrar Saida de Produto\n");
        printf("4. Gerar Alertas de Estoque\n");
        printf("5. Cadastrar Fornecedor\n");
        printf("6. Relatorio de Produtos\n");
        printf("7. Relatorio de Fornecedores\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                registrarEntradaProduto();
                break;
            case 3:
                registrarSaidaProduto();
                break;
            case 4:
                gerarAlertas();
                break;
            case 5:
                cadastrarFornecedor();
                break;
            case 6:
                relatorioProdutos();
                break;
            case 7:
                relatorioFornecedores();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
        printf("\nPressione qualquer tecla para continuar...");
        getchar();
        getchar();

    } while(opcao != 0);
}

int main() {

    configurarTelaPrincipal();
    menu();
    return 0;
}
