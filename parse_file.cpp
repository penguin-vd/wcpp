#include "parse_file.h"

#include <array>
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include <string>

using namespace std;

int get_num_words(const string& str) {
    istringstream iss(str);    
    vector<string> words;
    
    // c++ magic
    copy(istream_iterator<string>(iss),
            istream_iterator<string>(),
            back_inserter(words));

    return words.size();
}

int get_num_bytes(const string& filename) {
    ifstream file(filename, ios::binary);
    file.seekg(0, ios::end);
    int bytes = file.tellg();
    file.close();
    return bytes;
}


array<int, 5> parse_file(const string& filename, parameters params) {
    int lines = 0;
    int words = 0;
    int chars = 0;
    int max_line_length = 0;
    int bytes = 0;

    if (params.bytes) {
        bytes = get_num_bytes(filename);
    }

    string line;
    ifstream file(filename, ios::binary);
    
    while (getline(file, line)) {
        if (params.lines) {
            lines++;
        }

        if (params.chars) {
            chars += line.length();
        }

        if (params.words) {
            words += get_num_words(line);
        }

        if (params.max_line_length) {
            if (line.length() > max_line_length) {
                max_line_length = line.length();
            }
        }
    }

    file.close();
    return {lines, words, chars, bytes, max_line_length};
}

