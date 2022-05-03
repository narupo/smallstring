#include "smallstring.h"

SsBufMBType ss_dummy_buf[1];

struct SsBufMB {
    SsBufMBType *buf;
    size_t capa;
    size_t len;
};

#define IS_DUMMY_BUF (self->buf == ss_dummy_buf)

void
ss_buf_mb_destroy(SsBufMB *self) {
    if (!IS_DUMMY_BUF) {
        free(self->buf);
    }
    // free(self);  DO NOT FREE SELF
}

SsBufMB *
ss_buf_mb_init(SsBufMB *self) {
    self->capa = 4;
    self->len = 0;

    if (!IS_DUMMY_BUF && self->buf) {
        free(self->buf);
    }

    self->buf = calloc(sizeof(SsBufMBType), self->capa + 1);
    if (self->buf == NULL) {
        return NULL;
    }

    return self;
}

SsBufMB *
ss_buf_mb_resize(SsBufMB *self, size_t new_capa) {
    SsBufMBType *buf = realloc(self->buf, new_capa);
    if (buf == NULL) {
        return NULL;
    }

    self->buf = buf;
    self->capa = new_capa;

    return self;
}

SsBufMB *
ss_buf_mb_push_back(SsBufMB *self, SsBufMBType c) {
    if (IS_DUMMY_BUF) {
        if (ss_buf_mb_init(self) == NULL) {
            return NULL;
        }
    }

    if (self->len >= self->capa) {
        if (ss_buf_mb_resize(self, self->capa * 2) == NULL) {
            return NULL;
        }
    }

    self->buf[self->len++] = c;
    return self;
}

void
ss_free_array_mb(char **ary) {
    for (char **p = ary; *p; p += 1) {
        free(*p);
    }
    free(ary);
}

char **
ss_split_mb(const char *str, const char *seps) {
    size_t len = strlen(str);
    size_t byte = sizeof(char *);
    size_t ary_capa = 4;
    size_t size = byte * ary_capa + byte;
    size_t ary_len = 0;

    char **ary = malloc(size);
    if (ary == NULL) {
        return NULL;
    }
    memset(ary, 0, size);

#define resize() { \
        ary_capa *= 2; \
        size = byte * ary_capa + byte; \
        char **tmp = realloc(ary, size); \
        if (tmp == NULL) { \
            ss_free_array_mb(ary); \
            return NULL; \
        } \
        ary = tmp; \
    } \

#define store() { \
        if (buf.len) { \
            ss_buf_mb_push_back(&buf, '\0'); \
            if (ary_len >= ary_capa) { \
                resize(); \
            } \
            ary[ary_len++] = buf.buf; \
            buf = SS_BUF_MB_INIT; \
        } \
    } \

    SsBufMB buf = SS_BUF_MB_INIT;

    for (size_t i = 0; i < len; i += 1) {
        char c = str[i];
        if (strchr(seps, c)) {
            store();
        } else {
            ss_buf_mb_push_back(&buf, c);
        }
    }

    store();
    ss_buf_mb_destroy(&buf);

    return ary;
}

