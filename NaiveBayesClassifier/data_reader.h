#pragma once

#include <string>
#include <vector>

std::string read_file(const std::string& path);
std::vector<std::string> get_file_names(const std::string& path);
void get_data(const std::string path, std::vector<std::string>& data);
void get_data(const std::string path, std::vector<std::string>& data, std::vector<std::string>& labels);