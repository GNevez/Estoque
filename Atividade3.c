// Autor: Guilherme Neves M Ferraz
// Matricula: UC23100623
// Instituição: UCB - Universidade Catolica de Brasilia
// Professora: Hially Rabelo

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_produtos 1000

struct cadastro_produtos
{
    int codigo;
    char nome[100];
    char Marca[100];
    int Quantidade;
    char Descricao[200];
    double Valor;
};
// struct construtora dos produtos

// isso aqui é so pra limpar o buffer, usado dps dos scanf
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Função que cadastra os produtos
void cadastrarProduto(struct cadastro_produtos produtos[MAX_produtos], int indice)
{
    struct cadastro_produtos *Produto = &produtos[indice];

    printf("\n ----------------CADASTRO DE PRODUTOS---------------- \n \n \n");

    int input;
    int isNumero;

    do {
        printf("Digite o codigo do produto: \n");
        isNumero = scanf("%d", &input);
        limparBuffer();

        if (isNumero) {
            Produto->codigo = input;
            break;
        } else {
            printf("Codigo invalido. Tente novamente.\n");
        }
    } while (1);


    printf("Digite o nome do produto: \n");
    fgets(Produto->nome, sizeof(Produto->nome), stdin);


    printf("Digite a marca do produto: \n");
    fgets(Produto->Marca, sizeof(Produto->Marca), stdin);

    size_t lengthMarca = strlen(Produto->Marca);
    if (lengthMarca > 0 && Produto->Marca[lengthMarca - 1] == '\n')
    {
        Produto->Marca[lengthMarca - 1] = '\0';
    }
    // debugar a parada quando aperta enter ^
    
    printf("Digite a descricao do produto: \n");
    fgets(Produto->Descricao, sizeof(Produto->Descricao), stdin);
    size_t lengthDescricao = strlen(Produto->Descricao);
    if (lengthDescricao > 0 && Produto->Descricao[lengthDescricao - 1] == '\n')
    {
        Produto->Descricao[lengthDescricao - 1] = '\0';
    }

    printf("Digite a quantidade desse produto \n");
    scanf("%d", &Produto->Quantidade);
    limparBuffer();

        
    printf("Digite o valor do produto: \n");
    scanf("%lf", &Produto->Valor);
    limparBuffer();


    printf("\n -----------INFORMACOES DO Produto----------- \n \n");
    printf("Nome: %s \n", Produto->nome);
    printf("Marca: %s \n", Produto->Marca);
    printf("Quantidade: %d \n", Produto->Quantidade);
    printf("Descricao: %s \n", Produto->Descricao);
    printf("Valor: %.2lf\n", Produto->Valor);

    printf("Cadastro concluido. Obrigado!\n");
    printf("\n \n \n");
}

// Função que busca os produtos por codigo
int buscarPorcodigo(struct cadastro_produtos produtos[MAX_produtos], int codigo)
{
    for (int i = 0; i < MAX_produtos; ++i)
    {
        if (produtos[i].codigo == codigo)
        {
            return i;
        }
    }
    return -1;

    // busca o codigo do produto percorrendo a array e retorna o indice do array
}

// Exibe o relatorio de todas informações cadastradas do produto
void relatorioProdutos(struct cadastro_produtos produtos[MAX_produtos], int totalprodutos){
    printf("\n -----------TODOS OS PRODUTOS CADASTRADOS----------- \n \n");
    if(totalprodutos >= 1){
    for (int i = 0; i < totalprodutos; ++i)
    {
        printf("Codigo: %d\n", produtos[i].codigo);
        printf("Nome: %s \n", produtos[i].nome);
        printf("Marca: %s \n", produtos[i].Marca);
        printf("Quantidade: %d \n", produtos[i].Quantidade);
        printf("Descricao: %s \n", produtos[i].Descricao);
        printf("Valor: %.2lf\n", produtos[i].Valor);
        printf("---------------------------------------------------\n");
    }
    }
    else{
        printf("---------------------------------------------------\n");
        printf("Nenhum produto encontrado, retorne as opcoes iniciais e pressione 3 para cadastrar um produto.");
        printf("\n---------------------------------------------------\n");
    }
    // imprime todos produtos
}

// Formatador de string para desbugar a função de procurar o produto pelo nome
int formatadorStr(const char *str1, const char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 == ' ' || *str1 == '\n')
        {
            str1++;
            continue;
        }

        if (*str2 == ' ' || *str2 == '\n')
        {
            str2++;
            continue;
        }

        char ch1 = tolower((unsigned char)*str1);
        char ch2 = tolower((unsigned char)*str2);

        if (ch1 != ch2)
        {
            return ch1 - ch2;
        }

        str1++;
        str2++;
    }

    while (*str1 && (*str1 == ' ' || *str1 == '\n'))
    {
        str1++;
    }

    while (*str2 && (*str2 == ' ' || *str2 == '\n'))
    {
        str2++;
    }

    return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);

    // isso aqui era pra tirar os espaços e \n do nome pq tava bugando quando ia buscar usuario por nome
}

// Função que percorre o array de nomes imprime as informações do produto
struct cadastro_produtos *buscarPorNome(struct cadastro_produtos produtos[MAX_produtos], const char *Nome)
{
    for (int i = 0; i < MAX_produtos; ++i)
    {
        if (formatadorStr(produtos[i].nome, Nome) == 0)
        {
            return &produtos[i];
        }
    }
    return NULL;

}

// Função para editar informações dos produtos
void editarProduto(struct cadastro_produtos *Produto)
{
    int opcao;
    printf("\n ---------------------------------- \n \n");
    printf("Escolha o campo a ser editado: \n");
    printf("1 - Nome\n");
    printf("2 - Marca\n");
    printf("3 - Quantidade\n");
    printf("4 - Descricao\n");
    printf("5 - Valor\n");
    printf("0 - Sair\n");
    printf("\n ----------------------------------");
    printf("Digite a opcao: ");
    scanf("%d", &opcao);
    limparBuffer();

    switch (opcao)
    {
    case 1:
        printf("Digite o novo nome: ");
        fgets(Produto->nome, sizeof(Produto->nome), stdin);
        break;

    case 2:
        printf("Digite a nova Marca: ");
        fgets(Produto->Marca, sizeof(Produto->Marca), stdin);
        size_t lengthMarca = strlen(Produto->Marca);
        if (lengthMarca > 0 && Produto->Marca[lengthMarca - 1] == '\n')
        {
            Produto->Marca[lengthMarca - 1] = '\0';
        }
        break;

    case 3:
        printf("Digite a nova quantidade: ");
        scanf("%d", &Produto->Quantidade);
        limparBuffer();
        break;

    case 4:
        printf("Digite a nova descricao: ");
        fgets(Produto->Descricao, sizeof(Produto->Descricao), stdin);
        break;

    case 5:
        printf("Digite o novo valor: ");
        scanf("%lf", &Produto->Valor);
        limparBuffer();
        break;

    case 0:
        break;

    default:
        printf("Opcao invalida.\n");
    }

    // substitui as variaveis do objeto que está inserido o Produto buscado
}

// Função que subtrai a quantidade do produto escolhido, caso a quantidade de produtos excluidos for maior que a quantidade em estoque o produto é excluido do estoque
void excluirProduto(struct cadastro_produtos produtos[MAX_produtos], int *totalprodutos, int codigoExcluir, int itensExcluidos)
{
    int indiceExcluir = -1;

    for (int i = 0; i < *totalprodutos; ++i)
    {
        if (produtos[i].codigo == codigoExcluir)
        {
            indiceExcluir = i;
            break;
        }
    }

    if (indiceExcluir != -1)
    {
        // for (int i = indiceExcluir; i < *totalprodutos - 1; ++i)
        // {
        //     produtos[i] = produtos[i + 1];
        // }

        
        if (produtos[indiceExcluir].Quantidade <= itensExcluidos)
        {

            (*totalprodutos)--;
            printf("\n-----------------------------------\n");
            printf("Produto excluido com sucesso!\n");
            printf("\n-----------------------------------\n");
        }
        else
        {
            produtos[indiceExcluir].Quantidade -= itensExcluidos;

            printf("\n-----------------------------------\n");
            printf("%d itens foram excluidos do estoque de %s\n", itensExcluidos, produtos[indiceExcluir].nome);
            printf("\n-----------------------------------\n");
        }

    }
    else
    {
        printf("\n-----------------------------------\n");
        printf("Produto nao encontrado por codigo.\n");
        printf("\n-----------------------------------\n");
    }
}

// Função Main
int main()
{
    struct cadastro_produtos produtos[MAX_produtos];

    int totalprodutos = 0;

    int ProcurarC;
    int codigoBuscado;
    char NomeBuscado[100];
    int indiceProduto;
    int itensExcluido;

    // menu de opções com laço de repetições ate que o programa seja encerrado
    do
    {   
        printf("\n------------------------------------------ \n");
        printf("Selecione uma das opcoes: \n\n1 = Procurar produto pelo codigo \n2 = Procurar produto por nome \n3 = Cadastrar um novo produto \n4 = Editar informacoes de um produto \n5 = Remover produto do estoque \n6 = Listar produtos e informacoes \n7 = Fechar programa \nDigite: ");
        scanf("%d", &ProcurarC);
        limparBuffer();

        switch (ProcurarC)
        {
        case 1:
            printf("Digite o codigo do produto cadastrado: \n");
            scanf("%d", &codigoBuscado);

            indiceProduto = buscarPorcodigo(produtos, codigoBuscado);

            if (indiceProduto != -1)
            {
                struct cadastro_produtos *ProdutoPorcodigo = &produtos[indiceProduto];
                printf("\n ----------------INFORMACOES DO PRODUTO ENCONTRADO--------------- \n \n");
                printf("Codigo: %d \n", ProdutoPorcodigo->codigo);
                printf("Nome: %s \n", ProdutoPorcodigo->nome);
                printf("Marca: %s \n", ProdutoPorcodigo->Marca);
                printf("Quantidade: %d \n", ProdutoPorcodigo->Quantidade);
                printf("Descricao: %s \n", ProdutoPorcodigo->Descricao);
                printf("Valor: %.2lf\n", ProdutoPorcodigo->Valor);
                printf("\n ----------------------------------------------------- \n \n");
            }
            else
            {
                printf("Produto nao cadastrado no sistema.\n");
            }
            break;

        case 2:
            printf("Digite o nome do produto cadastrado: \n");
            fgets(NomeBuscado, sizeof(NomeBuscado), stdin);

            struct cadastro_produtos *ProdutoPorNome = buscarPorNome(produtos, NomeBuscado);

            if (ProdutoPorNome != NULL)
            {
                printf("\n -----------INFORMACOES DO PRODUTO ENCONTRADO----------- \n \n");
                printf("codigo: %d \n", ProdutoPorNome->codigo);
                printf("Nome: %s \n", ProdutoPorNome->nome);
                printf("Marca: %s \n", ProdutoPorNome->Marca);
                printf("Quantidade: %d \n", ProdutoPorNome->Quantidade);
                printf("Descricao: %s \n", ProdutoPorNome->Descricao);
                printf("Valor: %.2lf\n", ProdutoPorNome->Valor);
                printf("\n ----------------------------------------------------- \n \n");
            }
            else
            {
                printf("Produto nao cadastrado no sistema.\n");
            }
            break;

        case 3:
            cadastrarProduto(produtos, totalprodutos);
            totalprodutos++;
            break;

        case 4:
            printf("Digite o codigo do Produto a ser editado: \n");
            scanf("%d", &codigoBuscado);

            indiceProduto = buscarPorcodigo(produtos, codigoBuscado);

            if (indiceProduto != -1)
            {
                editarProduto(&produtos[indiceProduto]);
                printf("Produto editado com sucesso!\n");
            }
            else
            {
                printf("Produto nao encontrado por codigo.\n");
            }
            break;

        case 5:
            printf("Digite o codigo do Produto a ser excluido: ");
            scanf("%d", &codigoBuscado);
            limparBuffer();
            printf("Digite a quantidade de itens a serem excluidos: ");
            scanf("%d", &itensExcluido);
            limparBuffer();

            excluirProduto(produtos, &totalprodutos, codigoBuscado, itensExcluido);
            break;

        case 6:
            relatorioProdutos(produtos, totalprodutos);
            break;

        case 7:
            printf("Programa encerrado, Ate mais!\n");
            return 0;
        default:
            printf("Opcao invalida.\n");
        }

        printf("\nDeseja voltar as opcoes? (1 = Sim / 0 = Nao): ");
        scanf("%d", &ProcurarC);
        limparBuffer();

    } while (ProcurarC == 1);

    return 0;
    // Cada caso chama uma função.
}
