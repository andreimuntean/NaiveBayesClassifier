#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class NaiveBayes
{
private:
	std::vector<std::string> labels;

	// The prior probability of every class.
	std::unordered_map<std::string, double> priors;

	// Determines the likelihood of a word belonging to a class.
	// Unknown words are taken into account as well.
	std::unordered_map<std::string, std::unordered_map<std::string, double>> likelihood;

	// Parses a string into a vector of lowercase alphabetic words.
	std::vector<std::string> to_words(std::string data);
public:
	void train(std::vector<std::string> data, std::vector<std::string> labels);
	std::unordered_map<std::string, double> estimate_probabilities(const std::string& data);
	std::string predict(const std::string& data);
};
