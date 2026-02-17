#include "search.h"
#include "docmap.h"
#include "storage.h"

#include <iostream>
#include <vector>
#include <string>

void search_word(const std::string& word) {
    storage_load_dictionary();
    long offset = storage_find_offset(word.c_str());
    if (offset < 0) {
        std::cout << "No results found for: " << word << "\n";
        return;
    }

    int count;
    int* docIDs = storage_load_postings(offset, &count);
    if (!docIDs) {
        std::cout << "No results found for: " << word << "\n";
        return;
    }

    std::cout << "Results for '" << word << "':\n";
    for (int i = 0; i < count; i++) {
        std::cout << "  " << docmap_get(docIDs[i]) << "\n";
    }

    free(docIDs);
}
