#ifndef SERVIDOR_H
#define SERVIDOR_H

#define _XOPEN_SOURCE 500

/* Tamanho do buffer */
#define BUFFER_SIZE 4096

/* Tamanho máximo de um inteiro */
#define MAX_INT_SIZE 12

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ma.h"
#include "utils.h"

/* Stock */
typedef struct Stock {
  int codigo;
  int stock;
} Stock;

/* Info retornada pelo servidor */
typedef struct Info {
  int stock;
  float preco;
} Info;

/* Info enviada para o servidor */
typedef struct PFifo {
  pid_t fifoname;
  int cod;
  int quantidade;
  char comando;
  float preco;
} PFifo;

/* Reset da Struct PFifo */
static const struct PFifo EmptyPFifo = {0};

/* Reset da Struct Info */
static const struct Info EmptyInfo = {0};

/**
 * Cria um novo stock
 *
 * @param codigo Código do artigo.
 * @param stock Stock do artigo.
 * @returns A struct Stock.
 */
Stock new_stock(int codigo, int stock);

/**
 * Guarda o stock de um artigo em ficheiro.
 *
 * @param codigo Código do artigo.
 * @param stock Stock do artigo.
 */
void cria_stock(int codigo, int stock);

/**
 * Atualiza o stock de um artigo.
 *
 * @param codigo Código do artigo a ser atualizado.
 * @param stock Novo stock do artigo.
 * @returns O novo stock.
 */
int atualiza_stock(int codigo, int stock);

/**
 * Lê o stock de um artigo.
 *
 * @param codigo Código do artigo a ser lido.
 * @returns A struct Stock.
 */
Stock ler_stock(int codigo);

/**
 * Cria uma string com as informações de um venda.
 *
 * @param *venda_new String onde vão ser guardadas as informações.
 * @param codigo Código do artigo.
 * @param quantidade Quantidade da venda.
 */
void new_venda(char *venda_new, int codigo, int quantidade);

/**
 * Guarda a venda num ficheiro.
 *
 * @param *venda_new String da venda que vai ser guardada.
 * @param codigo Código do artigo.
 * @param quantidade Quantidade da venda.
 */
void cria_venda(char *venda_new, int codigo, int quantidade);

#endif /* SERVIDOR_H*/