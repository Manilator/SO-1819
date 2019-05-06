#include "cv.h"

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  int fifo0 = open("files/fifo_in", O_WRONLY);

  char buf[4096] = {0};
  int l = 0;

  while ((l = readln(0, buf, 4096))) {

    write(fifo0, buf, l);

    int espacos = 0;
    for (int j = 0; j < l; j++) {
      if (buf[j] == ' ') {
        ++espacos;
      }
    }
    if (espacos == 0) {
      cv_mostraStock();
    }
    if (espacos == 1) {
      cv_atualizaStock();
    }
  }

  close(fifo0);

  return 0;
}
