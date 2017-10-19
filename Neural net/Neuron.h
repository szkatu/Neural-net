#pragma once
#include <vector>
#include "Layer.h"
#include <cmath>
#include"Connection.h" 
using namespace std;
class Layer;
class Neuron
{
public:
	Neuron(unsigned int  ,int);
	
	void calcOutputGradient(double target);
	void calcGradient(const Layer& );
	
	double sumDer(const Layer& );
	double gradient;

	 int index;
	double output;
	unsigned int noutputs;
	vector<Connection>weights;
	~Neuron();
	static double activationFunction(double);
	
	 void forward(const Layer& l);
};

