#ifndef MANUTENCAO_H
#define MANUTENCAO_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

//PARA REMOVER
#include <stdio.h>

#define STOCK_INICIAL 0

struct Artigo
{
    int posicao;
    float preco;
};

typedef struct Artigo Artigo;

Artigo new_artigo(int posicao, float preco);

Artigo clone_artigo(Artigo artigo);

void store_artigo(Artigo artigo);

int store_string(char *nome, int posicao_atual);

int store(float preco, char *nome, int posicao_atual);

int altera_nome(int codigo, char *nome, int posicao_atual);

void altera_preco(int codigo, float preco);

Artigo ler_artigo(int codigo);

int ma_inserir(char *buf, int posicao_atual, int codigo_atual, int l);

void ma_altera_nome(char *buf, int posicao_atual, int l);

void ma_altera_preco(char *buf, int posicao_atual, int l);


#endif /* MANUTENCAO_H*/