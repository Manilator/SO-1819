#include "sv.h"
#include "utils.h"

int main() {

  int fd1 = open("stock", O_CREAT | O_TRUNC, 0666);
  int fd2 = open("vendas", O_CREAT | O_TRUNC, 0666);
  mkfifo("../../files/fifo_in", 0666);
  mkfifo("../../files/fifo_out", 0666);


  char buf[4096] = {0};
  int posicao_atual = 0;
  int codigo = 0;
  ssize_t l;

  if (!fork()) {
      int l = read()

      int i = 0;

      for ( ; i < )
  }
  return 0;
}
