#include "ma.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  open("artigos", O_CREAT | O_TRUNC, 0666);
  open("strings", O_CREAT | O_TRUNC, 0666);

  char buf[4096] = {0};
  int posicao_atual = 0;
  int codigo = 0;
  ssize_t l;
  while ((l = readln(0, buf, 4096))) {
    if ('i' == buf[0]) {
      codigo = ma_inserir(buf, posicao_atual, codigo, l);
    }
    if ('n' == buf[0]) {
      ma_altera_nome(buf, posicao_atual, l);  
    }
    if ('p' == buf[0]) {
      ma_altera_preco(buf, posicao_atual, l);
    }
  }
  return 0;
}
