#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector> 
using namespace std;

class MNIST
{
public:
	MNIST();
	~MNIST();
	bool ReadInputFile(string);
	bool ReadLabelFile(string);
	vector<double> GetImage();
	vector<double> GetLabel();
	int GetNumOfImages();
	void PrintStats();
	void ResetMNIST();

private:
	vector<double> ConvertVector(double);
	int FindBinaryValue(int);

	int data_magic_number;
	int label_magic_number;
	int num_of_images;
	int num_of_labels;
	int Number_of_Rows;
	int Number_of_Columns;
	int lastImgIndex;
	int lastlblIndex;
	vector<double> images;
	vector<double> labels;
};

