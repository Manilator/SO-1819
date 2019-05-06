
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ag.h"
#include "sv.h"
#include "utils.h"


int main (int argc, char* argv[]){

    int fd0 = open ("./vendas", O_CREAT | O_TRUNC | O_RDWR | O_APPEND, 0666);
    int fd1 = open ("./agregadores", O_CREAT | O_TRUNC | O_RDWR | O_APPEND, 0666);

    cria_venda (1, 5, 10.0);
    cria_venda (2, 10, 20.0);
    cria_venda (3, 15, 30.0);

    Venda aux;

    while (readln (fd0, &aux, sizeof(Venda))){
        
        printf ("%d\n", aux.codigo);
        printf ("%d\n", aux.quantidade);
        printf ("%f\n", aux. montante);
        /*cria_agregador (aux.codigo, 1, aux.quantidade, aux.montante);
        ler_agregador (aux.codigo);*/
    }

    close (fd0);
    close (fd1);
    return 0;
}