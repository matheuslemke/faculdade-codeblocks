#include <stdio.h>
#include <stdlib.h>


void le(int **ptr_matriz, int linha, int coluna)
{
    int i, j;
    printf("Digite a matriz\n");
    for(i = 0; i < linha; i++)
        for(j = 0; j < coluna; j++)
            scanf("%d", &ptr_matriz[i][j]);
}

void imprime(int **ptr_matriz, int linha, int coluna)
{
    int i, j;
    for(i = 0; i < linha; i++)
    {
        for(j = 0; j < coluna; j++)
            printf("%d ", ptr_matriz[i][j]);
        printf("\n");
    }
}


int main()
{
    int **ptr_matriz, linha, coluna, i, j, **pivo;
    printf("Linhas\n");
    scanf("%d", &linha);
    printf("Colunas\n");
    scanf("%d", &coluna);

    ptr_matriz = calloc(linha, sizeof(int));
    if(ptr_matriz == NULL)
        exit(1);
    for(i = 0; i < linha; i++)
        ptr_matriz[i] = calloc(coluna, sizeof(int));
    if(ptr_matriz[i] == NULL)
        exit(1);

    pivo = calloc(linha, sizeof(int));
    if(pivo == NULL)
        exit(1);
    for(i = 0; i < linha; i++)
        pivo[i] = calloc(coluna, sizeof(int));
    if(pivo == NULL)
        exit(1);



    le(ptr_matriz, linha, coluna);

    imprime(ptr_matriz, linha, coluna);

    for(i = 0; i < linha; i++)
    {
        pont
        for(j = 0; j < coluna; j++)
        {

        }
    }



    return 0;
}
