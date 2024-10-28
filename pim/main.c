#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

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
    {1, "Maca", 2000, 10, "10/12/2024", "28/10/2024", 1},
    {2, "Maca", 3000, 15, "30/12/2024", "27/10/2024", 1}
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

void pegarCor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void pegarCorEFundo(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor | (bgColor << 4));
}

void definirCorDeFundo(int corFundo) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        int cor = (csbi.wAttributes & 0x0F) | (corFundo << 4);
        SetConsoleTextAttribute(hConsole, cor);
    }
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
    pegarCor(11);
    printf("\n==========================");
    pegarCor(14);
    printf("  Bem vindo ao Little Bird  ");
    pegarCor(11);
    printf("==========================\n\n");
}

void exibirTituloPersonalizado(int corTexto,int corBarra, char texto[250]) {
    system("cls");
    pegarCor(corBarra);
    printf("\n==========================");
    pegarCor(corTexto);
    printf(" %s ", texto);
    pegarCor(corBarra);
    printf("==========================\n\n");
}

void exibirTituloEFundo(int corTexto,int corBarra, int fundo, char texto[250]) {
    system("cls");
    pegarCorEFundo(corBarra, fundo);
    printf("\n==========================");
    pegarCorEFundo(corTexto, fundo);
    printf(" %s ", texto);
    pegarCorEFundo(corBarra, fundo);
    printf("==========================\n\n");
}




//FUNCOES DESENVOLVIDAS PARA SEREM USADAS NAS GESTOES DOS PRODUTOS
void cadastrarProduto() {
    system("cls");
    exibirTituloPersonalizado(14, 11, "Cadastrar Produto");
    pegarCor(7);

    if (numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }

    produtos[numProdutos].id = numProdutos + 1;

    printf("Digite o nome do produto: ");
    fgets(produtos[numProdutos].nome, sizeof(produtos[numProdutos].nome), stdin);

    produtos[numProdutos].nome[strcspn(produtos[numProdutos].nome, "\n")] = 0;

    printf("Digite o preco do produto (KG) R$ ");
    while (scanf("%f", &produtos[numProdutos].preco) != 1) {
        printf("Entrada inválida. Digite um número válido para o preço: ");
        while (getchar() != '\n');
    }

    numProdutos++;
    printf("Produto cadastrado com sucesso!\n");
}

void registrarEntradaProduto() {
    system("cls");
    exibirTituloPersonalizado(14, 11, "Registrar Entrada do produto");
    pegarCor(7);

    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }


    int id, quantidade;
    float preco;
    printf("---- Digite o ID do produto para registrar a entrada ----\n");

    printf("Produtos cadastrados:\n");
    for (int i = 0; i < numProdutos; i++) {
        pegarCorEFundo(11, 0);
        printf(" ID: %d", produtos[i].id);
        pegarCorEFundo(8, 0);
        printf(" | Nome: %s \n", produtos[i].nome);
    }
    pegarCorEFundo(15, 0);
    printf("\n");
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

    printf("\n---- Digite o ID do fornecedor ----\n");
    printf("Fornecedores cadastrados:\n");
    for (int i = 0; i < numFornecedores; i++) {
        pegarCorEFundo(11, 0);
        printf(" ID: %d", fornecedores[i].id);
        pegarCorEFundo(8, 0);
        printf(" | Nome: %s | CNPJ: %s \n", fornecedores[i].nome, fornecedores[i].cnpj);
    }
    pegarCorEFundo(15, 0);
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
    alterarCorConsole("4F");
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
    alterarCorConsole("6F");
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
    definirCorDeFundo(9);
    system("cls");
    pegarCorEFundo(15, 9);
    printf("\n==========================");
    pegarCorEFundo(15, 9);
    printf(" Cadastrar Fornecedor ");
    pegarCorEFundo(15, 9);
    printf("==========================\n\n");

    if (numFornecedores >= MAX_FORNECEDORES) {
        printf("Limite de fornecedores atingido.\n");
        return;
    }


    printf("Digite o nome do fornecedor: ");
    fgets(fornecedores[numFornecedores].nome, sizeof(fornecedores[numFornecedores].nome), stdin);
    fornecedores[numFornecedores].nome[strcspn(fornecedores[numFornecedores].nome, "\n")] = 0;

    printf("Digite o contato do fornecedor: ");
    fgets(fornecedores[numFornecedores].contato, sizeof(fornecedores[numFornecedores].contato), stdin);
    fornecedores[numFornecedores].contato[strcspn(fornecedores[numFornecedores].contato, "\n")] = 0;

    printf("Digite o CNPJ do fornecedor(XX.XXX.XXX/0001-XX): ");
    fgets(fornecedores[numFornecedores].cnpj, sizeof(fornecedores[numFornecedores].cnpj), stdin);
    fornecedores[numFornecedores].cnpj[strcspn(fornecedores[numFornecedores].cnpj, "\n")] = 0;

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
    definirCorDeFundo(15);
    exibirTituloEFundo(9, 9, 15, "Relatorio de Produtos");
    pegarCorEFundo(8, 15);

    for (int i = 0; i < numProdutos; i++) {

        pegarCorEFundo(0, 15);
        printf(" Nome: %s | ",  produtos[i].nome);
        pegarCorEFundo(8, 15);
        printf("ID: %d | Preco: %.2f | Quantidade: %d \n",
               produtos[i].id, produtos[i].preco, produtos[i].quantidade);
    }
}

void relatorioFornecedores() {
    system("cls");
    definirCorDeFundo(15);
    exibirTituloEFundo(13, 13, 15, "Relatorio de Fornecedores");
    pegarCorEFundo(8, 15);


    for (int i = 0; i < numFornecedores; i++) {
        pegarCorEFundo(0, 15);
        printf("\n==========================");
        pegarCorEFundo(0, 15);
        printf(" Nome: %s ", fornecedores[i].nome);
        pegarCorEFundo(0, 15);
        printf("==========================\n\n");

        pegarCorEFundo(8, 15);
        printf("ID: %d | Contato: %s | CNPJ: %s \n",
                fornecedores[i].id, fornecedores[i].contato, fornecedores[i].cnpj);
        printf("        Total Entregas: %d | Entregas com Atraso: %d | Problemas de Qualidade: %d\n",
                fornecedores[i].totalEntregas, fornecedores[i].entregasComAtraso, fornecedores[i].problemasQualidade);
    }
}

void relatorioEntradas() {
    system("cls");
    definirCorDeFundo(15);
    exibirTituloEFundo(2, 2, 15, "Relatorio de Entradas");
    pegarCorEFundo(8, 15);

    if(numEntradas < 0 || !numEntradas){
        printf("Nao existem entradas esse mes!\n");
        return;
    }

    for (int i = 0; i < numEntradas; i++) {
        pegarCorEFundo(0, 15);
        printf("\n==========================");
        pegarCorEFundo(0, 15);
        printf(" Nome: %s ", entradas[i].nome);
        pegarCorEFundo(0, 15);
        printf("==========================\n\n");
        pegarCorEFundo(8, 15);

        printf("Preco: R$ %.2f | Quantidade: %d KG | Data de Entrada: %s | Data de Validade: %s\n",
                entradas[i].preco, entradas[i].quantidade, entradas[i].dataDeEntrada, entradas[i].dataValidade);
    }
}

void relatorioSaidas() {
    system("cls");
    definirCorDeFundo(15);
    exibirTituloEFundo(12, 12, 15, "Relatorio de saidas");
    pegarCorEFundo(8, 15);


    for (int i = 0; i < numSaidas; i++) {
        pegarCorEFundo(0, 15);
        printf("\n==========================");
        pegarCorEFundo(0, 15);
        printf(" ID: %d ", saidas[i].id);
        pegarCorEFundo(0, 15);
        printf("==========================\n\n");
        pegarCorEFundo(8, 15);

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
        pegarCor(7);
        for (int i = 0; i < 10; i++) {
            if (i == opcao) {
                pegarCor(14);
                printf("-> ");
            } else {
                printf("   ");
            }
            printf("%d. %s\n", i + 1, menuOptions[i]);
            pegarCor(7);
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
                    break;
                default:
                    printf("Opcao invalida.\n");
            }
            if (opcao != 9) {
                printf("\nPressione qualquer tecla para continuar...");
                getchar();
                getchar();
                alterarCorConsole("0F");
            }
        }
    } while(opcao != 9);
}

int main() {
    configurarTelaPrincipal();
    menu();
    return 0;
}
