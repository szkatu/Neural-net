#include<vector>
#include"Neuron.h"
#include <iostream>
#include<string>
#include <sstream>
#include <fstream>
#include"NeuralNet.h"

using namespace std;


int main()
{
	double eta = 0.15;
	double alfa = 0.5;
	int numberOFIterations = 200;
	fstream plik;
	plik.open("C:\\Users\\szkatu\\Desktop\\dane.txt");
	string line;
	vector<string> linie;
	while (getline(plik, line))
	{
		linie.push_back(line);
	}
	

	vector <unsigned int> topology;
		topology.push_back(2);
		topology.push_back(1);
	NeuralNet n(topology);
	
	for (int i = 0; i < numberOFIterations;i++)
	{


		for (string line:linie) 
		{
			vector<double> input;
			vector<double> result;
			vector <double> target;


			stringstream ss(line);
			double num;			

			while (ss >> num)
			{
				
					input.push_back(num);
					
			}
			target.push_back(input.back());
			input.pop_back();
			input.push_back(1.0);

			n.feedForward(input);

			n.backProp(target, eta, alfa);
			n.getResults(result);
			/*for (double j : result) 
			{
				double error = target[0] - j;
				if (error == 0.0)
				{
					cout << "true" << "\n";
				}
				else
					cout << "false" << "\n";
			}*/


		}
		/*cout << i;*/
		
	}
	double f,s;
	vector<double> input;
	vector<double>result;
	cin >> f;
		cin >> s;
		input.push_back(f);
		input.push_back(s);
		input.push_back(1.0);
		n.feedForward(input);
		n.getResults(result);
		for (double r : result)
		{
			cout << r<<"\n";
		}

	system("pause");
	return 0;
}