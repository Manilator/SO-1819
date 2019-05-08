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
  printf("Stocks\n");
  if (fd == 0) {
    printf("Error opening stocks file\n");
  }
  write(fd, &stock_new, sizeof(Stock));
  printf("Guardei um novo stock\n");
  close(fd);
}

int atualiza_stock(int codigo, int stock) {
  Stock new_stock = ler_stock(codigo);

  new_stock.stock += stock;

  int fd = open("files/stocks", O_RDWR);
  printf("Stocks\n");
  if (fd == 0) {
    printf("Error opening stocks file\n");
  }
  int p = pwrite(fd, &new_stock, sizeof(Stock), codigo * sizeof(Stock));
  printf("Li do Ficheiro Stocks\n");
  if (p == 0) {
    printf("Error writting on stocks file\n");
  }
  close(fd);

  return new_stock.stock;
}

Stock ler_stock(int codigo) {
  Stock stock_new;

  int fd = open("files/stocks", O_RDONLY);
  printf("Stocks\n");
  if (fd == 0) {
    printf("Error opening stocks file\n");
  }
  int p = pread(fd, &stock_new, sizeof(Stock), codigo * sizeof(Stock));
  printf("Li do ficheiro stocks\n");
  if (p == 0) {
    printf("Error reading from stocks file\n");
  }

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

  int fd = open("files/vendas", O_WRONLY | O_APPEND);
  printf("Vendas\n");
  if (fd == 0) {
    printf("Error opening vendas file\n");
  }
  int p = write(fd, &venda_new, sizeof(Venda));
  printf("Guardei uma nova venda\n");
  if (p == 0) {
    printf("Error writting to vendas file\n");
  }
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

int sv_mostraStock(PFifo fifoid, int l) {
  char cod[12] = {0};
  int i;

  for (i = 0; i < l && fifoid.buf[i] != ' '; i++) {
    cod[i] = fifoid.buf[i];
  }

  Info new_info;
  new_info.stock = ler_stock(atoi(cod)).stock;
  new_info.preco = ler_artigo(atoi(cod)).preco;
  printf("Stock lido do ficheiro: %d\n", new_info.stock);
  printf("Preço lido do ficheiro: %d\n", new_info.preco);
  memset(cod, 0, sizeof(cod));

  char fifoname[21] = {0};
  sprintf(fifoname, "/tmp/%dfifo", fifoid.fifoname);
  int fifo1 = open(fifoname, O_WRONLY);
  printf("Fifo único %d\n", fifo1);
  if (fifo1 == 0) {
    printf("Error opening unique client fifo\n");
  }

  int p = write(fifo1, &new_info, sizeof(Info));
  if (p == 0) {
    printf("Error writting to unique client fifo\n");
  }
  printf("Devolvi pelo pipe a info\n");

  return fifo1;
}

int sv_atualizaStock(PFifo fifoid, int l) {
  char quantidade[12] = {0};
  char cod[12] = {0};
  int i;

  for (i = 0; i < l && fifoid.buf[i] != ' '; i++) {
    cod[i] = fifoid.buf[i];
  }

  for (; i < l && fifoid.buf[i] == ' '; i++) {
  }

  for (int j = 0; i < l && fifoid.buf[i] != ' '; i++, j++) {
    quantidade[j] = fifoid.buf[i];
  }

  cria_venda(atoi(cod), atoi(quantidade));

  int new_stock;
  new_stock = atualiza_stock(atoi(cod), atoi(quantidade));
  char return_stock[12] = {0};
  sprintf(return_stock, "%d\n", new_stock);
  printf("Atualizei o Stock\n");

  char fifoname[21] = {0};
  sprintf(fifoname, "/tmp/%dfifo", fifoid.fifoname);
  int fifo1 = open(fifoname, O_WRONLY);
  printf("Fifo único %d\n", fifo1);
  if (fifo1 == 0) {
    printf("Error opening unique client fifo\n");
  }

  int p = write(fifo1, return_stock, sizeof(return_stock));
  printf("p%d\n", p);
  if (p == 0) {
    printf("Error writting to unique client fifo\n");
  }
  printf("Devolvi pelo pipe o novo stock\n");

  return fifo1;
}
