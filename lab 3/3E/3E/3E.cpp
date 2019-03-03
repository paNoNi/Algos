#include<fstream>
#include <vector>
#include<string>

using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;

const int Range = 26;

void redixSort(vector<string> &, int , int );
void sort(vector<string> &, int);

int main() {
	ifstream iFile("radixsort.in");
	int N = 0, M = 0, K = 0;
	iFile >> N >> M >> K;
	vector<string> str(N);
	for (int i = 0; i < N; i++) {
		iFile >> str[i];
	}
	ofstream oFile("radixsort.out");
	redixSort(str, M, K);
	for (int i = 0; i < N; i++)
	{
		oFile << str[i] << "\n";
	}
	oFile.close();
	return 0;
}


void redixSort(vector<string> &data , int M, int K) {
	for (int i = 0; i < K; i++)
	{
		sort(data, M-i-1);
	}
}

void sort(vector<string> &data,int value) {
	vector<vector<string>> temp(Range);
	vector<int> checkTemp;
	for (size_t i = 0; i < data.size(); i++)
	{
		temp[data[i][value] - 'a'].push_back(data[i]);
	}
	for (int i = 0; i < Range; i++)
	{
		if (!temp[i].empty()) {
			checkTemp.push_back(i);
		}
	}
	int k = 0, Row = 0;
	int Columns = checkTemp[k];
	for (int i = 0; i < data.size(); i++)
	{
		if (Row < temp[Columns].size())
		{
			data[i] = temp[Columns][Row];
			Row++;
		}
		else
		{
			Columns = checkTemp[++k];
			data[i] = temp[Columns][0];
			Row = 1;
		}
	}
}