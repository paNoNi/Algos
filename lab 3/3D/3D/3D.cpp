#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using std::ifstream;
using std::ofstream;
using std::vector;
using std::swap;

void heapSort(vector<int> &);

int main() {
	ifstream iFile("sort.in");
	int length = 0;
	iFile >> length;
	vector<int> arr(length);
	for (int i = 0; i < length; i++)
	{
		iFile >> arr[i];
	}
	iFile.close();
	heapSort(arr);
	ofstream oFile("sort.out");
	for (int i = 0; i < length; i++)
	{
		oFile << arr[i] <<' ';
	}
	oFile.close();
	return 0;
}

 
void heapify(vector<int> &data,int length, int i)
{
	int largest = i;  
	int l = 2 * i + 1; 
	int r = 2 * i + 2;  
 
	if (l < length && data[l] > data[largest])
		largest = l;
 
	if (r < length && data[r] > data[largest])
		largest = r;

	if (largest != i)
	{
		swap(data[i], data[largest]);
 
		heapify(data, length, largest);
	}
}

void heapSort(vector<int> &data)
{

	for (int i = data.size() / 2 - 1; i >= 0; i--)
		heapify(data,data.size(), i );


	for (int i = data.size() - 1; i >= 0; i--)
	{
 
		swap(data[0], data[i]);

		heapify(data, i, 0);
	}
}
		
			