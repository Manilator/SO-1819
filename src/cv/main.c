#include "cv.h"

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  int fifo0 = open("files/fifo_in", O_WRONLY);
  if (fifo0 == 0) {
    printf("Fifo_in Error\n");
  }
  char fifoname[21] = {0};

  pid_t id = getpid();
  sprintf(fifoname, "/tmp/%dfifo", id);
  mkfifo(fifoname, 0666);

  PFifo fifoid;
  int fifo1 = open(fifoname, O_RDWR);
  int l = 0;
  while ((l = readln(0, &fifoid.buf, 4096))) {
    
    // if (!cv_certificaBuf(fifoid.buf)) {
    //   fifoid = EmptyStruct;
    // }

    pid_t id = getpid();
    sprintf(fifoname, "/tmp/%dfifo", id);
    fifoid.fifoname = getpid();
    int p = write(fifo0, &fifoid, sizeof(PFifo));
    if (p == 0) {
      printf("Error writting to Server\n");
    }
    int espacos = -1;
    if (fifoid.buf[0] == 0 || fifoid.buf[0] == '\n') {
    } else {
      espacos = 0;
      for (int j = 0; j < l; j++) {
        if (fifoid.buf[j] == ' ') {
          ++espacos;
        }
      }
    }
    if (espacos == 0) {
      cv_mostraStock(fifo1);
    } else if (espacos == 1) {
      cv_atualizaStock(fifo1);
    }
    fifoid = EmptyStruct;
  }
  close(fifo0);
  close(fifo1);

  return 0;
}
