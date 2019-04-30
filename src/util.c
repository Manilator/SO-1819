#include "util.h"

ssize_t readln(int fildes, void *buf, size_t nbyte)
{

    size_t n = 0;
    char *buff = (char *)buf;
    while (read(fildes, buff + n, 1))
    {
        if (buff[n] == '\n')
        {
            n++;
            break;
        }
        if (n >= nbyte - 1)
        {
            n++;
            break;
        }
        n++;
    }
    return n;
}