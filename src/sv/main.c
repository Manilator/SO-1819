#include "sv.h"
#include <string.h>

int main() {

  mkfifo("files/fifo_in", 0666);

  if (!fork()) {

    for (;;) {
      printf("Entrei no loop\n");

      int fifo1;
      int l;
      PFifo fifoid;
      int fifo0 = open("files/fifo_in", O_RDONLY);
      if (fifo0 == 0) {
        printf("Error opening Fifo_In\n");
      }
      while (l = read(fifo0, &fifoid, sizeof(PFifo))) {
        printf("Inicio do While\n");
        if (l == 0) {
          printf("Error reading from client\n");
        }

        int espacos = -1;
        printf("%d\n", l);
        l = strlen(fifoid.buf);

        char fifoname[21] = {0};
        sprintf(fifoname, "/tmp/%dfifo", fifoid.fifoname);

        if ('i' == fifoid.buf[0]) {
          sv_criaStock(fifoid.buf, l);
        } else if (fifoid.buf[0] == 0 || fifoid.buf[0] == '\n') {
          fifo1 = open(fifoname, O_WRONLY);
        } else {
          espacos = 0;
          for (int j = 0; j < l; j++) {
            if (fifoid.buf[j] == ' ') {
              ++espacos;
            }
          }

          if (0 == espacos) {
            fifo1 = sv_mostraStock(fifoid, l);
          } else if (1 == espacos) {
            fifo1 = sv_atualizaStock(fifoid, l);
          }
        }
        fifoid = EmptyStruct;
      }
      close(fifo0);
    }
    _exit(0);
  }
  return 0;
}
