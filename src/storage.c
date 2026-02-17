#include "storage.h"
#include <stdio.h>

void storage_init() {
    printf("[storage] init\n");
}

long storage_append_postings(int* docIDs, int count) {
    return 0;
}

long storage_find_offset(const char* word) {
    return -1;
}

int* storage_load_postings(long offset, int* count) {
    *count = 0;
    return NULL;
}
