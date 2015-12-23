#include <iostream>
#include "data_reader.h"
#include "naive_bayes.h"

void perform_lyrics_tests()
{
	std::vector<std::string> data;
	std::vector<std::string> labels;

	get_data("data", data, labels);

	NaiveBayes naive_bayes;
	naive_bayes.train(data, labels);

	// Tests the classifier using data from the training set:
	std::cout << "Should be Coldplay: " << naive_bayes.predict("you don't know how lovely you are") << std::endl;
	std::cout << "Should be Radiohead: " << naive_bayes.predict("let down and hanging around") << std::endl;
	std::cout << "Should be Taylor Swift: " << naive_bayes.predict("shake it off, shake it off") << std::endl;

	// Tests the classifier using new data:
	std::cout << "Should be Coldplay: " << naive_bayes.predict("you came along and you cut me loose") << std::endl;
	std::cout << "Should be Radiohead: " << naive_bayes.predict("we're here to keep your prices down") << std::endl;
	std::cout << "Should be Taylor Swift: " << naive_bayes.predict("I'd give everything / to have you here today") << std::endl;
}

void perform_spam_tests()
{
	std::vector<std::string> training_data, training_labels;
	std::vector<std::string> test_data, test_labels;

	get_data("emails/training", training_data, training_labels);
	get_data("emails/test", test_data, test_labels);

	NaiveBayes naive_bayes;
	naive_bayes.train(training_data, training_labels);

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
	perform_spam_tests();
	perform_lyrics_tests();
	system("pause");

	return 0;
}