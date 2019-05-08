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

  int fd = open("files/artigos", O_WRONLY | O_APPEND);
  write(fd, &artigo, sizeof(Artigo));
  close(fd);
}

int store_string(char *nome, int posicao_atual) {

  int fd = open("files/strings", O_WRONLY | O_APPEND);
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
  int fd1 = open("files/artigos", O_RDWR);
  int fd2 = open("files/strings", O_RDWR | O_APPEND);
  Artigo artigo;

  pread(fd1, &artigo, sizeof(Artigo), codigo * sizeof(Artigo));
  artigo.posicao = posicao_atual;
  int proxima_posicao = store_string(nome, posicao_atual);
  pwrite(fd1, &artigo, sizeof(Artigo), codigo * sizeof(Artigo));

  close(fd1);
  close(fd2);

  return proxima_posicao;
}

void altera_preco(int codigo, float preco) {
  int fd = open("files/artigos", O_RDWR);
  Artigo artigo;

  pread(fd, &artigo, sizeof(Artigo), codigo * sizeof(Artigo));
  artigo.preco = preco;
  pwrite(fd, &artigo, sizeof(Artigo), codigo * sizeof(Artigo));

  close(fd);
}

Artigo ler_artigo(int codigo) {
  Artigo artigo_new;

    int fd = open("files/artigos", O_RDONLY);
    pread(fd, &artigo_new, sizeof(artigo_new), codigo * sizeof(artigo_new));

    close(fd);

    return artigo_new;
}

int ma_inserir(char *buf, int posicao_atual, int codigo_atual, int l) {
  int i = 2;

      // Guarda o nome
      char nome[4096] = {0};
      for (int j = 0; buf[i] != ' ' && i < l; i++, j++) {
        nome[j] = buf[i];
      }
      ++i;

      // Guarda o valor
      char valor[12] = {0};
      for (int j = 0; buf[i] != '\n' && i < l; i++, j++) {
        valor[j] = buf[i];
      }
      float preco = atof(valor);

      posicao_atual = store(preco, nome, posicao_atual);
      // Escreve o código no ecra
      char cod[12];
      int e = sprintf(cod, "%d\n", codigo_atual);
      write(1, &cod, sizeof(e));
      ++codigo_atual;

      memset(nome, 0, sizeof(nome));
      memset(valor, 0, sizeof(valor));
      return codigo_atual;
}

void ma_altera_nome(char *buf, int posicao_atual, int l) {
      int i = 2;

      // Ler o código 
      char codigo[12] = {0};
      for (int j = 0; buf[i] != ' ' && i < l; i++, j++) {
        codigo[j] = buf[i];
      }
      i++;

      // Ler o nome
      char nome[4096] = {0};
      for (int j = 0; buf[i] != ' ' && buf[i] != '\n' && i < l; i++, j++) {
        nome[j] = buf[i];
      }
      ++i;

      // Alterar o nome
      altera_nome(atoi(codigo), nome, posicao_atual);
      memset(nome, 0, sizeof(nome));
      memset(codigo, 0, sizeof(codigo));

}

void ma_altera_preco(char *buf, int l) {
  int i = 2;

      // Ler o código
      char codigo[12] = {0};
      for (int j = 0; buf[i] != ' ' && i < l; i++, j++) {
        codigo[j] = buf[i];
      }
      i++;

      // Ler o valor
      char valor[12] = {0};
      for (int j = 0; buf[i] != '\n' && i < l; i++, j++) {
        valor[j] = buf[i];
      }
      float preco = atoi(valor);

      // Alterar o valor
      altera_preco(atoi(codigo), preco);
      
      memset(codigo, 0, sizeof(codigo));
      memset(valor, 0, sizeof(valor));
}



/*
void gimme(int codigo) {
  int fd = open("artigos", O_RDONLY);
  
  Artigo artigo;
  pread(fd,&artigo, sizeof(Artigo), codigo * sizeof(Artigo));
  printf("%d\n", artigo.posicao);
  printf("%f\n", artigo.preco);
}
*/