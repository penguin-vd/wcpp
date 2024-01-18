#ifndef PARSE_FILE_H
#define PARSE_FILE_H
#endif

#include <string>
#include <array>
#include <vector>

using namespace std;

struct parameters { 
    bool bytes;
    bool chars;
    bool lines;
    bool max_line_length;
    bool words;
    bool recursive;
    bool sum;
    bool hasfilter;
    vector<string> filter;
    
    void reset() {
        bytes = false;
        chars = false;
        lines = false;
        max_line_length = false;
        words = false;
        recursive = false;
        sum = false;
        hasfilter = false;
        filter = {};
    }

    void def() {
        bytes = true;
        lines = true;
        words = true;
        max_line_length = false;
        chars = false;
        recursive = false;
        sum = false;
        hasfilter = false;
        filter = {};
    }
};

int get_num_words(const string &str);
int get_num_bytes(const string &filename);
array<int, 5> parse_file(const string& filename, parameters params);

