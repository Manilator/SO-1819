#include "cv.h"

void cv_mostraStock() {
  Info new_info;

  int fifo1 = open("files/fifo_out", O_RDONLY);
  read(fifo1, &new_info, 4096);
  close(fifo1);

  char quantidade[12] = {0};
  sprintf(quantidade, "%d\n", new_info.stock);
  char preco[12] = {0};
  sprintf(preco, "%d\n", new_info.preco);
  write(1, quantidade, sizeof(quantidade));
  write(1, preco, sizeof(preco));
}

void cv_atualizaStock() {
  char quantidade[12] = {0};

  int fifo1 = open("files/fifo_out", O_RDONLY);
  read(fifo1, quantidade, sizeof(quantidade));
  close(fifo1);
  
  write(1, quantidade, sizeof(quantidade));
}