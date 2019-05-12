#include "sv.h"
#include <string.h>

int main() {

  mkfifo("files/fifo_in", 0666);

  if (!fork()) {

    for (;;) {
      char venda_new[BUFFER_SIZE];
      int l;
      PFifo fifoid = EmptyPFifo;
      int fifo0 = open("files/fifo_in", O_RDONLY);
      while ((l = read(fifo0, &fifoid, sizeof(PFifo)))) {
        char fifoname[21] = {0};
        sprintf(fifoname, "/tmp/%dfifo", fifoid.fifoname);

        if ('i' == fifoid.comando) {
          cria_stock(fifoid.cod, 0);
        } else if (fifoid.quantidade == 0 && fifoid.cod != -1) {
          Info new_info = EmptyInfo;
          new_info.stock = ler_stock(fifoid.cod).stock;
          new_info.preco = ler_artigo(fifoid.cod).preco;
          int fifo1 = open(fifoname, O_WRONLY);
          write(fifo1, &new_info, sizeof(Info));
          close(fifo1);
        } else if (fifoid.cod == -1) {
        } else if (fifoid.quantidade != 0 && fifoid.cod != -1) {
          Info new_info = EmptyInfo;
          cria_venda(venda_new, fifoid.cod, fifoid.quantidade);
          memset(venda_new, 0, sizeof(venda_new));
          int fifo1 = open(fifoname, O_WRONLY);
          new_info.stock = atualiza_stock(fifoid.cod, fifoid.quantidade);
          write(fifo1, &new_info, sizeof(Info));
          close(fifo1);
        }
      }
      fifoid = EmptyPFifo;
      close(fifo0);
    }
    _exit(0);
  }
  return 0;
}
