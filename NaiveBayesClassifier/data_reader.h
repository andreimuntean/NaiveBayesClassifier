#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

string read_file(const string path);
vector<string> get_file_names(const string directory);