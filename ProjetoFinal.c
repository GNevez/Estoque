// Autor: Guilherme Neves M Ferraz
// Matricula: UC23100623
// Instituição: UCB - Universidade Catolica de Brasilia
// Professora: Hially Rabelo

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_USUARIOS 1000

struct cadastro_usuario
{
    int id;
    char nome[100];
    char email[100];
    char sexo[3];
    char endereco[200];
    double altura;
    int vacina;
};

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
// ^ isso aqui é so pra limpar o buffer, usado dps dos scanf
void cadastrarUsuario(struct cadastro_usuario usuarios[MAX_USUARIOS], int indice)
{
    struct cadastro_usuario *usuario = &usuarios[indice];

    printf("\n ----------------CADASTRO DE USUARIO---------------- \n \n \n");

    usuario->id = indice + 1;

    printf("Digite o seu nome: \n");
    fgets(usuario->nome, sizeof(usuario->nome), stdin);

    bool contemArroba = false;
    do{
    printf("Digite seu email: \n");
    fgets(usuario->email, sizeof(usuario->email), stdin);

    size_t lengthEmail = strlen(usuario->email);
    if (lengthEmail > 0 && usuario->email[lengthEmail - 1] == '\n')
    {
        usuario->email[lengthEmail - 1] = '\0';
    }
    // debugar a parada quando aperta enter ^
    
    for (size_t i = 0; i < lengthEmail; ++i)
    {
        if (usuario->email[i] == '@')
        {
            contemArroba = true;
            break;
        }
    }
    }while(contemArroba == false);
    // verifica o @ ^

    printf("Digite seu endereco: \n");
    fgets(usuario->endereco, sizeof(usuario->endereco), stdin);
    size_t lengthEndereco = strlen(usuario->endereco);
    if (lengthEndereco > 0 && usuario->endereco[lengthEndereco - 1] == '\n')
    {
        usuario->endereco[lengthEndereco - 1] = '\0';
    }

    int respostaValida = 0;
    while (!respostaValida)
    {
        printf("Qual o seu sexo (H) = Homem / (M) = Mulher \n");
        fgets(usuario->sexo, sizeof(usuario->sexo), stdin);
        size_t lengthSexo = strlen(usuario->sexo);
        if (lengthSexo > 0 && usuario->sexo[lengthSexo - 1] == '\n')
        {
            usuario->sexo[lengthSexo - 1] = '\0';
        }
        else
        {
            limparBuffer();
        }

        if (strcmp(usuario->sexo, "H") == 0 || strcmp(usuario->sexo, "h") == 0 || strcmp(usuario->sexo, "M") == 0 || strcmp(usuario->sexo, "m") == 0)
        {
            respostaValida = 1;
        }
        else
        {
            printf("Resposta inválida! \n");
        }
        // verifica se foi digitado outra coisa alem de H ou M
    }

    printf("Digite a sua altura em metro (Ex: 1.80): \n");
    scanf("%lf", &usuario->altura);
    limparBuffer();

    printf("Voce e vacinado? (1) = SIM / (0) = NAO \n");
    while (scanf("%d", &usuario->vacina) != 1 || (usuario->vacina != 0 && usuario->vacina != 1))
    {
        printf("Entrada invalida. Por favor, digite novamente (1) = SIM / (0) = NAO: \n");
        limparBuffer();
    }

    char EVacinado[4];

    if (usuario->vacina == 1)
    {
        strcpy(EVacinado, "Sim");
    }
    else
    {
        strcpy(EVacinado, "Nao");
    }
    // substitui o 1 e 0 por Sim e Nao

    printf("\n -----------INFORMACOES DO USUARIO----------- \n \n");
    printf("Nome: %s \n", usuario->nome);
    printf("Email: %s \n", usuario->email);
    printf("Sexo: %s \n", usuario->sexo);
    printf("Endereco: %s \n", usuario->endereco);
    printf("Altura: %.2lf\n", usuario->altura);
    printf("E Vacinado? %s \n", EVacinado);

    printf("Cadastro concluido. Obrigado!\n");
}

int buscarPorId(struct cadastro_usuario usuarios[MAX_USUARIOS], int id)
{
    for (int i = 0; i < MAX_USUARIOS; ++i)
    {
        if (usuarios[i].id == id)
        {
            return i;
        }
    }
    return -1;

    // busca o id do usuario percorrendo a array e retorna o indice do array
}

void imprimirTodosUsuarios(struct cadastro_usuario usuarios[MAX_USUARIOS], int totalUsuarios){
    printf("\n ----------- TODOS OS USUARIOS CADASTRADOS ----------- \n \n");
    for (int i = 0; i < totalUsuarios; ++i)
    {
        printf("ID: %d\n", usuarios[i].id);
        printf("Nome: %s \n", usuarios[i].nome);
        printf("Email: %s \n", usuarios[i].email);
        printf("Sexo: %s \n", usuarios[i].sexo);
        printf("Endereco: %s \n", usuarios[i].endereco);
        printf("Altura: %.2lf\n", usuarios[i].altura);
        printf("E Vacinado? %s \n", (usuarios[i].vacina == 1) ? "Sim" : "Nao");
        printf("---------------------------------------------------\n");
    }
    // imprime todos usuarios
}

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

    // isso aqui era pra tirar os espaços e \n do email pq tava bugando quando ia buscar usuario por email
}

struct cadastro_usuario *buscarPorEmail(struct cadastro_usuario usuarios[MAX_USUARIOS], const char *email)
{
    for (int i = 0; i < MAX_USUARIOS; ++i)
    {
        if (formatadorStr(usuarios[i].email, email) == 0)
        {
            return &usuarios[i];
        }
    }
    return NULL;

    // busca o usuario por email e retorna as o usuario direto
}

void editarUsuario(struct cadastro_usuario *usuario)
{
    int opcao;

    printf("Escolha o campo a ser editado: \n");
    printf("1 - Nome\n");
    printf("2 - Email\n");
    printf("3 - Altura\n");
    printf("4 - Endereco\n");
    printf("0 - Sair\n");
    printf("Digite a opcao: ");
    scanf("%d", &opcao);
    limparBuffer();

    switch (opcao)
    {
    case 1:
        printf("Digite o novo nome: ");
        fgets(usuario->nome, sizeof(usuario->nome), stdin);
        break;

    case 2:
        printf("Digite o novo email: ");
        fgets(usuario->email, sizeof(usuario->email), stdin);
        size_t lengthEmail = strlen(usuario->email);
        if (lengthEmail > 0 && usuario->email[lengthEmail - 1] == '\n')
        {
            usuario->email[lengthEmail - 1] = '\0';
        }
        break;

    case 3:
        printf("Digite a nova altura: ");
        scanf("%lf", &usuario->altura);
        limparBuffer();
        break;

    case 4:
        printf("Digite o novo endereco: ");
        fgets(usuario->endereco, sizeof(usuario->endereco), stdin);
        break;

    case 0:
        break;

    default:
        printf("Opcao invalida.\n");
    }

    // substitui as variaveis do objeto que está inserido o usuario buscado
}

void excluirUsuario(struct cadastro_usuario usuarios[MAX_USUARIOS], int *totalUsuarios, int idExcluir)
{
    int indiceExcluir = -1;

    for (int i = 0; i < *totalUsuarios; ++i)
    {
        if (usuarios[i].id == idExcluir)
        {
            indiceExcluir = i;
            break;
        }
    }

    if (indiceExcluir != -1)
    {
        for (int i = indiceExcluir; i < *totalUsuarios - 1; ++i)
        {
            usuarios[i] = usuarios[i + 1];
        }

        (*totalUsuarios)--;

        printf("Usuario excluido com sucesso!\n");
    }
    else
    {
        printf("Usuario nao encontrado por ID.\n");
    }

    // transforma o indice do usuario que é para excluir em -1
}

int main()
{
    struct cadastro_usuario usuarios[MAX_USUARIOS];

    int totalUsuarios = 0;
    int continuarCadastro = 1;

    while (totalUsuarios < MAX_USUARIOS && continuarCadastro)
    {
        cadastrarUsuario(usuarios, totalUsuarios);
        totalUsuarios++;

        printf("\nDeseja continuar cadastrando? (1 = Sim / 0 = Nao): ");
        scanf("%d", &continuarCadastro);
        limparBuffer();
    }

    printf("\n --------------Total de usuarios cadastrados: %d--------------\n", totalUsuarios);

    int ProcurarC;
    int idBuscado;
    char emailBuscado[100];
    int indiceUsuario;

    // menu de opções
    do
    {
        printf("Selecione uma das opcoes: \n1 = Procurar por ID \n2 = Procurar por Email \n3 = Cadastrar mais usuarios \n4 = Editar informacoes de um usuario \n5 = Excluir um usuario \n6 = Imprimir todos os usuarios \n7 = Fechar programa \nDigite: ");
        scanf("%d", &ProcurarC);
        limparBuffer();

        switch (ProcurarC)
        {
        case 1:
            printf("Digite o ID do usuario cadastrado: \n");
            scanf("%d", &idBuscado);

            indiceUsuario = buscarPorId(usuarios, idBuscado);

            if (indiceUsuario != -1)
            {
                struct cadastro_usuario *usuarioPorId = &usuarios[indiceUsuario];
                printf("Id: %d \n", usuarioPorId->id);
                printf("Nome: %s \n", usuarioPorId->nome);
                printf("Email: %s \n", usuarioPorId->email);
                printf("Sexo: %s \n", usuarioPorId->sexo);
                printf("Endereco: %s \n", usuarioPorId->endereco);
                printf("Altura: %.2lf\n", usuarioPorId->altura);
                printf("E Vacinado? %s \n", (usuarioPorId->vacina == 1) ? "Sim" : "Nao");
            }
            else
            {
                printf("Usuario nao encontrado por ID.\n");
            }
            break;

        case 2:
            printf("Digite o Email do usuario cadastrado: \n");
            fgets(emailBuscado, sizeof(emailBuscado), stdin);

            struct cadastro_usuario *usuarioPorEmail = buscarPorEmail(usuarios, emailBuscado);

            if (usuarioPorEmail != NULL)
            {
                printf("\n -----------INFORMACOES DO USUARIO ENCONTRADO POR EMAIL ----------- \n \n");
                printf("ID: %d\n", usuarioPorEmail->id);
                printf("Nome: %s \n", usuarioPorEmail->nome);
                printf("Email: %s \n", usuarioPorEmail->email);
                printf("Sexo: %s \n", usuarioPorEmail->sexo);
                printf("Endereco: %s \n", usuarioPorEmail->endereco);
                printf("Altura: %.2lf\n", usuarioPorEmail->altura);
                printf("E Vacinado? %s \n", (usuarioPorEmail->vacina == 1) ? "Sim" : "Nao");
            }
            else
            {
                printf("Usuario nao encontrado por email.\n");
            }
            break;

        case 3:
            cadastrarUsuario(usuarios, totalUsuarios);
            totalUsuarios++;
            break;

        case 4:
            printf("Digite o ID do usuario a ser editado: \n");
            scanf("%d", &idBuscado);

            indiceUsuario = buscarPorId(usuarios, idBuscado);

            if (indiceUsuario != -1)
            {
                editarUsuario(&usuarios[indiceUsuario]);
                printf("Usuario editado com sucesso!\n");
            }
            else
            {
                printf("Usuario nao encontrado por ID.\n");
            }
            break;

        case 5:
            printf("Digite o ID do usuario a ser excluido: ");
            scanf("%d", &idBuscado);
            limparBuffer();
            excluirUsuario(usuarios, &totalUsuarios, idBuscado);
            break;

        case 6:
            imprimirTodosUsuarios(usuarios, totalUsuarios);
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
}
