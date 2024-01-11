#include <cstdio>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include <string>

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

int parse_file(const std::string& filename) {
    std::string line;
    std::ifstream File(filename);
    
    int lines = 0;
    int words = 0;
    while (getline(File, line)) {
        lines++;
        words += get_word_count(line);        
    }

    return words;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_args(argv[0]);
        return 1;
    }
    
    std::string filename = argv[1];
    if (!file_exists(filename)) {
        printf("ERROR: could not find file with name %s.\n\n", filename.c_str());
        print_args(argv[0]);
        return 1;
    }   
    
    printf("File: %s, has %i words.\n", filename.c_str(), parse_file(filename));

    return 0;
}

