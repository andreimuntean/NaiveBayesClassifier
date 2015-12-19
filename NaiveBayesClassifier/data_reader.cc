#include <fstream>
#include <vector>
#include <Windows.h>

using std::string;
using std::vector;
using std::wstring;

// Reads the file from the specified path as a string.
string read_file(const string path)
{
	std::ifstream file(path, std::ios::in || std::ios::binary);

	if (!file)
	{
		throw errno;
	}

	string contents;

	file.seekg(0, std::ios::end);
	contents.resize(file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&contents[0], contents.size());
	file.close();

	return contents;
}

// Lists the names of the files from the specified path. This only works for Windows.
vector<string> get_file_names(const string path)
{
	vector<string> file_names;
	WIN32_FIND_DATAA data;
	HANDLE h_find = FindFirstFileA(path.c_str(), &data);

	if (h_find != INVALID_HANDLE_VALUE)
	{
		do
		{
			const string& file_name = data.cFileName;

			if (file_name.compare(0, 1, ".") == 0)
			{
				continue;
			}

			file_names.push_back(file_name);
		}
		while (FindNextFileA(h_find, &data));
	}

	FindClose(h_find);

	return file_names;
}