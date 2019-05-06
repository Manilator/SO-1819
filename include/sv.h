#ifndef SERVIDOR_H
#define SERVIDOR_H

#define _XOPEN_SOURCE 500

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#include "sv.h"
#include "ma.h"
#include "utils.h"

struct Stock
{
    int codigo;
    int stock;
};

struct Info
{
    int stock;
    int preco;
};

struct Venda
{
    int codigo;
    int quantidade;
    float montante;
};

typedef struct Stock Stock;

typedef struct Info Info;

typedef struct Venda Venda;

Stock new_stock(int codigo, int stock);

Stock clone_stock(Stock stock);

void cria_stock(int codigo, int stock);

int atualiza_stock(int codigo, int stock);

Stock ler_stock(int codigo);

Venda nova_venda(int codigo, int quantidade, float montante);

Venda clone_venda(Venda old_venda);

void cria_venda(int codigo, int quantidade, float montante);

void sv_criaStock(char *buf, int l);

void sv_mostraStock(char *buf, int l);

void sv_atualizaStock(char *buf, int l);

#endif /* SERVIDOR_H*/