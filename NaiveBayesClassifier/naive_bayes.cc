#include <algorithm>
#include <cctype>
#include <iterator>
#include <set>
#include "naive_bayes.h"

std::vector<std::string> NaiveBayes::to_words(std::string data)
{
	std::vector<std::string> words;

	// Turns every upper case letter into lower case.
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	
	// Turns every tab into a space.
	std::replace(data.begin(), data.end(), '\t', ' ');

	// Turns every newline into a space.
	std::replace(data.begin(), data.end(), '\n', ' ');

	// Removes every character that is not a space, letter or digit.
	data.erase(std::remove_if(data.begin(), data.end(), [](char character) {
		return character != ' ' && !isalnum(character);
	}), data.end());

	const auto delimiter = " ";
	size_t start = 0;
	auto end = data.find(delimiter);

	while (end != std::string::npos)
	{
		words.push_back(data.substr(start, end - start));
		start = data.find_first_not_of(delimiter, end);
		end = data.find(delimiter, start);
	}

	return words;
}

void NaiveBayes::train(std::vector<std::string> data, std::vector<std::string> labels)
{
	// Stores the possible labels.
	std::unique_copy(labels.begin(), labels.end(), std::back_inserter(this->labels));

	// Stores the number of words for every label.
	std::unordered_map<std::string, size_t> word_count;

	// Stores every unique word from the training set.
	std::set<std::string> vocabulary;

	// Calculates the frequency of words for every label.
	for (auto index = 0; index < data.size(); ++index)
	{
		const auto& label = labels[index];
		const auto& words = to_words(data[index]);

		word_count[label] += words.size();

		for (const auto& word : words)
		{
			likelihood[word][label]++;
			vocabulary.insert(word);
		}

		// Counts the frequency of labels.
		priors[label]++;
	}

	// Turns the word frequency counts into probabilities.
	for (const auto& label : this->labels)
	{
		// Due to Laplace smoothing, |vocabulary| is added to the nominator.
		// An additional 1 is added as well to account for unknown values.
		const auto nominator = (double)word_count[label] + vocabulary.size() + 1;

		for (const auto& word : vocabulary)
		{
			likelihood[word][label] = (likelihood[word][label] + 1) / nominator;
		}

		// Determines the likelihood of unknown values.
		likelihood["?"][label] = 1 / nominator;

		// Turns the label frequencies into probabilities.
		priors[label] /= (double)labels.size();
	}
}

std::string NaiveBayes::predict(const std::string& data)
{
	auto probabilities = priors;

	for (const auto& word : to_words(data))
	{
		for (const auto& label : labels)
		{
			// Magnifies the probabilities if they get too close to zero.
			if (probabilities[label] < 1.0e-200)
			{
				for (auto& probability : probabilities)
				{
					probability.second *= 1.0e+100;
				}
			}

			// Determines if this word is known.
			if (likelihood.count(word))
			{
				probabilities[label] *= likelihood[word][label];
			}
			else
			{
				probabilities[label] *= likelihood["?"][label];
			}
		}
	}

	// Gets the label that has the highest probability.
	const auto& prediction = std::max_element(probabilities.begin(), probabilities.end(),
		[](const auto& x, const auto& y) { return x.second < y.second; });

	return prediction->first;
}