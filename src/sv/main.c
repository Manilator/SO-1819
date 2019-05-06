#include "sv.h"

int main() {

  mkfifo("files/fifo_in", 0666);
  mkfifo("files/fifo_out", 0666);

  char buf[4096] = {0};

  if (!fork()) {
    for (;;) {
      printf("Entrei no loop\n");
      int fd1 = open("files/stocks", O_CREAT, 0666);
      int fd2 = open("files/vendas", O_CREAT, 0666);
      int fifo0 = open("files/fifo_in", O_RDONLY);

      int l = readln(fifo0, buf, sizeof(buf));

      int espacos = 0;

      if ('i' == buf[0]) {
        sv_criaStock(buf, l);
        memset(buf,0,sizeof(buf));
      }

      else if (buf[0] == 0) {
      }

      else {
        for (int j = 0; j < l; j++) {
          if (buf[j] == ' ') {
            ++espacos;
          }
        }

        if (0 == espacos) {
          sv_mostraStock(buf, l);
          memset(buf,0,sizeof(buf));
        }
        if (1 == espacos) {
          sv_atualizaStock(buf, l);
          memset(buf,0,sizeof(buf));
        }
      }
      close(fifo0);
      close(fd1);
      close(fd2);
    }
    _exit(0);
  }
  return 0;
}
