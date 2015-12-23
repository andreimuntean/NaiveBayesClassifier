#include <fstream>
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

void get_data(const std::string path, std::vector<std::string>& data)
{
	// Iterates through every data.
	for (const auto& file_path : get_file_names(path))
	{
		data.push_back(read_file(file_path));
	}
}

void get_data(const std::string path, std::vector<std::string>& data, std::vector<std::string>& labels)
{
	// Iterates through every class.
	for (const auto& directory_path : get_file_names(path))
	{
		// Uses directory names as data labels.
		auto label = directory_path.substr(path.length() + 1);

		// Iterates through every data for this class.
		for (const auto& file_path : get_file_names(directory_path))
		{
			data.push_back(read_file(file_path));
			labels.push_back(label);
		}
	}
}