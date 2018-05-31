#pragma once
#include <vector>
#include "Layer.h"
#include <cmath>
#include"Connection.h" 
#include"json.hpp"
using namespace std;
class Layer;
const static string TANGENS = "tangens";
const static string LINIOWA = "liniowa";
const static string SIGMOIDA = "sigmoida";

class Neuron
{
public:
	Neuron(unsigned int  ,int);
	

	double error;
	bool dropout = false;

	
	double sumDer( Layer&,string);
	
	double derivativeActivationFunction(double,string);

	 int index;
	double output;
	unsigned int noutputs;
	vector<Connection>weights;
	~Neuron();
	static double activationFunction(double, string,double theta=0.0);
	
	 void forward(const Layer& l,string);
};

