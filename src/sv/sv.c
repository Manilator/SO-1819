#include "sv.h"

Stock new_stock(int codigo, int stock) {
  Stock stock_new;

  stock_new.codigo = codigo;
  stock_new.stock = stock;

  return stock_new;
}

Stock clone_stock(Stock stock) {
  Stock new_stock;

  new_stock.codigo = stock.codigo;
  new_stock.stock = stock.stock;

  return new_stock;
}

void cria_stock(int codigo, int stock) {
  Stock stock_new = new_stock(codigo, stock);

  int fd = open("files/stocks", O_CREAT | O_RDWR | O_APPEND, 0666);
  write(fd, &stock_new, sizeof(Stock));
  close(fd);
}

int atualiza_stock(int codigo, int stock) {
  Stock new_stock = ler_stock(codigo);

  new_stock.stock += stock;

  int fd = open("files/stocks", O_CREAT | O_RDWR, 0666);
  pwrite(fd, &new_stock, sizeof(Stock), codigo * sizeof(Stock));
  close(fd);

  return new_stock.stock;
}

Stock ler_stock(int codigo) {
  Stock stock_new;

  int fd = open("files/stocks", O_CREAT | O_RDWR, 0666);
  int p = pread(fd, &stock_new, sizeof(Stock), codigo * sizeof(Stock));
  if (p == 0) {
    stock_new.codigo = -1;
  }

  close(fd);

  return stock_new;
}

void new_venda(char *venda_new, int codigo, int quantidade) {

  Artigo new_artigo = ler_artigo(codigo);
  char cod[12] = {0};
  sprintf(cod, "%d ", codigo);
  char quant[12] = {0};
  sprintf(quant, "%d ", quantidade);
  float montante = (float)quantidade * new_artigo.preco;
  char mont[100] = {0};
  snprintf(mont, 100, "%f\n", montante);
  strcat(venda_new, cod);
  strcat(venda_new, quant);
  strcat(venda_new, mont);
}

void cria_venda(char *venda_new, int codigo, int quantidade) {
  new_venda(venda_new, codigo, quantidade);

  int fd = open("files/vendas", O_CREAT | O_WRONLY | O_APPEND, 0666);
  write(fd, venda_new, strlen(venda_new));
  close(fd);
}
