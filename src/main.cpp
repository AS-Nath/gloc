#include <iostream>
#include <string>

extern void build_index(const std::string& dir);
extern void search_word(const std::string& word);

void print_help() {
    std::cout << "gloc - global locate (indexed search)\n";
    std::cout << "Usage:\n";
    std::cout << "  gloc -b <dir>   Build index\n";
    std::cout << "  gloc <word>     Search word\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_help();
        return 0;
    }

    std::string arg1 = argv[1];

    if (arg1 == "-h") {
        print_help();
    }
    else if (arg1 == "-b") {
        if (argc < 3) {
            std::cerr << "Error: missing directory\n";
            return 1;
        }
        build_index(argv[2]);
    }
    else {
        search_word(arg1);
    }

    return 0;
}
