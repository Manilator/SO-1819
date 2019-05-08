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
#include "cv.h"
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

struct PFifo
{
    pid_t fifoname;
    char buf[256];
};



struct Venda
{
    int codigo;
    int quantidade;
    float montante;
};

typedef struct Stock Stock;

typedef struct Info Info;

typedef struct PFifo PFifo;

typedef struct Venda Venda;

static const struct PFifo EmptyStruct;

Stock new_stock(int codigo, int stock);

Stock clone_stock(Stock stock);

void cria_stock(int codigo, int stock);

int atualiza_stock(int codigo, int stock);

Stock ler_stock(int codigo);

Venda new_venda(int codigo, int quantidade);

Venda clone_venda(Venda old_venda);

void cria_venda(int codigo, int quantidade);

void sv_criaStock(char *buf, int l);

int sv_mostraStock(PFifo fifoid, int l);

int sv_atualizaStock(PFifo fifoid, int l);

#endif /* SERVIDOR_H*/