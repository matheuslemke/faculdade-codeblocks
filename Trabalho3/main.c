#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int poliglota_salario(int n);
int base_salario(int escalao, int base);
int formacao(int n);
float salario(int grau, int linguas, int escalao, float indice);
void bubble(float *vet, int n);

typedef struct
{
    int dia, mes, ano;
} date;

typedef struct
{
    char nome[255],
         sexo;
    int grau,
        escalao,
        linguas;
    float indice,
          idade,
          salario;
    date data;
} Funcionario;

int formacao(int n)
{
    if (n == 1)
        return 1;
    else
        return n * (formacao(n - 1));
}

int poliglota_salario(int n)
{
    return n*n;
}

int base_salario(int escalao, int base)
{
    switch (escalao)
    {
    case 1:
        base = 10;
        break;
    case 2:
        base = 5;
        break;
    case 3:
        base = 2;
        break;
    }
    return (1000 * base);
}

float salario(int grau, int linguas, int escalao, float indice)
{
    float salario;
    if (indice > 0.7)
        salario = (float) (base_salario(escalao, 0) + (float) (formacao(grau)*100) + (float) (poliglota_salario(linguas)*50)) + (float) (base_salario(escalao, 0) * indice);
    else if (indice > 0.4)
        salario = (float) (base_salario(escalao, 0) + (float) (formacao(grau)*100) + (float) (poliglota_salario(linguas)*50));
    else
        salario = (float) (base_salario(escalao, 0) + (float) (formacao(grau)*100) + (float) (poliglota_salario(linguas)*50)) - (float) (base_salario(escalao, 0)*(0, 4 - indice));
    return salario;
}

void bubble(float *vet, int n)
{
    int i, j;
    float temp;

    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 2; j++)
            if (vet[j] > vet[j + 1])
            {
                temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
            }
}

int mostra_menu()
{
    int menu;
    printf("Universidade Estadual do Centro-Oeste - UNICENTRO\tProfa. Inali Wisniewski Soares\n");
    printf("Programacao de Computadores II                   \tDepartamento de Ciencia da Computacao - DECOMP\n\n");
    printf("\t\t\tTRABALHO 3 - ESTRUTURAS E ARQUIVOS\n");
    printf("\nMenu\n");
    printf("1 - Cadastrar funcionarios\n");
    printf("2 - Relatorio empresarial\n");
    printf("3 - Salvar dados\n");
    printf("4 - Consultar dados salvos\n");
    printf("5 - Sair\n");
    scanf("%d%*c", &menu);
    return menu;
}

void aguarda()
{
    printf("\nPressione uma tecla para continuar\n");
    for (; !kbhit();)
    {

    }
}

int media_salarial(float *vetor, int n, float soma, float *maior, float *maior2, float *menor2, float *menor)
{
    *maior = vetor[n - 1];
    *menor = vetor[0];
    if (n > 1)
    {
        *maior2 = vetor[n - 2];
        *menor2 = vetor[1];
    }

    int i, acima_media = 0;
    soma = soma / (float) n;
    for (i = 0; i < n; i++)
    {
        if (vetor[i] >= soma)
            acima_media++;
    }
    return acima_media;
}

void salvar(int n, Funcionario *funcionario)
{
    FILE *arquivo;
    char nome_arquivo[80];
    int i, result;


}

//Usuario dá: nome, sexo, data, grau, escalao, linguas, indice
//Calcular  : idade, salario, salariobase

typedef enum
{
    PRINCIPAL,
    CADASTRAR,
    RELATORIO,
    SALVAR,
    CONSULTAR,
    SAIR
} MENU;

int main()
{
    FILE *arquivo;
    char c, opcao, nome_arquivo[80];
    int n, i, acima_media = 0, result, j;
    Funcionario *funcionario;
    float *vet_salarios, soma = 0, maior = 0, maior2 = 0, menor2 = 0, menor = 0;

    MENU menu = 0;
    bool execucao = true;

    while (execucao)
    {
        switch (menu)
        {
        case PRINCIPAL:
            menu = mostra_menu();
            break;


        case CADASTRAR:
            printf("\nNumero de funcionarios\n");
            scanf("%d", &n);
            getchar();

            funcionario = malloc(n * sizeof (Funcionario));
            vet_salarios = malloc(n * sizeof (float));

            if (!funcionario)
            {
                printf("Memoria insuficiente");
                exit(1);
            }

            if (!vet_salarios)
            {
                printf("Memoria insuficiente");
                exit(1);
            }

            time_t hoje = time(NULL);
            struct tm tm = *localtime(&hoje);

            for (i = 0; i < n; i++)
            {
                printf("\n");
                printf("Funcionario %d\n", i + 1);
                printf("Nome: ");
                scanf("%254[^\n]%*c", &(funcionario + i)->nome);

                printf("Data de nascimento: ");
                j = 0;
                do
                {
                    if (j > 0)
                        printf("Erro! (Dia: 0 > dia < 32; Mes: 0 > mes < 13)\n");
                    j++;
                    scanf("%d%*c %d%*c %d%*c", &(funcionario + i)->data.dia, &(funcionario + i)->data.mes, &(funcionario + i)->data.ano);
                }
                while ((funcionario + i)->data.dia < 1 || (funcionario + i)->data.dia > 31 || (funcionario + i)->data.mes < 1 || (funcionario + i)->data.mes > 12);

                (funcionario + i)->idade = (tm.tm_year + 1900 - (funcionario + i)->data.ano) + ((float) (tm.tm_mon + 1 - (funcionario + i)->data.mes) / (float) 10);

                printf("Sexo: ");
                j = 0;
                do
                {
                    if (j > 0)
                        printf("Erro! Escolha entre m/f\n");
                    j++;
                    scanf("%c%*c", &(funcionario + i)->sexo);
                }
                while ((funcionario + i)->sexo != 'm' && (funcionario + i)->sexo != 'f');

                printf("Grau de estudo: ");
                scanf("%d%*c", &(funcionario + i)->grau);

                printf("Escalao: ");
                scanf("%d%*c", &(funcionario + i)->escalao);

                printf("Linguas: ");
                scanf("%d%*c", &(funcionario + i)->linguas);

                printf("Indice de produtividade: ");
                scanf("%f%*c", &(funcionario + i)->indice);

                (funcionario + i)->salario = salario((funcionario + i)->grau, (funcionario + i)->linguas, (funcionario + i)->escalao, (funcionario + i)->indice);
                vet_salarios[i] = (funcionario + i)->salario;
                soma += (funcionario + i)->salario;
            }
            printf("\n");
            menu = 0;
            aguarda();
            system("cls");
            break;


        case RELATORIO:
            bubble(vet_salarios, n);
            acima_media = media_salarial(vet_salarios, n, soma, &maior, &maior2, &menor2, &menor);
            printf("\nSalarios:\n");
            for (i = 0; i < n; i++)
            {
                printf("%d. R$ %.2f\n", i + 1, vet_salarios[i]);
            }
            printf("\nMaior salario: R$ %.2f\nSegundo maior salario: R$ %.2f\nSegundo menor salario: R$ %.2f\nMenor salario: R$ %.2f\n\nFuncionarios com salario acima da media: %d\n\n", vet_salarios[n - 1], vet_salarios[n - 2], vet_salarios[1], vet_salarios[0], acima_media);
            menu = 0;
            aguarda();
            system("cls");
            break;


        case SALVAR:
            printf("Nome do arquivo (Ex: nome.bin)\n");
            scanf("%254[^\n]%*c", nome_arquivo);

            arquivo = fopen(nome_arquivo, "wb");
            if (arquivo == NULL)
            {
                printf("\nArquivo nao pode ser aberto");
                exit(1);
            }

            fwrite(&n, sizeof (n), 1, arquivo);

            for (i = 0; i < n; i++)
                result = fwrite((funcionario + i), sizeof (Funcionario), 1, arquivo);

            printf("Elementos gravados: %d\n", result);
            fclose(arquivo);
            menu = 0;
            aguarda();
            system("cls");
            break;


        case CONSULTAR:
            printf("Nome do arquivo: \n");
            scanf("%254[^\n]%*c", nome_arquivo);

            arquivo = fopen(nome_arquivo, "rb");
            if (arquivo == NULL)
            {
                printf("\nArquivo nao pode ser aberto");
                exit(1);
            }

            for (i = 0; i < n; i++)
            {
                if (fread(&funcionario[i], sizeof (funcionario), 1, arquivo) == 1)
                {
                    printf("\n\n     %s", (funcionario + i)->nome);
                    printf("\n%.2f", (funcionario + i)->idade);
                    if ((funcionario + i)->sexo == 'm')

                        printf("\nMasculino");
                    else
                        printf("\nFeminino");

                    printf("\nSalario: R$ %.2f", (funcionario + i)->salario);
                    printf("\nGrau de estudos: %d", (funcionario + i)->grau);
                    printf("\nEscalao: %d", (funcionario + i)->escalao);
                    printf("\nLinguas estrangeiras: %d", (funcionario + i)->linguas);
                    printf("\nIndice de produtividade: %.2f", (funcionario + i)->indice);
                }
            }

            fclose(arquivo);
            menu = 0;
            aguarda();
            system("cls");
            break;


        case SAIR:
            exit(1);
        }
    }
    return 0;
}

