#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

struct Stock
{
    int codigo;
    int stock;
};

struct Venda
{
    int codigo;
    int quantidade;
    float montante;
};

typedef struct Stock Stock;

typedef struct Venda Venda;

Stock new_stock(int codigo, int stock);

Stock clone_stock(Stock stock);

void cria_stock(int codigo, int stock);

void atualiza_stock(int codigo, int stock);

void ler_stock(int codigo);

Venda nova_venda(int codigo, int quantidade, float montante);

Venda clone_venda(Venda old_venda);

void cria_venda(int codigo, int quantidade, float montante);

#endif /* SERVIDOR_H*/