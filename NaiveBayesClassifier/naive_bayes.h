#pragma once

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

class NaiveBayes
{
private:
	vector<string> labels;

	// The prior probability of every class.
	vector<int> priors;

	// Stores every word encountered in the training set.
	vector<string> vocabulary;

	// Determines the likelihood of a word belonging to a class.
	// Unknown words are represented by "?".
	map<string, map<string, double>> likelihood;

	// Parses a string into a vector of words.
	vector<string> to_words(string data);
public:
	NaiveBayes();
	void train(vector<string> data, vector<string> labels);
	string predict(string data);
	virtual ~NaiveBayes();
};
