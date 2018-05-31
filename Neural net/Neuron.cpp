#include "Neuron.h"
#include "Layer.h"
#include<math.h>
#include<vector>



Neuron::Neuron(unsigned int  noutputs, int i)
{
	index = i;

	for (int i = 0; i < noutputs; i++)
	{
		weights.push_back(Connection());
	}
	error = 0.0;
}



double Neuron::sumDer(  Layer& next,string type)
{
	double sum = 0.0;
	
	
	
		for (int j = 0; j < next.neurons.size(); j++)//add error from next layer
		{
			if (!next.neurons[j].dropout)
				sum += weights[j].weight*next.neurons[j].derivativeActivationFunction(output, type)*next.neurons[j].error;

		}
		error = sum;
	

	
	
	return sum;

}

double Neuron::derivativeActivationFunction(double value, string type)
{

	if (type == SIGMOIDA)
		return  value* (1 - value);
	else if (type == TANGENS)
		return 1-pow(value,2);
	else if (type == LINIOWA)
		return 1;
	
}

 void Neuron::forward(const Layer& l,string type)
{
	 double sum = 0.0;
	 for (int i = 0; i<l.neurons.size() ; i++)
	 {
		 if(!l.neurons[i].dropout)
		 sum += l.neurons[i].weights[index].weight*l.neurons[i].output;
	 }
	 output = activationFunction(sum,type);

}
 Neuron::~Neuron()
 {
 }
 double  Neuron::activationFunction(double s, string type, double theta)
	 
 {
	 if (type == SIGMOIDA)
		 return 1 / (1 + exp(-s));
	 else if (type == TANGENS)
		 return tanh(s);
	 else if (type == LINIOWA)
		 return s;

 }


