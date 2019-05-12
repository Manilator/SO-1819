#ifndef MANUTENCAO_H
#define MANUTENCAO_H

#define _XOPEN_SOURCE 500

#include "sv.h"

/* Stock inicial de um artigo */
#define STOCK_INICIAL 0

/* Artigo */
typedef struct Artigo {
  int posicao;
  float preco;
}Artigo;

/** 
 *  Cria um novo artigo.
 * 
 * @param posicao Posição do nome do artigo no ficheiro strings.
 * @param preco Preço do artigo.
 * @returns O artigo.
 */
Artigo new_artigo(int posicao, float preco);

/**
 *  Clona um artigo.
 * 
 * @param artigo Artigo a ser clonado.
 * @returns O artigo clonado.
 */
Artigo clone_artigo(Artigo artigo);

/**
 *  Guarda um artigo em ficheiro
 * 
 * @param artigo Artigo a ser guardado.
 */
void store_artigo(Artigo artigo);

/**
 *  Guarda um nome no ficheiro de strings.
 * 
 * @param *nome String a ser guardada.
 * @param posicao_atual Posição em que a string vai ser guardada no ficheiro.
 * @returns Posição do final da string no ficheiro.
 */
int store_string(char *nome, int posicao_atual);

/**
 * Guarda um artigo e preço de um artigo em ficheiros.
 * 
 * @param preco Preço do artigo.
 * @param *nome Nome do artigo.
 * @param posicao_atual Posição em que o nome do artigo vai ser guardado no ficheiro strings.
 * @returns Posicao do final da string no ficheiro.
 */
int store(float preco, char *nome, int posicao_atual);

/**
 * Atualiza o nome de um artigo.
 * 
 * @param codigo Código do artigo a ser alterado.
 * @param *nome Nome novo para o artigo.
 * @param posicao_atual Posição do final da ultima string a ser adicionada.
 */
int altera_nome(int codigo, char *nome, int posicao_atual);


void altera_preco(int codigo, float preco);

Artigo ler_artigo(int codigo);

#endif /* MANUTENCAO_H*/