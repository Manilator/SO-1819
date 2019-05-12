#include "ma.h"
#include "utils.h"

int main() {

  int fifo0 = open("files/fifo_in", O_WRONLY);

  char buf[BUFFER_SIZE] = {0};
  char nome[100] = {0};
  int posicao_atual = 0;
  int codigo = 0;
  ssize_t l;
  PFifo fifoid = EmptyPFifo;

  while ((l = readln(0, buf, BUFFER_SIZE))) {
    if ('i' == buf[0]) {
      fifoid.comando = 'i';
      if (buf[1] != ' ') {
        fifoid.cod = -1;
      } else {
        const char s[2] = " ";
        char *token;
        token = strtok(buf, s);
        if (token != NULL) {
          token = strtok(NULL, s);
          strcpy(nome, token);
        }
        token = strtok(NULL, s);
        if (token != NULL) {
          fifoid.preco = atof(token);
        }
      }
      write(fifo0, &fifoid, sizeof(PFifo));
      posicao_atual = store(fifoid.preco, nome, posicao_atual);
      char cod[MAX_INT_SIZE];
      sprintf(cod, "%d\n", codigo);
      write(1, cod, strlen(cod));
      ++codigo;
      memset(nome, 0, strlen(nome));
    } else if ('n' == buf[0]) {
      if (buf[1] != ' ') {
      } else {
        char s_codigo[MAX_INT_SIZE] = {0};
        const char s[2] = " ";
        char *token;
        token = strtok(buf, s);
        if (token != NULL) {
          token = strtok(NULL, s);
          strcpy(s_codigo, token);
        }
        token = strtok(NULL, s);
        if (token != NULL) {
          strcpy(nome, token);
        }
        nome[strlen(nome) - 1] = '\0';

        posicao_atual = altera_nome(atoi(s_codigo), nome, posicao_atual);
        memset(nome, 0, sizeof(nome));
        memset(s_codigo, 0, sizeof(s_codigo));
      }
    } else if ('p' == buf[0]) {
      char s_codigo[MAX_INT_SIZE] = {0};
      float preco;
      const char s[2] = " ";
      char *token;
      token = strtok(buf, s);
      if (token != NULL) {
        token = strtok(NULL, s);
        strcpy(s_codigo, token);
      }
      token = strtok(NULL, s);
      if (token != NULL) {
        preco = atof(token);
      }

      altera_preco(atoi(s_codigo), preco);

      memset(s_codigo, 0, strlen(s_codigo));
    } else if ('a' == buf[0]) {
      int pd[2];
      int pd2[2];
      pipe(pd);
      pipe(pd2);
      switch (fork()) {
      case -1:
        perror("fork");
        return -1;
      case 0:
        // child
        close(pd[1]);
        dup2(pd[0], 0);
        close(pd[0]);
        int fd2 = open("files/agregacoes_ma", O_CREAT | O_WRONLY, 0666);
        dup2(fd2, 1);
        execlp("./ag", "./ag", NULL);
      default:
        // parent
        close(pd[0]);
        char buf[BUFFER_SIZE];
        int l;
        int fd = open("files/vendas", O_RDONLY);
        while ((l = readln(fd, buf, sizeof(buf)))) {
          write(pd[1], buf, l);
        }
        close(pd[1]);
        wait(NULL);
      }
    }
    memset(buf, 0, sizeof(buf));
    fifoid = EmptyPFifo;
  }
  close(fifo0);

  return 0;
}
