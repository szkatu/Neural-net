#include "Neuron.h"
#include "Layer.h"
#include<vector>



Neuron::Neuron(unsigned int  noutputs, int i)
{
	index = i;

	for (int i = 0; i < noutputs; i++)
	{
		weights.push_back(Connection());
	}
}
void Neuron::calcOutputGradient(double target)
{
	double delta = target - output;
	gradient = delta*activationFunction(output); 

}

void Neuron::calcGradient(const Layer& l)
{
	
	double delta = sumDer(l);
	gradient = delta*activationFunction(delta);
}

double Neuron::sumDer(const Layer& l)
{
	double sum = 0.0;
	for (int i=0;i<l.neurons.size();i++)
	{
		sum += weights[i].weight*l.neurons[i].gradient;

	}
	return sum;

}

 void Neuron::forward(const Layer& l)
{
	 double sum = 0.0;
	 for (int i = 0; i<l.neurons.size() ; i++)
	 {

		 sum += l.neurons[i].weights[index].weight*l.neurons[i].output;
	 }
	 output = Neuron::activationFunction(sum);

}
 Neuron::~Neuron()
 {
 }
 double  Neuron::activationFunction(double s)
 {
	return s >0.5 ? 1:0;

 }


