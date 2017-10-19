#pragma once

#include "Layer.h"

class NeuralNet
{
public:
	NeuralNet(const vector<unsigned int> &topology);
	void feedForward(const vector<double> &input);
	void backProp(const vector<double> &target,double eta,double alfa);
	void getResults( vector<double> &result) ;
	void updateweights(double alfa, double error);
	~NeuralNet();
private:
	vector<Layer> layers;
	double error;
};

