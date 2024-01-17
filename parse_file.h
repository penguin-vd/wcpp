#ifndef PARSE_FILE_H
#define PARSE_FILE_H
#include <array>
#endif

#include <string>

using namespace std;

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

int get_num_words(const string &str);
int get_num_bytes(const string &filename);
array<int, 5> parse_file(const string& filename, parameters params);

