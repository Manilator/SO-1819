#ifndef UTIL_H
#define UTIL_H

#include <unistd.h>

/**
 * Função que lê linha a linha de um input
 *
 * @param fildes Input a ser lido.
 * @param *buf Buffer para onde vai ser lido.
 * @param nbyte Tamanho em bytes a ser lido.
 */
ssize_t readln(int fildes, void *buf, size_t nbyte);

#endif /* UTIL_H*/