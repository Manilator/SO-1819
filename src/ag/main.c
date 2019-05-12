#include "ag.h"

int main() {

  char venda_new[BUFFER_SIZE];
  A_Agregador agregadores = new_agregadores(CAPACIDADE_INICIAL);
  int l = 0;
  while ((l = readln(0, venda_new, sizeof(venda_new)))) {
    int venda_codigo = 0;
    int venda_quantidade = 0;
    float venda_montante = 0;
    const char s[2] = " ";
    char *token;
    token = strtok(venda_new, s);
    if (token != NULL) {
      venda_codigo = atoi(token);
    }
    token = strtok(NULL, s);
    if (token != NULL) {
      venda_quantidade = atoi(token);
    }
    token = strtok(NULL, s);
    if (token != NULL) {
      venda_montante = atof(token);
    }
    int i = 0;
    for (; i < agregadores.posicao_atual; i++) {
      if (venda_codigo == agregadores.ag[i].cod) {
        atualiza_agregador(agregadores, i, venda_quantidade, venda_montante);
        break;
      }
    }
    if (i == agregadores.posicao_atual) {
      Agregador ag =
          new_agregador(venda_codigo, venda_quantidade, venda_montante);
      add_agregador(&agregadores, ag);
    }
  }
  for (int j = 0; j < agregadores.posicao_atual; j++) {
    char ag_new[BUFFER_SIZE] = {0};
    char cod[MAX_INT_SIZE] = {0};
    sprintf(cod, "%d ", agregadores.ag[j].cod);
    char quant[MAX_INT_SIZE] = {0};
    sprintf(quant, "%d ", agregadores.ag[j].quantidade);
    char mont[100] = {0};
    snprintf(mont, 100, "%f\n", agregadores.ag[j].montante);
    strcat(ag_new, cod);
    strcat(ag_new, quant);
    strcat(ag_new, mont);
    write(1, ag_new, strlen(ag_new));
    memset(ag_new, 0, sizeof(ag_new));
  }
  return 0;
}
