#ifndef STORAGE_H
#define STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif

void storage_init();
long storage_append_postings(int* docIDs, int count);
long storage_find_offset(const char* word);
int* storage_load_postings(long offset, int* count);

#ifdef __cplusplus
}
#endif

#endif
