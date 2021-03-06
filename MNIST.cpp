#include "stdafx.h"
#include "MNIST.h"


MNIST::MNIST()
{
	lastlblIndex = 0;
	lastImgIndex = 0;
}


MNIST::~MNIST()
{
}

bool MNIST :: ReadInputFile(string strFile) {
	ifstream inputFile(strFile, ios::binary);
	unsigned char tempBinary = 0;
	if (inputFile) {
		//binary file is given in MSB format, so we need to reverse and find the integers
		inputFile.read((char*)&data_magic_number, sizeof(data_magic_number));
		data_magic_number = FindBinaryValue(data_magic_number);
		inputFile.read((char*)&num_of_images, sizeof(num_of_images));
		num_of_images = FindBinaryValue(num_of_images);
		inputFile.read((char*)&Number_of_Rows, sizeof(Number_of_Rows));
		Number_of_Rows = FindBinaryValue(Number_of_Rows);
		inputFile.read((char*)&Number_of_Columns, sizeof(Number_of_Columns));
		Number_of_Columns = FindBinaryValue(Number_of_Columns);

		images.resize(num_of_images * 784);

		for (int i = 0; i<num_of_images*784; i++) {
			inputFile.read((char*)&tempBinary, sizeof(tempBinary));
			images[i] = (double)tempBinary;
		}
		return true;
	}
	else
		return false;
	inputFile.close();
}

bool MNIST::ReadLabelFile(string strFile) {
	ifstream labelFile(strFile, ios::binary);
	unsigned char tempBinary = 0;

	if (labelFile) {
		labelFile.read((char*)&label_magic_number, sizeof(label_magic_number));
		label_magic_number = FindBinaryValue(label_magic_number);

		if (label_magic_number == 2049) {
			labelFile.read((char*)&num_of_labels, sizeof(num_of_labels));
			num_of_labels = FindBinaryValue(num_of_labels);

			labels.resize(num_of_labels);

			for (int i = 0; i < num_of_labels; i++) {
				labelFile.read((char*)&tempBinary, 1);
				labels[i] = (double)tempBinary;
			}
			return true;
		}
		else
			return false;
		labelFile.close();
	}
	else
		return false;
}

vector<double> MNIST::GetImage() {
	vector<double> vctRet(784);
	int nextImgIndex = lastImgIndex + 784;
	if (nextImgIndex == 47040000)
		nextImgIndex = 0;
	int counter = 0;
	for (int i = lastImgIndex; i < nextImgIndex; i++) {
		vctRet[counter] = images[i];
		counter++;
	}
	lastImgIndex = nextImgIndex;
	return vctRet;
}

vector<double> MNIST::GetLabel() {
	vector<double> vctRet(10);
	int nextLblIndex = lastlblIndex+1;
	if (nextLblIndex == num_of_labels)
		nextLblIndex = 0;
	double value = labels[lastlblIndex];
	lastlblIndex = nextLblIndex;
	vctRet = ConvertVector(value);
	return vctRet;
}

int MNIST::GetNumOfImages() {
	return num_of_images;
}

vector<double> MNIST::ConvertVector(double value) {
	vector<double> vctRet(10);
	vctRet[value] = 1.0;
	return vctRet;
}
void MNIST::PrintStats() {
	cout << "Image Count: " << num_of_images << "." << endl;
	cout << "Row Count: " << Number_of_Rows << "." << endl;
	cout << "Column Count: " << Number_of_Columns << "." << endl;
	cout << "Label Magic #: " << label_magic_number << "." << endl;
	cout << "Input Magic $: " << data_magic_number << "." << endl;
}

int MNIST::FindBinaryValue(int input) {
	unsigned char ch1, ch2, ch3, ch4;
	ch1 = input & 255;
	ch2 = (input >> 8) & 255;
	ch3 = (input >> 16) & 255;
	ch4 = (input >> 24) & 255;
	return (((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4);
}

void MNIST::ResetMNIST() {
	fill(images.begin(), images.end(), 0);
	fill(labels.begin(), labels.end(), 0);
}
