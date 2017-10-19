#pragma once
#include<vector>
#include"Neuron.h"

using namespace std;
class Neuron;
class Layer
{
public:
	Layer();
	vector <Neuron> neurons;
	~Layer();
};

