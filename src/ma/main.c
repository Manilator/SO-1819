#include "ma.h"
#include "utils.h"

int main(int argc, char const *argv[]) {

  int fd1 = open("files/artigos", O_CREAT | O_TRUNC, 0666);
  int fd2 = open("files/strings", O_CREAT | O_TRUNC, 0666);
  int fifo0 = open("files/fifo_in", O_WRONLY);
  int fifo1 = open("files/fifo_out", O_RDONLY);

  char buf[4096] = {0};
  int posicao_atual = 0;
  int codigo = 0;
  ssize_t l;

      while ((l = readln(0, buf, 4096))) {
        if ('i' == buf[0]) {
          write(fifo0, buf, sizeof(buf));
          codigo = ma_inserir(buf, posicao_atual, codigo, l);
        }
        if ('n' == buf[0]) {
          ma_altera_nome(buf, posicao_atual, l);  
        }
        if ('p' == buf[0]) {
          ma_altera_preco(buf, posicao_atual, l);
        }
        if ('b' == buf[0]) {
          break;
        }
      }

  close(fd1);
  close(fd2);
  return 0;
}
