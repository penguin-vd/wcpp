#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <string>
#include "parse_file.h"
#include "parse_dir.h"

using namespace std;

void print_args(char* name) {
    printf("Usage: %s [OPTIONS]... [FILE]\n", name);
    printf("   or: %s [OPTIONS]... [DIR]\n", name);
    
    printf("\n\n");
    printf("  -c, --bytes\t\tprint the byte counts\n");
    printf("  -m, --chars\t\tprint the character counts\n");
    printf("  -l, --lines\t\tprint the newline counts\n");
    printf("  -L, --max-line-length\tprint the maximum display width\n");
    printf("  -w, --words\t\tprint the word counts\n");
    printf("  -r, --recursive\trecursively parse through a directory\n");
    printf("  -s, --sum\t\tsum all information of a directory\n");
    printf("      --filter STRING\tfilter the files when going through a directory\n");
    printf("         e.g. .cpp,.h\n\n");
    printf("      --help\t\tprint this help information and exit\n");
}

bool file_exists(const string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

void parse_filter(char* filter, parameters* params) {
    std::string f = "";
    
    int i = 0;
    while (filter[i]) {
        if (filter[i] == ',') {
            if (f != "") {
                params->filter.push_back(f);
                f = "";
            }
        } else {
            f += filter[i];
        }

        ++i;
    } 
    if (f != "") {
        params->filter.push_back(f);
    }
}

bool parse_args(int argc, char* argv[], parameters* params, string* filename) {
    bool isdef = true;

    for (int i = 1; i < argc; ++i) {
        char* arg = argv[i];
        
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
            } else if (strcmp(arg, "--recursive") == 0) {
                params->recursive = true;
            } else if (strcmp(arg, "--sum") == 0) {
                params->sum = true;
            } else if (strcmp(arg, "--filter") == 0) {
                params->hasfilter = true;
                if (!argv[i+1]) {
                    return false;
                }

                parse_filter(argv[i+1], params);
                i++;
            } else if (strcmp(arg, "--help") == 0) {
                print_args(argv[0]);
                exit(0);
            } else {
                return false;
            }
            
            continue;
        }

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
            } else if (arg[x] == 'r') {
                params->recursive = true;
            } else if (arg[x] == 's') {
                params->sum = true;
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
        
    string filename;
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

    if (is_dir(filename)) {
        if (params.sum) {
            print_res(sum_dir(filename, params), filename);
            return 0;
        }
        parse_dir(filename, params);
        return 0;
    }

    print_res(parse_file(filename, params), filename);
           

    return 0;
}
