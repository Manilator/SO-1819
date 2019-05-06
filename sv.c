
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
    int l = write(fd, &stock_new, sizeof(stock_new));
    printf("%d\n",l);
    close(fd);
}

int atualiza_stock(int codigo, int stock) {
    Stock new_stock;
    
    int fd = open("files/stocks", O_RDWR);
    pread(fd, &new_stock, sizeof(new_stock), codigo * sizeof(Stock));

    new_stock.stock += stock;

    pwrite(fd, &new_stock, sizeof(new_stock), codigo * sizeof(Stock));
    close(fd);

    return new_stock.stock;
}

Stock ler_stock(int codigo) {
    Stock stock_new;

    int fd = open("files/stocks", O_RDONLY);
    pread(fd, &stock_new, sizeof(stock_new), codigo * sizeof(stock_new));

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

Venda nova_venda(int codigo, int quantidade, float montante) {
    Venda new_venda;

    new_venda.codigo = codigo;
    new_venda.quantidade = quantidade;
    new_venda.montante = montante;

    return new_venda;
}

Venda clone_venda(Venda old_venda) {
    Venda new_venda;

    new_venda.codigo = old_venda.codigo;
    new_venda.montante = old_venda.montante;
    new_venda.quantidade = old_venda.quantidade;

    return new_venda;
}

void cria_venda(int codigo, int quantidade, float montante) {
    Venda new_venda = nova_venda(codigo, quantidade, montante);

    int fd = open("./vendas", O_WRONLY | O_APPEND);
    write(fd, &new_venda, sizeof(new_venda));
    close(fd);
}


