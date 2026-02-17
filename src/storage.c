#include "storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POSTINGS_FILE "postings.bin"
#define DICT_FILE "dictionary.bin"

typedef struct {
    char* term;
    long offset;
} dict_entry;

static dict_entry* dict = NULL;
static size_t dict_size = 0;

// Append a posting list
long storage_append_postings(int* docIDs, int count) {
    FILE* f = fopen(POSTINGS_FILE, "ab");
    if (!f) return -1;

    fseek(f, 0, SEEK_END);
    long offset = ftell(f);

    fwrite(&count, sizeof(int), 1, f);
    fwrite(docIDs, sizeof(int), count, f);

    fclose(f);
    return offset;
}

// Lookup a term
long storage_find_offset(const char* word) {
    for (size_t i = 0; i < dict_size; i++) {
        if (strcmp(dict[i].term, word) == 0) return dict[i].offset;
    }
    return -1;
}

// Load postings from offset
int* storage_load_postings(long offset, int* out_count) {
    FILE* f = fopen(POSTINGS_FILE, "rb");
    if (!f) return NULL;

    fseek(f, offset, SEEK_SET);

    int count;
    fread(&count, sizeof(int), 1, f);

    int* docIDs = (int*)malloc(sizeof(int) * count);
    fread(docIDs, sizeof(int), count, f);

    fclose(f);

    if (out_count) *out_count = count;
    return docIDs;
}

// Add entry to dictionary
static void dict_add(const char* term, long offset) {
    dict = (dict_entry*)realloc(dict, sizeof(dict_entry) * (dict_size + 1));
    dict[dict_size].term = strdup(term);
    dict[dict_size].offset = offset;
    dict_size++;
}

// Save dictionary to disk
void storage_save_dictionary() {
    FILE* f = fopen(DICT_FILE, "wb");
    if (!f) return;

    fwrite(&dict_size, sizeof(size_t), 1, f);
    for (size_t i = 0; i < dict_size; i++) {
        size_t len = strlen(dict[i].term);
        fwrite(&len, sizeof(size_t), 1, f);
        fwrite(dict[i].term, 1, len, f);
        fwrite(&dict[i].offset, sizeof(long), 1, f);
    }

    fclose(f);
}

// Load dictionary from disk
void storage_load_dictionary() {
    FILE* f = fopen(DICT_FILE, "rb");
    if (!f) return;

    fread(&dict_size, sizeof(size_t), 1, f);
    dict = (dict_entry*)malloc(sizeof(dict_entry) * dict_size);

    for (size_t i = 0; i < dict_size; i++) {
        size_t len;
        fread(&len, sizeof(size_t), 1, f);
        dict[i].term = (char*)malloc(len + 1);
        fread(dict[i].term, 1, len, f);
        dict[i].term[len] = '\0';
        fread(&dict[i].offset, sizeof(long), 1, f);
    }

    fclose(f);
}

// Expose dictionary add to indexer
void storage_add_term(const char* term, long offset) {
    dict_add(term, offset);
}
