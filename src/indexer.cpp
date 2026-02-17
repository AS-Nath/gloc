#include "indexer.h"
#include "tokeniser.h"
#include "docmap.h"
#include "storage.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

// In-memory inverted index
static std::unordered_map<std::string, std::vector<int>> inverted_index;

// Index a single file
static void index_file(const std::string& path, int docID) {
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "Failed to open: " << path << "\n";
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        auto tokens = tokenize(line);
        for (const auto& word : tokens) {
            auto& posting = inverted_index[word];
            if (posting.empty() || posting.back() != docID)
                posting.push_back(docID);
        }
    }
}

// Build index for a root directory
void build_index(const std::string& root) {
    int docID = 0;

    for (const auto& entry : fs::recursive_directory_iterator(root)) {
        if (!entry.is_regular_file()) continue;

        std::string path = entry.path().string();
        docmap_add(docID, path);

        index_file(path, docID);

        std::cout << "Indexed [" << docID << "] " << path << "\n";
        docID++;
    }

    // Write inverted index to disk via storage.c
    for (auto& [word, posting] : inverted_index) {
        long offset = storage_append_postings(posting.data(), posting.size());
        storage_add_term(word.c_str(), offset);
    }

    storage_save_dictionary();
    std::cout << "Indexing complete. Terms saved to disk.\n";
}
