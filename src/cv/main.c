#include "utils.h"
#include "sv.h"

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
        
        write(fifo0,buf,l);

        int espacos = 0;
        for (int j = 0; j < l; j++) {
          if (buf[j] == ' ') {
          ++espacos;
        }
        }
        if (espacos == 0) {
            Info new_info;
            int fifo1 = open("files/fifo_out", O_RDONLY);
            read(fifo1,&new_info,4096);
            close(fifo1);
            char quantidade[12] = {0};
            sprintf(quantidade, "%d\n", new_info.stock);
            char preco[12] = {0};
            sprintf(preco, "%d\n", new_info.preco);
            write(1,quantidade,sizeof(quantidade));
            write(1,preco, sizeof(preco));
        }
        if (espacos == 1) {
            char quantidade[12] = {0};
            int fifo1 = open("files/fifo_out", O_RDONLY);
            read(fifo1,quantidade, sizeof(quantidade));
            close(fifo1);
            write(1,quantidade,sizeof(quantidade));
        }

    }

    close(fifo0);

    return 0;
}

