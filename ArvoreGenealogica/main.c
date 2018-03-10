#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *name;
    Principal pai
}Principal;


int main()
{
    Principal filho1;
    filho1.name = "Filho1";

    Principal filho2;
    filho2.name = "Filho1_1";
    filho2.pai = filho1;

    Principal filho3;
    filho3.name = "Filho1_1_1";
    filho3.pai = filho2;



    return 0;
}
