#include <stdio.h>
#include <unistd.h>
#include "cbuf.h"
#include <pthread.h>

void usart_write(char *buf, int n) {
    usleep(1000000);
    char *end = buf+n;
    for (; buf != end; buf++){
        cputc(ccsin, *buf);
        usleep(200000);
    }
}
int usart_read(char *buf, int n) {
    char *end = buf+n;
    int r = 0;
    while (buf != end) {
        char c;
        while (!(c = creadc(ccsin)));
        putc(c, stdout);
        fflush(stdout);
        *buf = c;
        r++;
        if (c == '\n')
            break;
        //r++;
        buf++;
    }
    return r;
}

void* f(void* p) {
usart_write("xitam\n", 6);
}

pthread_t th;
int main() {
    cinit();
    pthread_create(&th, NULL, f, NULL);
    printf("post\n");
    char buf1[16] = {0};
    int r = usart_read(buf1, 16);
    pthread_join(th, NULL);
    write(0, buf1, r);
    printf("exit\n");
    return 0;
}