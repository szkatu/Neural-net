#include "NeuralNet.h"
#include"Neuron.h"
#include<math.h>
using namespace std;


NeuralNet::NeuralNet(const vector<unsigned int> &topology)
{

	unsigned int nlayers = topology.size();	
	for (int i = 0; i < nlayers-1; i++)
	{
		unsigned int nouputs = topology[i + 1]+1;
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

void NeuralNet::feedForward(const vector<double>& input,string type)
{
	for (int j = 1; j<layers.size()-1; j++)
	{
		for (int i = 0; i < layers[j].neurons.size(); i++)
		{
			layers[j].neurons[i].dropout = false;
		}
	}
	for (int j = 1; j<layers.size()-1; j++)
	{
		for (int i = 0; i < layers[j].neurons.size(); i++)
		{
			double s = rand() / double(RAND_MAX);
			if (s > 0.5)
			{
				layers[j].neurons[i].dropout = true;
			}
		}
	}
	for (int i=0;i<layers[0].neurons.size() ;i++)
	{
		layers[0].neurons[i].output = input[i];
	}

	for (int i = 1; i<layers.size(); i++)
	{
		 const Layer& previousLayer = layers[i - 1];
		for (int j = 0; j<layers[i].neurons.size(); j++)
		{
			
			layers[i].neurons[j].forward(previousLayer,type);
		}
	}
}


void NeuralNet::backProp(const vector<double>& target,double eta, double alfa,string type)
{
	Layer& output = layers.back();
	
	for (unsigned int  i = 0; i < output.neurons.size(); i++)
	{

		output.neurons[i].error = target[i] - output.neurons[i].output;
			
	}


	// back prop for next layers
	for (int i=layers.size()-2;i>0;i--)//for each layer
	{
		for (int j = 0; j < layers[i].neurons.size();j++)//for each neuron in that layer
		{
			if (!layers[i].neurons[j].dropout)
			{
				layers[i].neurons[j].error = layers[i].neurons[j].sumDer(layers[i + 1], type);
			}
			
			
		}

		

	}

			updateweights(alfa,eta);

}

double NeuralNet::getResults( vector<double>& result, const vector<double>& target)
{

	result.clear();
	double sum = 0.0;
	for (int n = 0; n < layers.back().neurons.size(); n++)
	{
		result.push_back(layers.back().neurons[n].output);
		if(target.size()!=0)
		sum += pow(layers.back().neurons[n].output - target[n], 2);
	}
	
	
	
	
	return sum;

}


void NeuralNet::getClass(vector<double>& result, const vector<double>& target)
{
	for (int n = 0; n < layers.back().neurons.size(); n++)
	{
		if(layers.back().neurons[n].output>0.7)
		result.push_back(1);
		else
			result.push_back(0);
		
			
	}

}

void NeuralNet::updateweights(double alfa,double eta)
{

	for (int i = layers.size() - 1;i>0; i--)
	{
		Layer& prev = layers[i - 1];

		
		for (int k=0;k<prev.neurons.size();k++)
		{
			Neuron& n = prev.neurons[k];
			if (!n.dropout)
			{
				for (int j = 0; j < layers[i].neurons.size(); j++)
				{
					double o = n.weights[j].weight;
					//o *= 1 - alfa*eta;

					double newweight = o + alfa*layers[i].neurons[j].error*n.output;//


					n.weights[j].deltaweight = newweight - o;
					n.weights[j].weight = newweight;


				}

			}
		}
	}


}

void NeuralNet::printWeights()
{
	for (int i=0;i<layers.size()-1;i++)
	{
		Layer l = layers[i];
		for (Neuron n:l.neurons)
		{
			for (Connection c:n.weights) 
			{
				cout << c.weight<<" ";
			}
			cout << endl;
			
		}
		cout << endl;
	}
}

NeuralNet::~NeuralNet()
{
}
