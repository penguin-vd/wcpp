#include <cstdio>

void print_args(char* name) {
    printf("Usage: %s [OPTIONS]... [FILE]\n", name);
    printf("Usage: %s [OPTIONS]... [DIR]\n", name);
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        print_args(argv[0]);
        return 1;
    }

    // parse args
    // if starts with - is options
    // if not it is an parameter or it is the file

    return 0;
}

