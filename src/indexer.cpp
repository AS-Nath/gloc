#include "indexer.h"
#include "tokeniser.h"
#include "docmap.h"
#include "storage.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

namespace fs = std::filesystem;

static std::unordered_map<std::string, std::vector<int>> inverted_index;

static void index_file(const std::string& filepath, int docID) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "[INDEXER] Failed to open: " << filepath << "\n";
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        auto tokens = tokenize(line);
        for (const auto& word : tokens) {
            auto& posting = inverted_index[word];
            if (posting.empty() || posting.back() != docID)
                posting.push_back(docID);
        }
    }
}

static void save_index_to_disk() {
    for (const auto& pr : inverted_index) {
        const std::string& term = pr.first;
        const auto& postings = pr.second;
        long offset = storage_append_postings(postings.data(), postings.size());
        storage_add_term(term.c_str(), offset, postings.size());
    }
    storage_save_dictionary();
}

void index_directory(const std::string& root) {
    init_files();

    int docID = 0;
    for (const auto& entry : fs::recursive_directory_iterator(root)) {
        if (!entry.is_regular_file()) continue;
        std::string path = entry.path().string();
        docmap_add(docID, path);
        index_file(path, docID);
        std::cout << "[INDEXER] Indexed [" << docID << "]: " << path << "\n";
        docID++;
    }

    save_index_to_disk();
    std::cout << "=== Indexing complete ===\n";
    std::cout << "Unique terms: " << inverted_index.size() << "\n";
}
