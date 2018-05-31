#pragma once

#include "Layer.h"
#include"json.hpp"
using json = nlohmann::json;

class NeuralNet
{
public:
	NeuralNet(const vector<unsigned int> &topology);
	void feedForward(const vector<double> &input,string);
	void backProp(const vector<double> &target,double eta,double alfa,string);
	double getResults( vector<double> &result, const vector<double>& target) ;
	void getClass(vector<double>& result, const vector<double>& target);
	void updateweights(double alfa,double eta=0.0);
	void printWeights();
	~NeuralNet();
	json toJson();
private:
	vector<Layer> layers;
	double error;
};

