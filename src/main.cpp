#include "indexer.h"
#include "search.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Usage:\n";
        std::cout << "  " << argv[0] << " index <directory>\n";
        std::cout << "  " << argv[0] << " search <term>\n";
        return 1;
    }

    std::string cmd = argv[1];
    if (cmd == "index") {
        std::string dir = argv[2];
        std::cout << "[MAIN] Indexing directory: " << dir << "\n";
        index_directory(dir);
    } else if (cmd == "search") {
        std::string term = argv[2];
        search_term(term);
    } else {
        std::cout << "Unknown command: " << cmd << "\n";
        return 1;
    }

    return 0;
}
