#include "storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char POSTINGS_FILE[PATH_MAX];
static char DICT_FILE[PATH_MAX];

#define MAX_DICT_ENTRIES 1024
static dict_entry_t dict[MAX_DICT_ENTRIES];
static int dict_count = 0;

void init_files() {
    char cwd[PATH_MAX];
    if (!getcwd(cwd, sizeof(cwd))) {
        perror("getcwd");
        exit(1);
    }

    snprintf(POSTINGS_FILE, sizeof(POSTINGS_FILE), "%s/postings.bin", cwd);
    snprintf(DICT_FILE, sizeof(DICT_FILE), "%s/dictionary.bin", cwd);

    // load existing dictionary if present
    FILE* f = fopen(DICT_FILE, "rb");
    if (f) {
        dict_count = fread(dict, sizeof(dict_entry_t), MAX_DICT_ENTRIES, f);
        fclose(f);
    }
}

long storage_append_postings(const int* docIDs, int count) {
    FILE* f = fopen(POSTINGS_FILE, "ab");
    if (!f) {
        perror("fopen postings.bin");
        exit(1);
    }
    long offset = ftell(f);
    fwrite(docIDs, sizeof(int), count, f);
    fclose(f);
    return offset;
}

void storage_add_term(const char* term, long offset, int count) {
    if (dict_count >= MAX_DICT_ENTRIES) {
        fprintf(stderr, "Dictionary full\n");
        exit(1);
    }
    strncpy(dict[dict_count].term, term, sizeof(dict[dict_count].term)-1);
    dict[dict_count].term[sizeof(dict[dict_count].term)-1] = 0;
    dict[dict_count].offset = offset;
    dict[dict_count].count = count;
    dict_count++;
}

void storage_save_dictionary() {
    FILE* f = fopen(DICT_FILE, "wb");
    if (!f) {
        perror("fopen dictionary.bin");
        exit(1);
    }
    fwrite(dict, sizeof(dict_entry_t), dict_count, f);
    fclose(f);
}

dict_entry_t* storage_load_dictionary(int* out_count) {
    *out_count = dict_count;
    return dict;
}

long storage_find_offset(const char* term) {
    for (int i = 0; i < dict_count; i++) {
        if (strcmp(dict[i].term, term) == 0) {
            return dict[i].offset;
        }
    }
    return -1;
}

int* storage_load_postings(long offset, int* out_count) {
    for (int i = 0; i < dict_count; i++) {
        if (dict[i].offset == offset) {
            *out_count = dict[i].count;
            int* arr = (int*)malloc(sizeof(int) * (*out_count));
            FILE* f = fopen(POSTINGS_FILE, "rb");
            if (!f) return NULL;
            fseek(f, offset, SEEK_SET);
            fread(arr, sizeof(int), *out_count, f);
            fclose(f);
            return arr;
        }
    }
    *out_count = 0;
    return NULL;
}
