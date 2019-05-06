#include "sv.h"

Stock new_stock(int codigo, int stock) {
  Stock new_stock;

  new_stock.codigo = codigo;
  new_stock.stock = stock;

  return new_stock;
}

Stock clone_stock(Stock stock) {
  Stock new_stock;

  new_stock.codigo = stock.codigo;
  new_stock.stock = stock.stock;

  return new_stock;
}

void cria_stock(int codigo, int stock) {
  Stock stock_new = new_stock(codigo, stock);

  int fd = open("files/stocks", O_WRONLY | O_APPEND);
  int l = write(fd, &stock_new, sizeof(Stock));
  printf("%d\n", l);
  close(fd);
}

int atualiza_stock(int codigo, int stock) {
  Stock new_stock;

  int fd = open("files/stocks", O_RDWR);
  pread(fd, &new_stock, sizeof(Stock), codigo * sizeof(Stock));

  new_stock.stock += stock;

  pwrite(fd, &new_stock, sizeof(Stock), codigo * sizeof(Stock));
  close(fd);

  return new_stock.stock;
}


Stock ler_stock(int codigo) {
  Stock stock_new;

  int fd = open("files/stocks", O_RDONLY);
  pread(fd, &stock_new, sizeof(Stock), codigo * sizeof(Stock));

  close(fd);

  return stock_new;
  // Escreve o código no ecra
  // char cod[12];
  // char stock[4096];
  // int e = sprintf(cod, "%d\n", stock_new.codigo);
  // int d = sprintf(stock, "%d\n", stock_new.stock);
  // write(1, &cod, sizeof(e));
  // write(1, &stock, sizeof(d));
}

Venda new_venda(int codigo, int quantidade) {
  Venda new_venda;
  Artigo new_artigo = ler_artigo(codigo);

  new_venda.codigo = codigo;
  new_venda.quantidade = quantidade;

  new_venda.montante = quantidade * new_artigo.preco;

  return new_venda; 
}

Venda clone_venda(Venda old_venda) {
  Venda new_venda;

  new_venda.codigo = old_venda.codigo;
  new_venda.montante = old_venda.montante;
  new_venda.quantidade = old_venda.quantidade;

  return new_venda;
}

void cria_venda(int codigo, int quantidade) {
  Venda venda_new = new_venda(codigo, quantidade);

  int fd = open("vendas", O_WRONLY | O_APPEND);
  write(fd, &venda_new, sizeof(Venda));
  close(fd);
}

void sv_criaStock(char *buf, int l) {
  int i;
  char cod[12] = {0};

  for (i = 2; i < l; i++) {
    cod[i] = buf[i];
  }
  cria_stock(atoi(cod), 0);
  printf("Criei Stock\n");
}

void sv_mostraStock(char *buf, int l) {
  char cod[12] = {0};
  int i;

  for (i = 0; i < l && buf[i] != ' '; i++) {
    cod[i] = buf[i];
  }

  Info new_info;
  new_info.stock = ler_stock(atoi(cod)).stock;
  new_info.preco = ler_artigo(atoi(cod)).preco;
  memset(cod, 0, sizeof(cod));

  int fifo1 = open("files/fifo_out", O_WRONLY);

  write(fifo1, &new_info, sizeof(Info));
  printf("Devolvi pelo pipe a info\n");

  close(fifo1);
}

void sv_atualizaStock(char *buf, int l) {
  char quantidade[12] = {0};
  char cod[12] = {0};
  int i;

  for (i = 0; i < l && buf[i] != ' '; i++) {
    cod[i] = buf[i];
  }

  for (; i < l && buf[i] == ' '; i++) {
  }

  for (int j = 0; i < l && buf[i] != ' '; i++, j++) {
    quantidade[j] = buf[i];
  }

  cria_venda(atoi(cod), atoi(quantidade));

  int new_stock;
  new_stock = atualiza_stock(atoi(cod), atoi(quantidade));
  char return_stock[12] = {0};
  sprintf(return_stock, "%d\n", new_stock);
  printf("Atualizei o Stock\n");

  int fifo1 = open("files/fifo_out", O_WRONLY);

  write(fifo1, return_stock, sizeof(return_stock));
  printf("Devolvi pelo pipe o novo stock\n");

  close(fifo1);
}
