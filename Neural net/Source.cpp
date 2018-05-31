#include<vector>
#include"Neuron.h"
#include <iostream>
#include"Util.h"
#include<array>
#include<algorithm>
#include<string>
#include "C:\Users\szkatu\Desktop\lodepng-master\lodepng.h"
#include <sstream>
#include <fstream>
#include<filesystem>


#include"NeuralNet.h"
#include "Source.h"

using namespace std;
using fs = std::experimental::filesystem::recursive_directory_iterator;


bool hasEnding(std::string const &fullString, std::string const &ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}

void decodeOneStep(const char* filename, vector<unsigned char>& image)
{

	unsigned width = 28;
	unsigned height = 28;


	unsigned error = lodepng::decode(image, width, height, filename);


	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;


}
vector <array<array<int, 28>, 28>>wczytajobrazki(vector<string >paths)
{
	vector <array<array<int, 28>, 28>> xd;

	for (string path : paths) {

		std::array<std::array<int, 28>, 28> tab;

		vector<unsigned char> image;



		decodeOneStep(path.c_str(), image);
		Util ut = Util();

		if (image.size() > 0) {
			ut.decode(image, 28, 28, tab);
			xd.push_back(tab);
		}
		else cout << path << endl;

	}
	return xd;
}
void learn(NeuralNet& n, int numberOFIterations, vector<vector<double>>& inputs, vector<vector<double>>target, double alfa, double eta, string type = SIGMOIDA)
{
	int i = 1;
	double meanError = 200.0;
	fstream f;
	f.open("C:\\Users\\szkatu\\Desktop\\wyniki2.txt", fstream::app | fstream::in | fstream::out);
	fstream k;
	k.open("C:\\Users\\szkatu\\Desktop\\wyniki.txt", fstream::app | fstream::in | fstream::out);


	while ( i<8000 && meanError>0.05) //
	{
		meanError = 0.0;

		vector<double> result;
		for (int j = 0; j<inputs.size(); j++)
		{
			vector<double> input=inputs[j];
			

			n.feedForward(input, type);

			n.backProp(target[j], eta, alfa, type);

			meanError+= n.getResults(result, target[j]);

			
		}
		meanError /= inputs.size();
		f << i << " " << meanError << endl;

		i++;
		//n.printWeights();


	}
	k << "Epoki: " << i << "\t" << "error: " << meanError << "\t";
	k.close();
	f << endl;
	f.close();

}

vector<double> predict(vector<double> &inputs, NeuralNet n, string type = SIGMOIDA)
{
	
	vector<double> result;

	
	n.feedForward(inputs, type);
	n.getResults(result, {});
	return result;


}
vector<vector<double>> getInput(vector<array<array<int, 28>, 28>> results)
{
	//vector<array<array<int, 28>, 28>> results;
	vector<vector<double>> result;
	for (int j = 0; j < results.size(); j++)
	{
		vector<double> tym;
		for (int k = 0; k < 28 * 28; k++)
		{
			tym.push_back((double)results[j][k / 28][k % 28]);


		}
		result.push_back(tym);

	}
	return result;
}



int main()
{ //////////////////////////////////////////////////////////////////////////////
  //setting parameters
	vector<double> eta = { 0.0,0.1,0.2,0.3,0.4,0.5, 0.6, 0.8, };
	double alfa = 0.02;

	vector<double> alfaSet = { 0.01,0.02, 0.05 , 0.1 , 0.15 , 0.2, 0.3, 0.5 };
	vector<unsigned int> nNeurons = { 20,40,60,80,100,120,140,160,180,200 };

	////////////////////////////////////////////////////////////////////////////////
	//getting data

	vector<string>paths;
	vector<string>pathsTest;


	std::string path = "E:\\sn";
	std::string pathTest = "E:\\snTest";
	vector<vector<double>> result;
	vector<vector<double>> resultTest;
	for (auto& p : fs::recursive_directory_iterator(path))
	{
		string pathToFile = p.path().generic_string();
		if (hasEnding(pathToFile, ".png"))
		{
			paths.push_back(pathToFile);
			result.push_back({0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0});
			result.back()[pathToFile[6]-48] = 1.0;



		}
	}

	vector<vector<double>> xd = getInput(wczytajobrazki(paths));

	




	///////////////////////////////////////////////////////////////////////////////////////////////////////////




	vector <unsigned int> topology = { 28 * 28,120,10 };
	NeuralNet n(topology);
	learn(n, 2000, xd, result, 0.001, 3);

	// check prediction rate

	for (auto& p : fs::recursive_directory_iterator(pathTest))
	{
		string pathToFile = p.path().generic_string();
		if (hasEnding(pathToFile, ".png"))
		{
			pathsTest.push_back(pathToFile);
			resultTest.push_back({ 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 });
			resultTest.back()[pathToFile[10] - 48] = 1.0;



		}
	}
	vector<vector<double>> wyniki = getInput(wczytajobrazki(paths));
	int j = 0;
	for (auto i=0;i<wyniki.size();i++)
	{
		vector<double> calculatedOutput=predict(wyniki[i], n);
		for(int h=0;h<calculatedOutput.size();h++)
		{
			if (calculatedOutput[h] > 0.7)
				calculatedOutput[h] = 1;
			else
				calculatedOutput[h] = 0;
		}
		if (calculatedOutput== resultTest[i])
		{
			j++;

		}
	}

	cout << (double)j / (double)wyniki.size();






///////////////////////////////////////////////////////////////////////////////////////////////////////

system("pause");
return 0;
}