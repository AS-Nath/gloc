#include "search.h"
#include "docmap.h"
#include "storage.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

void search_term(const std::string& term) {
    init_files();
    std::cout << "[MAIN] Searching for: " << term << "\n";

    long offset = storage_find_offset(term.c_str());
    if (offset < 0) {
        std::cout << "No results found for: " << term << "\n";
        return;
    }

    int count = 0;
    int* docIDs = storage_load_postings(offset, &count);
    if (!docIDs || count == 0) {
        std::cout << "No results found for: " << term << "\n";
        return;
    }

    std::cout << "[SEARCH] Results for '" << term << "' (docIDs: " << count << ")\n";
    for (int i = 0; i < count; i++) {
        int docID = docIDs[i];
        const std::string& path = docmap_get(docID);
        if (!path.empty()) std::cout << "  [" << docID << "] " << path << "\n";
    }

    free(docIDs);
}
