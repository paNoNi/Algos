#include<iomanip>
#include<fstream>
#include <iostream>
#include <cmath>
#define del 100000000

using std::ifstream;
using std::ofstream;
using std::cout;

double BinarySearch(double, double, double, int);

int main() {
	ifstream iFIle("garland.in");
	double  A = 0;
	int N = 0;
	iFIle >> N >> A;
	iFIle.close();
	ofstream oFile("garland.out");
	oFile << std::fixed << std::setprecision(2) << BinarySearch(A, 0, A, N);
	oFile.close();
	return 0;
}



double BinarySearch(double point_A, double left, double right, int N) {
	int i = 2;
	int flag = 0;
	double firstPoint = point_A, secondPoint = (right + left) / 2, thirdPoint;
	while (i < N)
	{
		thirdPoint = 2 * secondPoint - firstPoint + 2;
		firstPoint = secondPoint;
		secondPoint = thirdPoint;
		i++;
		if (!(trunc(thirdPoint*del) / del)) { flag++; }
		if (thirdPoint < 0 || flag > 1) { return BinarySearch(point_A, (left + right) / 2, right, N); }
		if ((secondPoint > firstPoint  && !flag) || (i == N && !flag  )) { return BinarySearch(point_A, left, (left + right) / 2, N); }
	}
	return thirdPoint;
}
