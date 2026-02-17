#include "tokeniser.h"

#include <cctype>

std::vector<std::string> tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::string word;

    for (char c : text) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            word += std::tolower(static_cast<unsigned char>(c));
        } else {
            if (!word.empty()) {
                tokens.push_back(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) tokens.push_back(word);

    return tokens;
}
