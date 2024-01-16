#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include <string>

struct parameters { 
    bool bytes;
    bool chars;
    bool lines;
    bool max_line_length;
    bool words;
    
    void reset() {
        bytes = false;
        chars = false;
        lines = false;
        max_line_length = false;
        words = false;
    }

    void def() {
        bytes = true;
        lines = true;
        words = true;
        max_line_length = false;
        chars = false;
    }
};

void print_args(char* name) {
    printf("Usage: %s [OPTIONS]... [FILE]\n", name);
    printf("   or: %s [OPTIONS]... [DIR]\n", name);
    
    printf("\n\n");
    printf("  -c, --bytes\t\tprint the byte counts\n");
    printf("  -m, --chars\t\tprint the character counts\n");
    printf("  -l, --lines\t\tprint the newline counts\n");
    printf("  -L, --max-line-length\tprint the maximum display width\n");
    printf("  -w, --words\t\tprint the word counts\n");
    printf("      --help\t\tprint this help information and exit\n");
    printf("      --version\t\tprint version information and exit\n");
}

bool file_exists(const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

int get_word_count(const std::string& str) {
    std::istringstream iss(str);    
    std::vector<std::string> words;

    std::copy(std::istream_iterator<std::string>(iss),
            std::istream_iterator<std::string>(),
            std::back_inserter(words));

    return words.size();
}

std::string parse_file(const std::string& filename, parameters params) {
    std::string res = "";
    std::string line;
    std::ifstream File(filename);
    
    int lines = 0;
    int words = 0;
    int chars = 0;
    int max_line_length = 0;
    while (getline(File, line)) {
        lines++;
        words += get_word_count(line);
        chars += line.length(); // not good
        if (line.length() > max_line_length) {
            max_line_length = line.length();
        }
    }

    res += filename + " ";
    
    if (params.lines) {
        res += "Lines: " + std::to_string(lines) + " ";
    }

    if (params.max_line_length) {
        res += "Max Width Line: " + std::to_string(max_line_length) + " ";
    }

    if (params.words) {
        res += "Words: " + std::to_string(words) + " ";
    }

    if (params.chars) {
        res += "Chars: " + std::to_string(chars) + " ";
    }

    if (params.bytes) {
        res += "Bytes: " + std::to_string(0) + " "; // this aint it chief
    }

    res += "\n";

    return res;
}

bool parse_args(int argc, char* argv[], parameters* params, std::string* filename) {
    bool isdef = true;

    for (int i = 1; i < argc; ++i) {
        char* arg = argv[i];
        
        // check if it is a file or dir
        if (arg[0] != '-') {
            if (*filename != "") {
                return false;
            }
            *filename = arg;
            continue;
        }
        
        if (isdef) {
            params->reset();
            isdef = false;
        }

        // check if it is a full param
        if (arg[1] == '-') {
            if (strcmp(arg, "--bytes") == 0 ) {
                params->bytes = true;
            } else if (strcmp(arg, "--lines") == 0) {
                params->lines = true;
            } else if (strcmp(arg, "--chars") == 0) {
                params->chars = true;
            } else if (strcmp(arg, "--words") == 0) {
                params->words = true;
            } else if (strcmp(arg, "--max-line-length") == 0) {
                params->max_line_length = true;
            } else if (strcmp(arg, "--help") == 0) {
                print_args(argv[0]);
                exit(0);
            } else if (strcmp(arg, "--version") == 0) {
                // print version
                exit(0);
            } else {
                return false;
            }
            
            continue;
        }

        // parse short params
        int x = 1;
        while (arg[x]) {
            if (arg[x] == 'c') {
                params->bytes = true;
            } else if (arg[x] == 'm') {
                params->chars = true;
            } else if (arg[x] == 'l') {
                params->lines = true;
            } else if (arg[x] == 'L') {
                params->max_line_length -= true;
            } else if (arg[x] == 'w') {
                params->words = true;
            } else {
                return false;
            }

            x++;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_args(argv[0]);
        return 1;
    }
    
    parameters params;
    params.def();
        
    std::string filename;
    if (!parse_args(argc, argv, &params, &filename)) {
        printf("ERROR: wrong usage of arguments.\n\n");
        print_args(argv[0]);
        return 1;
    }

    if (!file_exists(filename)) {
        printf("ERROR: could not find file with name %s.\n\n", filename.c_str());
        print_args(argv[0]);
        return 1;
    }
    printf("%s", parse_file(filename, params).c_str());
    return 0;
}

