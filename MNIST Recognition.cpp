// MNIST Recognition.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MNIST.h"
#include "NeuralNetwork.h"

void trainNetwork(MNIST);

using namespace std;

void printImageVector(vector<double> vec) {
	int counter = 0;
	for (int i = 0; i < 28; i++) {
		for (int j = 0; j < 28; j++) {
			if (vec[counter] > 0)
				cout << "$";
			else
				cout << " ";
			counter++;
		}
		cout << endl;
	}
}

void printLabelVector(vector<double> vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i];
	}
	cout << endl;
}

int main()
{
	MNIST dataFile;
	NeuralNetwork tanhNN;

	string strTrainingInFile = "train-images.idx3-ubyte";
	string strTrainingLblFile = "train-labels.idx1-ubyte";
	string strTestingInFile = "t10k-images.idx3-ubyte";
	string strTestinglblFile = "t10k-labels.idx1-ubyte";
	string strOutputFile = "TestResults.txt";

	int epochCount = 1;
	int batchSize = 1;

	//Start training the MNIST File

	if (dataFile.ReadInputFile(strTrainingInFile)) {
		if (dataFile.ReadLabelFile(strTrainingLblFile)) {
			dataFile.PrintStats();
			for (int i = 0; i < epochCount; i++) {
				for (int j = 0; j < dataFile.GetNumOfImages(); j++) {
					tanhNN.InsertInputs(dataFile.GetImage());
					tanhNN.InsertLabel(dataFile.GetLabel());
					tanhNN.TrainImage();
					if (j % 10 == 0) {
						cout << "Step: " << j << " Epoch: " << i+1 << endl;
						tanhNN.DisplayError();
						tanhNN.DisplayLabels();
					}
				}
			}
		}
		else
			cout << "Error reading the training label file." << endl;
	}
	else
		cout << "Error reading the training input file." << endl;

	//result values of the dataFile
	dataFile.ResetMNIST();

	cout << "TESTING RESULTS:" << endl;
	cout << "***************************************" << endl;

	//Test the results
	if (dataFile.ReadInputFile(strTestingInFile)) {
		if (dataFile.ReadLabelFile(strTestinglblFile)) {
			dataFile.PrintStats();
			for (int i = 0; i < dataFile.GetNumOfImages(); i++) {
				tanhNN.InsertInputs(dataFile.GetImage());
				tanhNN.InsertLabel(dataFile.GetLabel());
				tanhNN.TestImage();
				tanhNN.WriteImageResult(strOutputFile);
			}
			tanhNN.WriteTestResults(strOutputFile);
		}
		else
			cout << "Error reading the testing label file." << endl;
	}
	else
		cout << "Error reading the testing input file." << endl;

}

