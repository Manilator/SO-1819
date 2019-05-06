
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ag.h"
#include "sv.h"


// Cria um Agregador
Agregador new_agregador (int codigo, int vendas, int quantidade, float montante){

    Agregador ag;
    ag.codigo = codigo;
    ag.vendas = vendas;
    ag.quantidade = quantidade;
    ag.montante = montante;
    return ag;
}


// Clona um Agregador
Agregador clone_agregador (Agregador ag){
    
    Agregador clone;
    clone.codigo = ag.codigo;
    clone.vendas = ag.vendas;
    clone.quantidade = ag.quantidade;
    clone.montante = ag.montante;
    return clone;
}


// Guarda um Agregador
void store_agregador (Agregador ag){

  int fd = open ("./agregadores", O_WRONLY | O_APPEND);
  write (fd, &ag, sizeof(Agregador));
}


// Cria e guarda um Agregador
void cria_agregador (int codigo, int vendas, int quantidade, float montante){
    
    Agregador ag = new_agregador (codigo, vendas, quantidade, montante);

    int fd = open ("./agregadores", O_WRONLY | O_APPEND);
    int l = write (fd, &ag, sizeof(Agregador));
    close (fd);
}


// Atualiza um Agregador
void atualiza_agregador (int codigo, int quantidade, float montante){
    
    Agregador ag;
    
    int fd = open ("./agregadores", O_RDWR);
    int l = pread (fd, &ag, sizeof(Agregador), codigo * sizeof(Agregador));

    ag.vendas ++;
    ag.quantidade += quantidade;
    ag.montante += montante;

    pwrite (fd, &ag, sizeof(Agregador), codigo * sizeof(Agregador));
    close (fd);
}


// Imprime um Agregador
void ler_agregador (int codigo){
    
    Agregador ag;

    int fd = open ("./agregadores", O_RDONLY);
    int l = pread (fd, &ag, sizeof(Agregador), codigo * sizeof(Agregador));

    printf ("Código: %d\n", ag.codigo);
    printf ("Vendas: %d\n", ag.vendas);
    printf ("Quantiadade: %d\n", ag.quantidade);
    printf ("Montante: %f\n", ag.montante);

    close (fd);
}


// Ler o ficheiro vendas e criar Agregadores
/*void ler_vendas(){

    int fd1 = open ("./agregadores", O_CREAT | O_WRONLY, 0666);
    int fd2 = open ("./vendas", O_RDONLY);

    int res = dup2 (fd2, 0);
    Venda venda;
    
    while (read (0, &venda, sizeof(venda))){
        atualiza_agregador (venda.codigo, venda.quantidade, venda.montante);
    }

    close (fd1);
    close (fd2);
}*/
