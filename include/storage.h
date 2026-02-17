#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PATH_MAX 4096

typedef struct dict_entry {
    char term[64];
    long offset;
    int count;
} dict_entry_t;

// initialize file paths
void init_files();

// append postings to postings.bin, return file offset
long storage_append_postings(const int* docIDs, int count);

// add dictionary entry (term + offset + count)
void storage_add_term(const char* term, long offset, int count);

// save dictionary to disk
void storage_save_dictionary();

// load dictionary from disk
dict_entry_t* storage_load_dictionary(int* out_count);

// find dictionary offset of a term, or -1 if not found
long storage_find_offset(const char* term);

// load postings from offset
int* storage_load_postings(long offset, int* out_count);

#ifdef __cplusplus
}
#endif
