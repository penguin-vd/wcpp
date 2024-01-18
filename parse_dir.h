#ifndef PARSE_FILE_H
#define PARSE_FILE_H
#include <string>
#include <vector>
#include <array>
#include "parse_file.h"
#include <sys/stat.h>
#endif


std::array<int, 5> sum_dir(const std::string dir, parameters params);
void parse_dir(const std::string dir, parameters params);
bool is_dir(const string& name);
void print_res(std::array<int, 5> res, std::string filename);  
array<int, 5> sum_res(array<int, 5> dest, array<int, 5> src);
