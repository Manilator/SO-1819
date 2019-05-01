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
    int fifo1 = open("files/fifo_out", O_RDONLY);

    char buf[4096] = {0};
    int l = 0;

    while ((l = readln(0, buf, 4096))) {
        
        write(fifo0,buf,4096);

        int espacos = 0;
        for (int j = 0; j < l; j++) {
          ++espacos;
        }
        if (espacos == 0) {
            Info new_info;
            read(fifo1,&new_info,4096);
            char quantidade[12] = {0};
            sprintf(quantidade, "%d\n", new_info.stock);
            char preco[12] = {0};
            sprintf(preco, "%d\n", new_info.preco);
            write(1,quantidade,sizeof(quantidade));
            write(1,preco, sizeof(preco));
        }
        if (espacos == 1) {
            char quantidade[12] = {0};
            read(fifo1,quantidade, sizeof(quantidade));
            write(1,quantidade,sizeof(quantidade));
        }

    }

    close(fifo0);
    close(fifo1);

    return 0;
}
