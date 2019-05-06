#include "sv.h"
#include "ma.h"
#include "utils.h"

int main() {

  mkfifo("files/fifo_in", 0666);
  mkfifo("files/fifo_out", 0666);

  char buf[4096] = {0};

  if (!fork()) {
    for(;;) {
      printf("Entrei no loop\n");
      int fd1 = open("files/stocks", O_CREAT , 0666);
      int fd2 = open("files/vendas", O_CREAT , 0666);
      int fifo0 = open("files/fifo_in", O_RDONLY);
      
      int l = readln(fifo0, buf, sizeof(buf));

      int i = 0;
      int espacos = 0;
      char cod[12] = {0};

      if ('i' == buf[0]) {
        for (i = 2; i < l; i++) {
          cod[i] = buf[i];
        }
        cria_stock(atoi(cod), 0);
        printf("Criei Stock\n");
        memset(buf,0,sizeof(buf));
      } else if (buf[0] == 0) {
      }
      else {
        for (int j = 0; j < l; j++) {
          if (buf[j] == ' ') {
          ++espacos;
          }
        }

        if (0 == espacos) {
          // Mostra no stdout stock e preço
          for (i = 0; i < l && buf[i] != ' '; i++) {
            cod[i] = buf[i];
          }
          Info new_info;
          new_info.stock = ler_stock(atoi(cod)).stock;
          new_info.preco = ler_artigo(atoi(cod)).preco;
          memset(cod, 0, sizeof(buf));

          int fifo1 = open("files/fifo_out", O_WRONLY);
          write(fifo1,&new_info, sizeof(new_info));
          printf("Devolvi pelo pipe a info\n");
          close(fifo1);
        }
        if (1 == espacos) {
          // Atualiza Stock e mostra nova Stock
          char quantidade[12] = {0};
          for (i = 0; i < l && buf[i] != ' '; i++) {
            cod[i] = buf[i];
          }

          // Avança Espaços
          for (; i < l && buf[i] == ' '; i++) {}

          for (int j = 0; i < l && buf[i] != ' '; i++, j++) {
            quantidade[j] = buf[i];
          }

          int new_stock;
          new_stock = atualiza_stock(atoi(cod), atoi(quantidade));
          char return_stock[12] = {0};
          sprintf(return_stock, "%d\n", new_stock);
          printf("Atualizei o Stock\n");

          int fifo1 = open("files/fifo_out", O_WRONLY);
          write(fifo1, return_stock,sizeof(return_stock));
          printf("Devolvi pelo pipe o novo stock\n");
          close(fifo1);
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
