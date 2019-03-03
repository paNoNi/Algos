#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::ifstream;
using std::ofstream;



pair<int,int> BinarySearch(vector<int> &data, int left, int right, int key)
{
	pair<int, int> temp(-1,-1);
	int mid = 0;
	while (left <= right)
	{
		mid = (left + right) / 2;

		if (key < data[mid])
			right = mid - 1;
		else if (key > data[mid])
			left = mid + 1;
		else if(key == data[mid]){
			temp.first = mid + 1;
		    right = mid - 1;
		}	
	}
	if (temp.first == -1 || left == right) {
		return temp;
	}
	else
	{
		left = mid;
		right = data.size() - 1;
		while (left <= right)	
		{
			mid = (left + right) / 2;

			if (key < data[mid])
				right = mid - 1;
			else if (key > data[mid])
				left = mid + 1;
			else if (key == data[mid]) {
				temp.second = mid + 1;
				left = mid + 1;
			}
		}
	}
	return temp;
}



int main() {
	ifstream inFile("binsearch.in");
	int N = 0, M = 0;
	pair<int, int> Value;
	inFile >> N;
	vector<int> Data(N);
	for (int i = 0; i < N; i++)
	{
		inFile >> Data[i];
	}
	inFile >> M;
	vector<int> requests(M);
	for (int i = 0; i < M; i++)
	{
		inFile >> requests[i];
	}
	inFile.close();
	ofstream outFile("binsearch.out");
	for (int i = 0; i < M; i++)
	{
		Value = BinarySearch(Data,0,Data.size()-1, requests[i]);
		outFile << Value.first << ' ' << Value.second << "\n";
	}
	outFile.close();
	return 0;
}