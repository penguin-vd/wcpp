#include <cstdio>
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
    }
};

void print_args(char* name) {
    printf("Usage: %s [OPTIONS]... [FILE]\n", name);
    printf("Usage: %s [OPTIONS]... [DIR]\n", name);
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
    if (argc == 1) {
        params->def();
        return true;
    }

    for (int i = 1; i < argc; ++i) {

        // cannot parse -wyc
        char* arg = argv[i];
        if (strcmp(arg, "-c") == 0 || strcmp(arg, "--bytes") == 0) {
            params->bytes = true;
        } else if (strcmp(arg, "-m") == 0 || strcmp(arg, "--chars") == 0) {
            params->chars = true;
        } else if (strcmp(arg, "-l") == 0 || strcmp(arg, "--lines") == 0) {
            params->lines = true;
        } else if (strcmp(arg, "-L") == 0 || strcmp(arg, "--max-line-length") == 0) {
            params->max_line_length = true;
        } else if (strcmp(arg, "-w") == 0 || strcmp(arg, "--words") == 0) {
            params->words = true;
        } else {
            if (*filename != "") {
                return false;
            }
            *filename = arg;
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
    params.reset();
        
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
    printf(parse_file(filename, params).c_str());
    return 0;
}

