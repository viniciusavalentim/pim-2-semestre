#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <string.h>


//SAO CONSTANTES QUE JA INICIAM COM UM TAMANHO FIXO DE PRODUTOS/FORNECEDORES
#define MAX_PRODUTOS 100
#define MAX_ENTRADAS 100
#define MAX_FORNECEDORES 50
#define MAX_SAIDAS 100


//CORES (FUNDO E LETRA)
//OF == PRETO E BRANCO
//1E == AZUL E AMARELO CLARO
//2E == VERDE E AMARELO CLARO
//4E == VERMELHO E AMARELO CLARO
//5E == ROXO E AMARELO CLARO
//6E == AMARELO E AMARELO CLARO
//3E == AZUL CLARO E AMARELO CLARO
//FUNDOVERDE 2
//CINZAMEDIO 8
//BRANCO 15
//AMARELO 14
//CIANO 11
//VERMELHO 12
// VERMELHOCLARO 4
// VERDECLARO 2
// AZULCLARO 1
// AMARELO_CLARO 6
// MAGENTA_CLARO 5
// CIANO_CLARO 3
// VERDE_OLIVA 10
// AZUL_ELETRICO 11
// LILAS 13
// BRANCO_FUMO 7
// VERDE_MAR 10
// MARROM 4



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
    char cnpj[20];
    int totalEntregas;
    int entregasComAtraso;
    int problemasQualidade;
} Fornecedor;

typedef struct {
    int id;
    int idProduto;
    char nome[50];
    float precoTotal;
    int quantidade;
    char dataDeSaida[11];
} Saidas;


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

Entradas entradas[MAX_PRODUTOS] = {
    {1, "Maca", 2000, 10, "10/12/2024", "28/10/2023", 1},
    {2, "Maca", 3000, 15, "30/12/2024", "27/10/2023", 1}
};

Saidas saidas[MAX_SAIDAS] = {
     {1, 1, "Maca", 234.02, 12,"10/12/2024"},
     {2, 3, "Laranja", 49.50, 23,"30/12/2024"},
     {3, 7, "Morango", 449.50, 23,"30/12/2024"},
     {4, 9, "Melancia", 39.50, 3,"30/12/2024"},
     {5, 10, "Kiwi", 29.50, 11,"30/12/2024"},
};

int numProdutos = 10;
int numFornecedores = 4;
int numEntradas = 2;
int numSaidas = 2;


//FUNCOES DESENVOILVIDAS PARA SEREM USADAS GLOBALEMNTE (TODO)


void obterDataDeEntrada(char* dataAtual) {
    time_t agora = time(NULL);
    struct tm *tempoLocal = localtime(&agora);
    strftime(dataAtual, 11, "%d/%m/%Y", tempoLocal);
}

void configurarTelaPrincipal() {
    system("cls");
}

void carregarAnimacao() {
    const char animacao[] = "|/-\\";
    for (int i = 0; i < 8; i++) {
        printf("\rCarregando %c", animacao[i % 4]);
        Sleep(150);
    }
    printf("\n");
}

void exibirTitulo() {
    system("cls");
    printf("\n==========================");
    printf("  Bem vindo ao Little Bird  ");
    printf("==========================\n\n");
}

void exibirTituloPersonalizado(int corTexto,int corBarra, char texto[250]) {
    system("cls");
    printf("\n==========================");
    printf(" %s ", texto);
    printf("==========================\n\n");
}

void exibirTituloEFundo(int corTexto,int corBarra, int fundo, char texto[250]) {
    system("cls");
    printf("\n==========================");
    printf(" %s ", texto);
    printf("==========================\n\n");
}



//FUNCOES DESENVOLVIDAS PARA SEREM USADAS NAS GESTOES DOS PRODUTOS
void cadastrarProduto() {
    system("cls");
    exibirTituloPersonalizado(14, 11, "Cadastrar Produto");
    char quite[50];
    if (numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }
    produtos[numProdutos].id = numProdutos + 1;
    printf("--> Caso queira sair digite 'q' ou 'Q' <--\n");
    while (1) {
        printf("Digite o nome do produto: ");
        if (fgets(produtos[numProdutos].nome, sizeof(produtos[numProdutos].nome), stdin) != NULL) {
            produtos[numProdutos].nome[strcspn(produtos[numProdutos].nome, "\n")] = '\0';
            if (strcmp(produtos[numProdutos].nome, "q") == 0 || strcmp(produtos[numProdutos].nome, "Q") == 0) {
                printf("Operacao cancelada pelo usuario.\n");
                return;
            }
            if (strlen(produtos[numProdutos].nome) == 0) {
                printf("Erro: o nome do produto nao pode estar vazio. Tente novamente.\n");
            } else {
                break;
            }
        } else {
            printf("Entrada invalida. Tente novamente.\n");
        }
    }
    char entrada[20];
    float preco;
    printf("============================================\n");
    printf("--> Caso queira sair digite 'q' ou 'Q' <--\n");
    while (1) {
        printf("Digite o preco do produto (KG) R$ ");
        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            entrada[strcspn(entrada, "\n")] = '\0';
            if (entrada[0] == 'q' || entrada[0] == 'Q') {
                printf("Operacao cancelada pelo usuario: ");
                return;
            }

            if (sscanf(entrada, "%f", &preco) != 1) {
                printf("Erro: Entrada invalida insira um numero: ");
            } else if (preco < 0.1) {
                printf("Erro: O preco deve ser maior ou igual a 0.1. Tente novamente.\n");
            } else {
                break;
            }
        } else {
            printf("Erro ao ler a entrada Tente novamente.\n");
        }
    }
    produtos[numProdutos].preco = preco;
    numProdutos++;
    printf("Produto cadastrado com sucesso!\n");
}

void registrarEntradaProduto() {
    system("cls");
    exibirTituloPersonalizado(14, 11, "Registrar Entrada do produto");


    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    int id, quantidade;
    float preco;
    printf("---- Digite o ID do produto para registrar a entrada ----\n");

    printf("Produtos cadastrados:\n");
    for (int i = 0; i < numProdutos; i++) {

        printf(" ID: %d", produtos[i].id);

        printf(" | Nome: %s \n", produtos[i].nome);
    }

    printf("\n");
    char entrada[50];


    printf("<-- Caso queira sair digite 'q' ou 'Q' -->\n");

    while (1) {
        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            entrada[strcspn(entrada, "\n")] = '\0';
            if (entrada[0] == 'q' || entrada[0] == 'Q') {
                printf("Operacao cancelada pelo usuario.\n");
                return 0;
            }
            if (sscanf(entrada, "%d", &id) != 1) {
                printf("Erro: Entrada invalida insira um numero: ");
            } else if (id <= 0) {
                printf("Erro: O id deve ser maior ou igual a 1. Tente novamente: ");
            } else if(id > numProdutos){
                printf("Erro: Produto nao existe. Tente novamente: ");
            }else{
                break;
            }
        } else {
            printf("Erro ao ler o id. Tente novamente: ");
        }
    }

    printf("========== Fruta selecionada: %s ==========\n", produtos[id - 1].nome);

    printf("Digite a quantidade a ser adicionada (em KG): ");
    while (1) {
        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            entrada[strcspn(entrada, "\n")] = '\0';
            if (entrada[0] == 'q' || entrada[0] == 'Q') {
                printf("Operacao cancelada pelo usuario.\n");
                return 0;
            }
            if (sscanf(entrada, "%d", &quantidade) != 1) {
                printf("Erro: Entrada invalida insira um numero: ");
            } else if (quantidade <= 0) {
                printf("Erro: A qauntidade deve ser maior ou igual a 1. Tente novamente: ");
            } else {
                break;
            }
        } else {
            printf("Erro ao ler o quantidade. Tente novamente: ");
        }
    }

    printf("Digite o preco da entrada R$ ");
    while (1) {
        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            entrada[strcspn(entrada, "\n")] = '\0';
            if (entrada[0] == 'q' || entrada[0] == 'Q') {
                printf("Operacao cancelada pelo usuario.\n");
                return 0;
            }
            if (sscanf(entrada, "%f", &entradas[numEntradas].preco) != 1) {
                printf("Erro: Entrada invalida insira um numero: ");
            } else if (entradas[numEntradas].preco <= 0) {
                printf("Erro: O Preco deve ser maior ou igual a 1. Tente novamente: ");
            } else {
                break;
            }
        } else {
            printf("Erro ao ler o Preco. Tente novamente: ");
        }
    }

    printf("Digite a data de validade (dd/mm/yyyy): ");

    while (1) {
        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            entrada[strcspn(entrada, "\n")] = '\0';
            if (entrada[0] == 'q' || entrada[0] == 'Q') {
                printf("Operacao cancelada pelo usuario.\n");
                return 0;
            }
            if (sscanf(entrada, "%10s", &entradas[numEntradas].dataValidade) != 1) {
                printf("Erro: Entrada invalida insira um numero.\n");
            } else {
                break;
            }

        } else {
            printf("Erro ao ler a data. Tente novamente: ");
        }
    }

    printf("\n---- Digite o ID do fornecedor ----\n");
    printf("Fornecedores cadastrados:\n");
    for (int i = 0; i < numFornecedores; i++) {

        printf(" ID: %d", fornecedores[i].id);
        printf(" | Nome: %s | CNPJ: %s \n", fornecedores[i].nome, fornecedores[i].cnpj);
    }


    while (1) {
        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            entrada[strcspn(entrada, "\n")] = '\0';
            if (entrada[0] == 'q' || entrada[0] == 'Q') {
                printf("Operacao cancelada pelo usuario.\n");
                return 0;
            }
            if (sscanf(entrada, "%d", &entradas[numEntradas].fornecedorId) != 1) {
                printf("Erro: Entrada invalida insira um numero: ");
            } else if (entradas[numEntradas].fornecedorId <= 0 ) {
                printf("Erro: o ID deve ser maior ou igual a 1. Tente novamente: ");
            } else if (entradas[numEntradas].fornecedorId > numFornecedores ) {
                printf("Erro: Fornecedor nao existe. Tente Novamente: ");
            } else {
                break;
            }
        } else {
            printf("Erro ao ler o ID. Tente novamente: ");
        }
    }

    entradas[numEntradas].id = numEntradas + 1;
    strcpy(entradas[numEntradas].nome, produtos[id-1].nome);
    entradas[numEntradas].quantidade = quantidade;
    obterDataDeEntrada(entradas[numEntradas].dataDeEntrada);

    produtos[id-1].quantidade += quantidade;
    numEntradas++;
    printf("Entrada registrada com sucesso!\n");
}

void registrarSaidaProduto() {
    system("cls");
    printf("Registro de Sa�da de Produto:\n");

    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    int id, quantidade;
    char entrada[50];

    printf("Produtos cadastrados:\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("ID: %d | Nome: %s | Quantidade: %d\n", produtos[i].id, produtos[i].nome, produtos[i].quantidade);
    }

    while (1) {
        printf("Digite o ID do produto para registrar a sa�da: ");
        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            entrada[strcspn(entrada, "\n")] = '\0';
            if (entrada[0] == 'q' || entrada[0] == 'Q') {
                printf("Opera��o cancelada pelo usu�rio.\n");
                return;
            }
            if (sscanf(entrada, "%d", &id) != 1 || id <= 0 || id > numProdutos) {
                printf("ID de produto inv�lido. Tente novamente.\n");
            } else {
                break;
            }
        }
    }

    while (1) {
        printf("Digite a quantidade a ser removida: ");
        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            entrada[strcspn(entrada, "\n")] = '\0';
            if (entrada[0] == 'q' || entrada[0] == 'Q') {
                printf("Opera��o cancelada pelo usu�rio.\n");
                return;
            }
            if (sscanf(entrada, "%d", &quantidade) != 1 || quantidade <= 0) {
                printf("Quantidade inv�lida. Deve ser um n�mero maior que zero. Tente novamente.\n");
            } else if (produtos[id - 1].quantidade < quantidade) {
                printf("Quantidade insuficiente em estoque. Dispon�vel: %d\n", produtos[id - 1].quantidade);
            } else {
                break;
            }
        }
    }

    strcpy(saidas[numSaidas].nome, produtos[id - 1].nome);
    saidas[numSaidas].idProduto = id;
    saidas[numSaidas].quantidade = quantidade;
    saidas[numSaidas].precoTotal = 0;

    char dataSaida[11];
    obterDataDeEntrada(dataSaida);
    strcpy(saidas[numSaidas].dataDeSaida, dataSaida);

    produtos[id - 1].quantidade -= quantidade;
    saidas[numSaidas].id = numSaidas + 1;
    numSaidas++;

    printf("Sa�da registrada com sucesso!\n");
}

void gerarAlertas() {

    system("cls");
    printf("Alertas de produtos proximos do vencimento e com estoque critico:\n");

    time_t currentTime = time(NULL);
    struct tm *currentDate = localtime(&currentTime);

    char currentDateStr[11];
    strftime(currentDateStr, sizeof(currentDateStr), "%d/%m/%Y", currentDate);

    for (int i = 0; i < numEntradas; i++) {
        if (produtos[i].quantidade < 5) {
            printf("Estoque baixo: Produto %s (ID: %d) - Quantidade: %d\n", produtos[i].nome, produtos[i].id, produtos[i].quantidade);
        }

        struct tm validadeDate = {0};
        sscanf(entradas[i].dataValidade, "%d/%d/%d", &validadeDate.tm_mday, &validadeDate.tm_mon, &validadeDate.tm_year);
        validadeDate.tm_mon -= 1;
        validadeDate.tm_year -= 1900;

        time_t validadeTime = mktime(&validadeDate);

        if (difftime(validadeTime, currentTime) <= 0) {
            printf("Produto %s (ID: %d) est� vencido.\n", produtos[i].nome, produtos[i].id);
        } else {
            struct tm proximaData = *currentDate;
            proximaData.tm_mday += 7;
            mktime(&proximaData);

            if (difftime(validadeTime, mktime(&proximaData)) <= 0) {
                printf("Produto %s (ID: %d) est� pr�ximo do vencimento.\n", produtos[i].nome, produtos[i].id);
            }
        }
    }
}

void cadastrarFornecedor() {

    system("cls");

    printf("\n==========================");

    printf(" Cadastrar Fornecedor ");

    printf("==========================\n\n");

    if (numFornecedores >= MAX_FORNECEDORES) {
        printf("Limite de fornecedores atingido.\n");
        return;
    }
    char entrada[50];


    printf("--> Caso queira sair digite 'q' ou 'Q' <--\n");


    printf("Digite o nome do fornecedor: ");
    while (1) {
        if (fgets(fornecedores[numFornecedores].nome, sizeof(fornecedores[numFornecedores].nome), stdin) != NULL) {
            fornecedores[numFornecedores].nome[strcspn(fornecedores[numFornecedores].nome, "\n")] = '\0';
            if (strcmp(fornecedores[numFornecedores].nome, "q") == 0 || strcmp(fornecedores[numFornecedores].nome, "Q") == 0) {
                printf("Operacao cancelada pelo usuario\n");
                return;
            }
            if (strlen(fornecedores[numFornecedores].nome) == 0) {
                printf("Erro: o nome do fornecedor nao pode estar vazio. Tente novamente: ");
            } else {
                break;
            }
        } else {
            printf("Entrada invalida. Tente novamente.\n");
        }
    }


    printf("Digite o contato do fornecedor: ");
    while (1) {
        if (fgets(fornecedores[numFornecedores].contato, sizeof(fornecedores[numFornecedores].contato), stdin) != NULL) {
            fornecedores[numFornecedores].contato[strcspn(fornecedores[numFornecedores].contato, "\n")] = '\0';
            if (strcmp(fornecedores[numFornecedores].contato, "q") == 0 || strcmp(fornecedores[numFornecedores].contato, "Q") == 0) {
                printf("Operacao cancelada pelo usuario\n");
                return;
            }
            if (strlen(fornecedores[numFornecedores].contato) == 0) {
                printf("Erro: o contato do fornecedor nao pode estar vazio. Tente novamente: ");
            } else {
                break;
            }
        } else {
            printf("Entrada invalida. Tente novamente.\n");
        }
    }


    printf("Digite o CNPJ do fornecedor(XX.XXX.XXX/0001-XX): ");
    while (1) {
        if (fgets(fornecedores[numFornecedores].cnpj, sizeof(fornecedores[numFornecedores].cnpj), stdin) != NULL) {
            fornecedores[numFornecedores].cnpj[strcspn(fornecedores[numFornecedores].cnpj, "\n")] = '\0';
            if (strcmp(fornecedores[numFornecedores].cnpj, "q") == 0 || strcmp(fornecedores[numFornecedores].cnpj, "Q") == 0) {
                printf("Operacao cancelada pelo usuario\n");
                return;
            }
            if (strlen(fornecedores[numFornecedores].cnpj) == 0) {
                printf("Erro: o cnpj do fornecedor nao pode estar vazio. Tente novamente: ");
            } else {
                break;
            }
        } else {
            printf("Entrada invalida. Tente novamente.\n");
        }
    }


    fornecedores[numFornecedores].id = numFornecedores + 1;
    fornecedores[numFornecedores].totalEntregas = 0;
    fornecedores[numFornecedores].entregasComAtraso = 0;
    fornecedores[numFornecedores].problemasQualidade = 0;
    numFornecedores++;

    printf("Fornecedor cadastrado com sucesso!\n");
}




//FUNCOES DESENVOLVIDAS PARA OS RELATORIOS
void relatorioProdutos() {
    system("cls");
    exibirTituloEFundo(9, 9, 15, "Relatorio de Produtos");

    for (int i = 0; i < numProdutos; i++) {


        printf(" Nome: %s | ",  produtos[i].nome);

        printf("ID: %d | Preco: %.2f | Quantidade: %d \n",
               produtos[i].id, produtos[i].preco, produtos[i].quantidade);
    }
}

void relatorioFornecedores() {
    system("cls");

    exibirTituloEFundo(13, 13, 15, "Relatorio de Fornecedores");



    for (int i = 0; i < numFornecedores; i++) {

        printf("\n==========================");

        printf(" Nome: %s ", fornecedores[i].nome);

        printf("==========================\n\n");


        printf("ID: %d | Contato: %s | CNPJ: %s \n",
                fornecedores[i].id, fornecedores[i].contato, fornecedores[i].cnpj);
        printf("        Total Entregas: %d | Entregas com Atraso: %d | Problemas de Qualidade: %d\n",
                fornecedores[i].totalEntregas, fornecedores[i].entregasComAtraso, fornecedores[i].problemasQualidade);
    }
}

void relatorioEntradas() {
    system("cls");
    exibirTituloEFundo(2, 2, 15, "Relatorio de Entradas");
    if(numEntradas < 0 || !numEntradas){
        printf("Nao existem entradas esse mes!\n");
        return;
    }

    for (int i = 0; i < numEntradas; i++) {
        printf("\n==========================");
        printf(" Nome: %s ", entradas[i].nome);
        printf("==========================\n\n");

        printf("Preco: R$ %.2f | Quantidade: %d KG | Data de Entrada: %s | Data de Validade: %s\n",
                entradas[i].preco, entradas[i].quantidade, entradas[i].dataDeEntrada, entradas[i].dataValidade);
    }
}

void relatorioSaidas() {
    system("cls");
    exibirTituloEFundo(12, 12, 15, "Relatorio de saidas");


    for (int i = 0; i < numSaidas; i++) {
        printf("\n==========================");
        printf(" ID: %d ", saidas[i].id);
        printf("==========================\n\n");
        printf("Id do produto: %d | Nome do produto: %s || Preco: R$ %.2f\n",
                saidas[i].idProduto, saidas[i].nome, saidas[i].precoTotal);
        printf("        Quantidade: %d | Data da saida: %s \n",
                saidas[i].quantidade, saidas[i].dataDeSaida);
    }
}

//RELATORIOS DE ENTRADAS (TODO)

//MENU DE TODAS AS OPCOES DE NAVEGACAO
void menu() {
    int opcao = 0;
    int ch;
    const char *menuOptions[10] = {
        "Cadastrar Produto",
        "Registrar Entrada de Produto",
        "Registrar Saida de Produto",
        "Gerar Alertas de Estoque",
        "Cadastrar Fornecedor",
        "Relatorio de Produtos",
        "Relatorio de Fornecedores",
        "Relatorio de Entradas",
        "Relatorio de Saidas",
        "Sair"
    };

    do {
        exibirTitulo();
        printf("--- Menu de Controle de Estoque ---\n");

        for (int i = 0; i < 10; i++) {
            if (i == opcao) {

                printf("-> ");
            } else {
                printf("   ");
            }
            printf("%d. %s\n", i + 1, menuOptions[i]);

        }
        printf("\nUse as setas para navegar e Enter para selecionar.\n");

        ch = _getch();

        if (ch == 224) {
            ch = _getch();
            if (ch == 72) {
                opcao = (opcao == 0) ? 9 : opcao - 1;
            } else if (ch == 80) {
                opcao = (opcao == 9) ? 0 : opcao + 1;
            }
        } else if (ch == 13) {
            configurarTelaPrincipal();
            printf("Opcao selecionada: %s\n", menuOptions[opcao]);
            carregarAnimacao();
            switch(opcao + 1) {
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
                case 8:
                    relatorioEntradas();
                    break;
                case 9:
                    relatorioSaidas();
                    break;
                case 10:
                    printf("Saindo do sistema...\n");
                    return;
                    break;
                default:
                    printf("Opcao invalida.\n");
            }
            if (opcao != 10) {
                printf("\nPressione qualquer tecla para continuar...");
                getchar();
                getchar();
            }
        }
    } while(opcao != 10);
}

int main() {
    configurarTelaPrincipal();
    menu();
    return 0;
}
