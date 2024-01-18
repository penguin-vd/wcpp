#include "parse_dir.h"
#include <cstdio>
#include <filesystem>

using namespace std;

array<int, 5> sum_dir(const std::string dir, parameters params) {
    array<int, 5> final = {0, 0, 0, 0, 0};

    for (const auto& entry : filesystem::directory_iterator(dir)) {
        if (is_dir(entry.path())) {
            if (params.recursive) {
                final = sum_res(final, sum_dir(entry.path(), params));
            }
            continue;
        }
            
        if (params.hasfilter) {
            bool in_filter = false;
            
            for (const auto& f : params.filter) {
                if (entry.path().string().find(f) != string::npos) {
                    in_filter = true;
                }
            }         
            
            if (in_filter) {
                final = sum_res(final, parse_file(entry.path(), params));
            }
        } else {
            final = sum_res(final, parse_file(entry.path(), params));
        }
    }

    return final;
}

array<int, 5> sum_res(array<int, 5> dest, array<int, 5> src) {
    for (int i = 0; i < 5; ++i) {
        if (i == 4) {
            if (src[i] > dest[i]) {
                dest[i] = src[i];
            }
        } else {
            dest[i] += src[i];
        }
    }
    return dest;
}

void parse_dir(const std::string dir, parameters params) {
    for (const auto& entry : filesystem::directory_iterator(dir)) {
        if (is_dir(entry.path())) {
            if (params.recursive) {
                parse_dir(entry.path(), params);
            }
            continue;
        }
        if (params.hasfilter) {
            bool in_filter = false;
            
            for (const auto& f : params.filter) {
                if (entry.path().string().find(f) != string::npos) {
                    in_filter = true;
                }
            }         
            
            if (in_filter) {
                print_res(parse_file(entry.path(), params), entry.path());
            }
        } else {
            print_res(parse_file(entry.path(), params), entry.path());
        }
    }
}

bool is_dir(const string &name) {
    struct stat buffer;
    if (stat (name.c_str(), &buffer) == 0) {
        return buffer.st_mode & S_IFDIR;
    }
    return false;
}

void print_res(std::array<int, 5> res, std::string filename) {
    for (auto a : res) {
        if (a > 0) {
            printf("%i  ", a);
        }
    }
    printf("%s", filename.c_str());
    printf("\n");
}
