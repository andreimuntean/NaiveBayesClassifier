#include <iomanip>
#include <iostream>
#include "data_reader.h"
#include "naive_bayes.h"

void perform_custom_tests()
{
	std::cout << "Reading data..." << std::endl;

	std::vector<std::string> training_data, training_labels;
	std::vector<std::string> test_data;

	get_data("data/custom/training", training_data, training_labels);
	get_data("data/custom/test", test_data);

	NaiveBayes naive_bayes;

	std::cout << "Training..." << std::endl;
	naive_bayes.train(training_data, training_labels);

	for (const auto& data : test_data)
	{
		const auto& probabilities = naive_bayes.estimate_probabilities(data);

		std::cout << std::endl << "\"" << data.substr(0, 50) << "\":" << std::endl;
		
		for (const auto& probability : probabilities)
		{
			std::cout << "  " << probability.first << ": " << probability.second << std::endl;
		}
	}
}

void perform_spam_tests()
{
	std::cout << "Reading data..." << std::endl;

	std::vector<std::string> training_data, training_labels;
	std::vector<std::string> test_data, test_labels;

	get_data("data/emails/training", training_data, training_labels);
	get_data("data/emails/test", test_data, test_labels);

	NaiveBayes naive_bayes;

	std::cout << "Training..." << std::endl;
	naive_bayes.train(training_data, training_labels);
	std::cout << "Predicting..." << std::endl;

	double accuracy = 0;

	for (int index = 0; index < test_data.size(); ++index)
	{
		auto prediction = naive_bayes.predict(test_data[index]);

		if (prediction == test_labels[index])
		{
			++accuracy;
		}
	}

	std::cout << "Accuracy: " << accuracy << "/" << test_data.size()
		<< " (" << accuracy / test_data.size() << ")" << std::endl;
}

int main()
{
	// perform_spam_tests();
	perform_custom_tests();
	system("pause");

	return 0;
}