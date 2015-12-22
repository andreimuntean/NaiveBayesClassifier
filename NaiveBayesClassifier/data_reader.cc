#include <fstream>
#include <Windows.h>
#include "boost/filesystem.hpp"
#include "boost/foreach.hpp"
#include "data_reader.h"

// Reads the file from the specified path.
std::string read_file(const std::string& path)
{
	std::ifstream input(path, std::ios::in | std::ios::binary | std::ios::ate);
	auto file_size = input.tellg();
	std::vector<char> bytes(file_size);

	input.seekg(0, std::ios::beg);
	input.read(&bytes[0], file_size);

	return std::string(&bytes[0], file_size);
}

// Gets the names of the files from the specified directory.
std::vector<std::string> get_file_names(const std::string& path)
{
	std::vector<std::string> file_names;
	boost::filesystem::path directory_path(path);
	boost::filesystem::directory_iterator directory_iterator(directory_path);

	for (const boost::filesystem::path& path : directory_iterator)
	{
		if (is_directory(path) || is_regular_file(path))
		{
			file_names.push_back(path.string());
		}
	}

	return file_names;
}