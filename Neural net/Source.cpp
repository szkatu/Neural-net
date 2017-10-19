#include<vector>
#include"Neuron.h"
#include <iostream>
#include"NeuralNet.h"

using namespace std;


int main()
{
	double eta = 0.15;
	double alfa = 0.5;
	int numberOFIterations = 200;
	

	vector <unsigned int> topology;
	topology.push_back(2);
		topology.push_back(1);
	NeuralNet n(topology);
	
	while (true) {


		vector<double> input = { 0.0,1.0,1.0};
		vector<double> result;
		vector <double> target = { 0.0 };
		n.feedForward(input);
		n.getResults(result);
		n.backProp(target, eta, alfa);
		for (auto j = result.begin(); j != result.end(); ++j)
			cout << *j<<"\n";
		
	}
	
	

	return 0;
}