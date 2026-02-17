#include "docmap.h"

#include <vector>

static std::vector<std::string> docmap;

void docmap_add(int docID, const std::string& path) {
    if (docID >= (int)docmap.size()) {
        docmap.resize(docID + 1);
    }
    docmap[docID] = path;
}

const std::string& docmap_get(int docID) {
    return docmap[docID];
}

int docmap_size() {
    return docmap.size();
}
