#include <iostream>
#include "data_reader.h"
#include "naive_bayes.h"

static void get_training_data(const std::string path, std::vector<std::string>& data, std::vector<std::string>& labels)
{
	// Iterates through every training class.
	for (const auto& directory_path : get_file_names(path))
	{
		// Uses directory names as data labels.
		auto label = directory_path.substr(path.length() + 1);

		// Iterates through every training data for this class.
		for (const auto& file_path : get_file_names(directory_path))
		{
			data.push_back(read_file(file_path));
			labels.push_back(label);
		}
	}
}

int main()
{
	std::vector<std::string> data;
	std::vector<std::string> labels;

	get_training_data("data", data, labels);

	NaiveBayes naive_bayes;

	naive_bayes.train(data, labels);
	
	// Tests the classifier using data from the training set:
	std::cout << "Coldplay: " << naive_bayes.predict("you don't know how lovely you are") << std::endl;
	std::cout << "Radiohead: " << naive_bayes.predict("let down and hanging around") << std::endl;
	std::cout << "Taylor Swift: " << naive_bayes.predict("shake it off, shake it off") << std::endl;

	// Tests the classifier using new data:
	std::cout << "Coldplay: " << naive_bayes.predict("you came along and you cut me loose") << std::endl;
	std::cout << "Radiohead: " << naive_bayes.predict("we're here to keep your prices down") << std::endl;
	std::cout << "Taylor Swift: " << naive_bayes.predict("I'd give everything / to have you here today") << std::endl;

	system("pause");
	
	return 0;
}