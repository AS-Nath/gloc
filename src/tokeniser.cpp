#include "tokeniser.h"
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

// Tokenizes a line of text into lowercase alphanumeric words
std::vector<std::string> tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string word;

    while (ss >> word) {
        std::string clean;

        // Keep only alphanumeric characters, convert to lowercase
        for (char c : word) {
            if (std::isalnum(static_cast<unsigned char>(c))) {
                clean += std::tolower(static_cast<unsigned char>(c));
            }
        }

        if (!clean.empty()) {
            tokens.push_back(clean);
        }
    }

    return tokens;
}
