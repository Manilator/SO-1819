#include "ma.h"
#include "utils.h"

int main() {

  int fd1 = open("files/artigos", O_CREAT | O_TRUNC, 0666);
  int fd2 = open("files/strings", O_CREAT | O_TRUNC, 0666);
  int fifo0 = open("files/fifo_in", O_WRONLY);

  char buf[4096] = {0};
  int posicao_atual = 0;
  int codigo = 0;
  ssize_t l;

      while ((l = readln(0, buf, 4096))) {
        if ('i' == buf[0]) {
          write(fifo0, buf, l);
          codigo = ma_inserir(buf, posicao_atual, codigo, l);
        }
        else if ('n' == buf[0]) {
          ma_altera_nome(buf, posicao_atual, l);  
        }
        else if ('p' == buf[0]) {
          ma_altera_preco(buf, l);
        }
        else if ('b' == buf[0]) {
          break;
        }
        memset(buf, 0, sizeof(buf));
      }

  close(fd1);
  close(fd2);
  return 0;
}
