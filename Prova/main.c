#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    DECRESCENTE,
    CRESCENTE
} ORDENACAO;

int busca_binaria(int *vet, int i, int n, int busca)
{
    int meio = (i + n) / 2;
    if (vet[meio] == busca)
    {
        return meio;
    }
    else if (busca > vet[meio])
    {
        return busca_binaria(vet, meio + 1, n, busca);
    }
    else
    {
        return busca_binaria(vet, i, meio - 1, busca);
    }

    return -1;
}

void bubble_sort(int *vet, int n, ORDENACAO metodo)
{
    int aux, i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < (n - i - 1); j++)
        {
            if ((vet[j] < vet[j + 1]) && metodo == DECRESCENTE)
            {
                aux = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = aux;
            }
            else if ((vet[j] > vet[j + 1]) && metodo == CRESCENTE)
            {
                aux = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = aux;
            }
        }
    }
}

void fun(int y)
{
    static int x;
    x += y;
    printf("x = %d\n",x);
    x++;
}


int main()
{
    int i, v[5], *p;
    p = v;
    printf("Hello world!\n");
    fun(10);
    fun(20);
    fun(30);

    for(i = 0; i < 5; i++)
    {
        scanf("%d", &*(p + i));
    }

    bubble_sort(v, 5, 1);

    for(i = 0; i < 5; i++)
    {
        printf("%d ", *(p + i));
    }

    printf("\n");
    printf("%d", busca_binaria(v, 0, 5, 5));

    return 0;
    return 0;
}
