#include "smallstring.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

static void
test_split_mb(void) {
    char **toks;

    toks = ss_split_mb("", " ");
    assert(toks);
    assert(toks[0] == NULL);
    ss_free_array_mb(toks);

    toks = ss_split_mb("123", " ");
    assert(toks);
    assert(strcmp(toks[0], "123") == 0);
    assert(toks[1] == NULL);
    ss_free_array_mb(toks);

    toks = ss_split_mb("123 223", " ");
    assert(toks);
    assert(strcmp(toks[0], "123") == 0);
    assert(strcmp(toks[1], "223") == 0);
    assert(toks[2] == NULL);
    ss_free_array_mb(toks);

    toks = ss_split_mb("123 223  323", " ");
    assert(toks);
    assert(strcmp(toks[0], "123") == 0);
    assert(strcmp(toks[1], "223") == 0);
    assert(strcmp(toks[2], "323") == 0);
    assert(toks[3] == NULL);
    ss_free_array_mb(toks);

    toks = ss_split_mb("  123 223  323  ", " ");
    assert(toks);
    assert(strcmp(toks[0], "123") == 0);
    assert(strcmp(toks[1], "223") == 0);
    assert(strcmp(toks[2], "323") == 0);
    assert(toks[3] == NULL);
    ss_free_array_mb(toks);

    toks = ss_split_mb("  123,223 ,323  ", " ,");
    assert(toks);
    assert(strcmp(toks[0], "123") == 0);
    assert(strcmp(toks[1], "223") == 0);
    assert(strcmp(toks[2], "323") == 0);
    assert(toks[3] == NULL);
    ss_free_array_mb(toks);
}

int main(void) {
    test_split_mb();
    puts("OK");
    return 0;
}
