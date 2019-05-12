#include "sv.h"

int main() {

  int fifo0 = open("files/fifo_in", O_WRONLY);
  char buf[BUFFER_SIZE] = {0};
  char fifoname[21] = {0};

  pid_t id = getpid();
  sprintf(fifoname, "/tmp/%dfifo", id);
  mkfifo(fifoname, 0666);

  PFifo fifoid = EmptyPFifo;
  int fifo1 = open(fifoname, O_RDWR);
  int l = 0;
  while ((l = readln(0, buf, BUFFER_SIZE))) {
    const char s[2] = " ";
    char *token;
    if (!isdigit(buf[0])) {
      fifoid.cod = -1;
    } else {

      token = strtok(buf, s);
      if (token != NULL) {
        fifoid.cod = atoi(token);
      }
      token = strtok(NULL, s);
      if (token != NULL) {
        fifoid.quantidade = atoi(token);
      }
    }
    fifoid.fifoname = getpid();
    write(fifo0, &fifoid, sizeof(PFifo));
    if (fifoid.cod == -1) {
    } else {
      Info new_info = EmptyInfo;
      read(fifo1, &new_info, sizeof(Info));
      if (new_info.preco != -1 && new_info.stock != -1) {
        char return_stock[MAX_INT_SIZE] = {0};
        sprintf(return_stock, "%d\n", new_info.stock);
        write(1, return_stock, strlen(return_stock));
        if (fifoid.quantidade == 0) {
          char return_preco[MAX_INT_SIZE] = {0};
          sprintf(return_preco, "%f\n", new_info.preco);
          write(1, return_preco, strlen(return_preco));
        }
      }
    }
    fifoid = EmptyPFifo;
  }
  close(fifo0);
  close(fifo1);

  return 0;
}
