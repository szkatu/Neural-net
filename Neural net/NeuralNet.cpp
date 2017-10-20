#include "NeuralNet.h"
#include"Neuron.h"
using namespace std;


NeuralNet::NeuralNet(const vector<unsigned int> &topology)
{

	unsigned int nlayers = topology.size();	
	for (int i = 0; i < nlayers-1; i++)
	{
		unsigned int nouputs = topology[i + 1];
		layers.push_back(Layer());
		
			for (int j = 0; j <= topology[i]; j++)
			{
				layers.back().neurons.push_back(Neuron(nouputs,j));
			}
			//bias neuron
			
			layers.back().neurons.back().output = 1.0;

	}
	//last layer
	layers.push_back(Layer());
	for (int j = 0; j < topology.back(); j++)
	{
		layers.back().neurons.push_back(Neuron(0, j));
	}

	
	 
}

void NeuralNet::feedForward(const vector<double>& input)
{
	for (int i=0;i<layers[0].neurons.size() ;i++)
	{
		layers[0].neurons[i].output = input[i];
	}

	for (int i = 1; i<layers.size(); i++)
	{
		 const Layer& previousLayer = layers[i - 1];
		for (int j = 0; j<layers[i].neurons.size(); j++)
		{
			
			layers[i].neurons[j].forward(previousLayer);
		}
	}
}


void NeuralNet::backProp(const vector<double>& target,double eta, double alfa)
{
	Layer& output = layers.back();
	error = 0.0;
	for (unsigned int  i = 0; i < output.neurons.size(); i++)
	{
		double delta = target[i] - output.neurons[i].output;
		error = delta;
	}
	updateweights(alfa, error);
}

void NeuralNet::getResults( vector<double>& result) 
{

	result.clear();
	for (int n = 0; n < layers.back().neurons.size(); n++)
	{
		result.push_back(layers.back().neurons[n].output);
	}

}



void NeuralNet::updateweights(double alfa, double error)
{
	for (int i = 0; i <  layers[layers.size() - 2].neurons.size(); i++)
	{
		Layer& prev = layers[layers.size() - 2];
		Neuron& n = prev.neurons[i];
		
		for (int j = 0; j < n.weights.size(); j++) {
			double o = n.weights[j].weight;

			double newweight = o + alfa*error*n.output;

			n.weights[j].deltaweight = newweight - o;
			n.weights[j].weight = newweight;
		}


	}

}

NeuralNet::~NeuralNet()
{
}
