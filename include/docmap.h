#ifndef DOCMAP_H
#define DOCMAP_H

#include <string>

void docmap_add(int docID, const std::string& path);
const std::string& docmap_get(int docID);
int docmap_size();

#endif
