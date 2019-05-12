#include "ma.h"

Artigo new_artigo(int posicao, float preco) {
  Artigo artigo;

  artigo.posicao = posicao;
  artigo.preco = preco;

  return artigo;
}

Artigo clone_artigo(Artigo artigo) {
  Artigo clone;

  clone.posicao = artigo.posicao;
  clone.preco = artigo.preco;

  return clone;
}

void store_artigo(Artigo artigo) {

  int fd = open("files/artigos", O_CREAT | O_WRONLY | O_APPEND, 0666);
  write(fd, &artigo, sizeof(Artigo));
  close(fd);
}

int store_string(char *nome, int posicao_atual) {

  int fd = open("files/strings", O_CREAT | O_WRONLY | O_APPEND, 0666);
  int l = write(fd, nome, strlen(nome)) + posicao_atual;

  close(fd);

  return l + posicao_atual;
}

int store(float preco, char *nome, int posicao_atual) {

  Artigo artigo;

  artigo.posicao = posicao_atual;
  int proxima_posicao = store_string(nome, posicao_atual);
  artigo.preco = preco;
  store_artigo(artigo);

  return proxima_posicao;
}

int altera_nome(int codigo, char *nome, int posicao_atual) {
  int fd1 = open("files/artigos", O_CREAT | O_RDWR, 0666);
  int fd2 = open("files/strings", O_CREAT | O_WRONLY | O_APPEND, 0666);
  Artigo artigo;

  ssize_t l = pread(fd1, &artigo, sizeof(Artigo), codigo * sizeof(Artigo));
  if (l != 0) {
    artigo.posicao = posicao_atual;
    int proxima_posicao = store_string(nome, posicao_atual);
    pwrite(fd1, &artigo, sizeof(Artigo), codigo * sizeof(Artigo));
    close(fd1);
    close(fd2);

    return proxima_posicao;
  }

  close(fd1);
  close(fd2);

  return posicao_atual;
}

void altera_preco(int codigo, float preco) {
  int fd = open("files/artigos", O_CREAT | O_RDWR, 0666);
  Artigo artigo;

  ssize_t l = pread(fd, &artigo, sizeof(Artigo), codigo * sizeof(Artigo));
  if (l != 0) {
    artigo.preco = preco;
    pwrite(fd, &artigo, sizeof(Artigo), codigo * sizeof(Artigo));
  }
  close(fd);
}

Artigo ler_artigo(int codigo) {
  Artigo artigo_new;

  int fd = open("files/artigos", O_CREAT | O_RDWR, 0666);
  int l =
      pread(fd, &artigo_new, sizeof(artigo_new), codigo * sizeof(artigo_new));
  if (l == 0) {
    artigo_new.preco = -1;
  }
  close(fd);

  return artigo_new;
}
