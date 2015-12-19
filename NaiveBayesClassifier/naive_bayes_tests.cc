#include <armadillo>
#include "data_reader.h"
#include "naive_bayes.h"

using namespace arma;

static void get_training_data(const string path, vector<string>& data, vector<int>& labels)
{
}

int main()
{
	vector<string> data;
	vector<int> labels;

	get_training_data("data", data, labels);
	
	return 0;
}