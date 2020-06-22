#ifndef CBUF_H
#define CBUF_H
#define BUFSZ 128
char sout_buf[BUFSZ], sin_buf[BUFSZ];

struct cbuf_t {
    char *h, *t, *e;
    char *buf;
    int nchar;
};
typedef struct cbuf_t* cbuf;

struct cbuf_t sout_s, sin_s;
cbuf csout = &sout_s, ccsin = &sin_s;

void makebuf(cbuf b, char *buf, int sz) {
    b->t = b->h = b->buf = buf;
    b->e = b->buf+sz;
}

int cputc(cbuf b, char c) {
    if (b->h+1 == b->t || b->h==b->e && b->t==b->buf)
        return 0;
    if (b->h == b->e)
        b->h = b->buf;
    else
        b->h++;
    *b->h = c;
    b->nchar++;
    return 1;
}
char creadc(cbuf b) {
    if (b->t == b->h)
        return 0;
    if (b->t == b->e)
        b->t = b->buf;
    else b->t++;
    b->nchar--;
    return *b->t;
}

int cempty(cbuf b) {
    return b->t+1 == b->h || b->t==b->e && b->h==b->buf;
}
void cinit() {
    makebuf(csout, sout_buf, BUFSZ);
    makebuf(ccsin, sin_buf, BUFSZ);
}
#endif