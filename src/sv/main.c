#include "sv.h"
#include "ma.h"
#include "utils.h"

int main() {

  mkfifo("files/fifo_in", 0666);
  mkfifo("files/fifo_out", 0666);

  char buf[4096] = {0};
  int posicao_atual = 0;
  int codigo = 0;
  ssize_t l;

  if (!fork()) {
    for(;;) {
      printf("Entrei no loop");
      int fd1 = open("files/stocks", O_CREAT | O_TRUNC, 0666);
      int fd2 = open("files/vendas", O_CREAT | O_TRUNC, 0666);
      int fifo0 = open("files/fifo_in", O_RDONLY);
      int fifo1 = open("files/fifo_out", O_WRONLY);

      int l = read(fifo0, buf, sizeof(buf));

      int i = 0;
      int espacos = 0;
      char cod[12] = {0};

      if ('i' == buf[0]) {
        for (i = 2; i < l; i++) {
          cod[i] = buf[i];
        }
        cria_stock(atoi(cod), 0);
      } else {
        for (int j = 0; j < l; j++) {
          ++espacos;
        }

        if (0 == espacos) {
          // Mostra no stdout stock e preço
          for (; i < l && buf[i] == ' '; i++) {
            cod[i] = buf[i];
          }
          Info new_info;
          new_info.stock = ler_stock(atoi(cod)).stock;
          new_info.preco = ler_artigo(atoi(cod)).posicao;
          memset(cod, 0, sizeof(buf));
          write(fifo1,&new_info, sizeof(new_info));
        }
        if (1 == espacos) {
          // Atualiza Stock e mostra nova Stock
          int quantidade[12] = {0};
          for (; i < l && buf[i] == ' '; i++) {
            cod[i] = buf[i];
          }

          for (; i < l && buf[i] == ' '; i++) {
            quantidade[i] = buf[i];
          }

          atualiza_stock(atoi(cod), atoi(quantidade));

          write(fifo1, quantidade,sizeof(quantidade));
        }
      }
      close(fifo0);
      close(fifo1);
      close(fd1);
      close(fd2);
    }
    _exit(0);
  }
  return 0;
}
