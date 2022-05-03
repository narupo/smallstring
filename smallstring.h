#pragma once

#include <string.h>
#include <stdlib.h>

typedef char SsBufMBType;

struct SsBufMB;
typedef struct SsBufMB SsBufMB;

extern SsBufMBType ss_dummy_buf[1];
#define SS_BUF_MB_INIT (SsBufMB) { .buf=ss_dummy_buf }

void
ss_free_array_mb(char **ary);

char **
ss_split_mb(const char *str, const char *seps);
