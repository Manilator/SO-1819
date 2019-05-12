#include "ag.h"

Agregador new_agregador(int cod, int quantidade, float montante) {
  Agregador ag;
  ag.cod = cod;
  ag.quantidade = quantidade;
  ag.montante = montante;

  return ag;
}

A_Agregador new_agregadores(int size) {
  A_Agregador new_ag;
  new_ag.posicao_atual = 0;
  new_ag.size_atual = size;
  new_ag.ag = malloc(sizeof(Agregador) * size);

  return new_ag;
}

void add_agregador(A_Agregador *agregadores, Agregador ag) {
  if (agregadores->posicao_atual == agregadores->size_atual - 1) {
    agregadores->ag =
        realloc(agregadores->ag, sizeof(agregadores->size_atual) * 2);
    agregadores->size_atual *= 2;
  }
  agregadores->ag[agregadores->posicao_atual] = ag;
  ++agregadores->posicao_atual;
}

void atualiza_agregador(A_Agregador agregadores, int i, int quantidade,
                        float montante) {
  agregadores.ag[i].montante += montante;
  agregadores.ag[i].quantidade += quantidade;
  if (agregadores.ag[i].quantidade < 0 || agregadores.ag[i].montante < 0) {
    agregadores.ag[i].montante = 0;
    agregadores.ag[i].quantidade = 0;
  }
}