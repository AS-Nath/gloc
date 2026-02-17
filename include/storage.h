#ifndef STORAGE_H
#define STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif

// Append a posting list to postings.bin
// Returns the file offset where this list starts
long storage_append_postings(int* docIDs, int count);

// Find the file offset of a term
long storage_find_offset(const char* word);

// Load postings from an offset
// Returns a dynamically allocated array of docIDs and sets count
int* storage_load_postings(long offset, int* count);

// Save/load dictionary to/from disk
void storage_save_dictionary();
void storage_load_dictionary();
// Add a term → offset mapping (used during indexing)
void storage_add_term(const char* term, long offset);

#ifdef __cplusplus
}
#endif

#endif // STORAGE_H
