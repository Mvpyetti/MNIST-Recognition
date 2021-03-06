#pragma once
#include <vector>
#include <math.h>
#include <random>
#include <fstream>
#include <iostream>

using namespace std; 

enum func{
	TANH,
	SIGM,
	DBLSIG,
	RELU
};

class NeuralNetwork
{
public:
	NeuralNetwork(int= 20, double= .006, double=1, func = TANH);
	void ChangeActivationFunc(func);
	void ChangeBatchSize(double);
	void ChangeNeuronCount(int);
	void ChangeEta(double);
	void DisplayError();
	void DisplayLabels();
	void InsertInputs(vector<double>);
	void InsertLabel(vector<double>);
	void TrainImage();
	void TestImage();
	void WriteTestResults(string);
	void WriteImageResult(string);
	~NeuralNetwork();
private:
	void BackProp();
	void CalculateOutput();
	void CalculateDeltas();
	void CalculateLabels();
	void CalculateTestResults();
	void InitializeWeights();
	void ResizeNeurons();
	void ResetOuputs();

	double ActivationFunction(double);
	double Derivative(double);

	//STANDARD VALUES
	vector<double> x;
	vector<vector<double>> w;
	vector<double> b;
	vector<double> s;
	vector<double> t;
	vector<double> y;
	vector<double> derivy;
	vector<vector<double>> u;
	vector<double> c;
	vector<double> r;
	vector<double> z;
	vector<double> derivz;

	//DELTA VALUES
	vector<vector<double>> deltaw;
	vector<double> deltab;
	vector<vector<double>> deltau;
	vector<double> deltac;


	//HYPER PARAMETERS
	func actFunc;
	int neuronCount;
	double batchSize;
	double eta;

	//Testing Variables
	int expectedLabel;
	int correctLabel;
	double totalImages;
	double correctImages;
	double testError;
	double error;
};

