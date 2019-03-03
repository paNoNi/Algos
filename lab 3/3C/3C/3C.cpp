#include<fstream>
#include<vector>

using std::ifstream;
using std::vector;
using std::ofstream;

int check(vector<int> &);

int main() {
	ifstream iFile("isheap.in");
	int N;
	bool Val;
	iFile >> N;
	vector<int> Data(N+1);
	for (int i = 1; i <= N; i++)
	{
		iFile >> Data[i];
	}
	iFile.close();
	Val = check(Data);
	ofstream oFile("isheap.out");
	if (Val) { oFile << "YES"; }
	else
	{
		oFile << "NO";
	}
	oFile.close();
	return 0;
}

int check(vector<int> &data) {
	for (int i = 1; i <= data.size(); i++)
	{
		if (2 * i <= (data.size()-1))
			if (data[i] > data[2 * i])return 0;
		if ((2 * i+1)<=(data.size()-1))
			if (data[i] > data[2 * i]) return 0;
	}
	return 1;
}