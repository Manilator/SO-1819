#include "cv.h"

void cv_mostraStock(int fifo1) {
  Info new_info;

  int l = read(fifo1, &new_info, 4096);
  printf("Stock: %d\n", new_info.stock);
  printf("Preço: %d\n", new_info.preco);
  if (l == 0) {
    printf("Error reading from unique client pipe\n");
  }

  char quantidade[12] = {0};
  sprintf(quantidade, "%d\n", new_info.stock);
  char preco[12] = {0};
  sprintf(preco, "%d\n", new_info.preco);
  int p = write(1, quantidade, sizeof(quantidade));
  printf("Printei a quantidade\n");
  if (p == 0) {
    printf("Error writting quantidade to stdout\n");
  }
  int y = write(1, preco, sizeof(preco));
  printf("Printei o preço\n");
  if (y == 0) {
    printf("Error writting preço to stdout\n");
  }
}

void cv_atualizaStock(int fifo1) {
  char quantidade[12] = {0};

  read(fifo1, quantidade, sizeof(quantidade));
  printf("Li a quantidade do pipe único\n");
  if (fifo1 == 0) {
    printf("Error reading from unique client pipe\n");
  }

  int p = write(1, quantidade, sizeof(quantidade));
  printf("quantidade: %d\n", atoi(quantidade));
  if (p == 0) {
    printf("Error writting quantidade to stdout\n");
  }
}

// int cv_certificaBuf(char *buf) {
//   int i = 0;
//   int l = strlen(buf);
//   int espacos = 0;
//   // Certificar quantos parametros
//   for (int j = 0 ; j < l; j++) {
//     if (buf[j] == ' ') {
//       espacos++;
//     }
//   }
//   if (espacos > 1) {
//     return 0;
//   }

//   // certificar primeiro argumento
//   if (espacos == 0) {
//     for (; i < (int)strlen(buf) - 1; i++) {
//       if (!isdigit(buf[i])) {
//         return 0;
//       }
//     }
//   } else if (espacos == 1) {
//     for (; i < (int)strlen(buf) - 1; i++) {
//       if (!isdigit(buf[i])) {
//         return 0;
//       }
//     }
//     ++i;
//     for (; i < (int)strlen(buf) - 1; i++) {
//       if (!isdigit(buf[i])) {
//         return 0;
//       }
//     }
//   }
//   return 1;
// }