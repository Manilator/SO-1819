#ifndef AGREGADOR_H
#define AGREGADOR_H

#define _XOPEN_SOURCE 500
#define CAPACIDADE_INICIAL 128

#include "sv.h"

/* Agregador */
typedef struct Agregador {
  int cod;
  int quantidade;
  float montante;
} Agregador;

/* Array Dinâmico de Agregadores */
typedef struct A_Agregador {
  Agregador *ag;
  int posicao_atual;
  int size_atual;
} A_Agregador;

/**
 *  Cria um novo agregador.
 *
 * @param cod Código do produto.
 * @param quantidade Quantidade da venda.
 * @param montante Total lucrado/perdido da venda.
 * @returns O Agregador
 */
Agregador new_agregador(int cod, int quantidade, float montante);

/**
 *  Cria um novo array dinâmico de agregadores.
 *
 * @param size Tamanho do array inicial.
 * @returns O array de agregadores.
 */
A_Agregador new_agregadores(int size);

/**
 *  Adiciona um agregador ao array dinâmico de agregadores.
 *
 * @param *agregadores Apontador para o array dinâmico de agregadores.
 * @param ag Agregador a ser adicionado ao array.
 */
void add_agregador(A_Agregador *agregadores, Agregador ag);

/**
 *  Atualiza um agregador num array dinâmico de agregadores.
 *
 * @param agregadores Array dinâmico de agregadores.
 * @param i Posição do agregador a ser atualizado.
 * @param quantidade Quantidade a adicionar.
 * @param montante Montante a adicionar.
 */
void atualiza_agregador(A_Agregador agregadores, int i, int quantidade,
                        float montante);

#endif /* AGREGADOR_H*/