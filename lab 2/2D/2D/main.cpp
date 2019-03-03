#include <iostream>
#include <vector>
#include <fstream>
#include <utility>



void antiQSort(std::vector<int> &data) {
	for (int i = 0; i < data.size(); i++) {
		data[i] = i + 1;
	}

	int value = 0;
	for (int i = 0; i < data.size() - 1; i++) {
		if (!(i % 2) && i > 0) {
			value++;
		}
		std::swap(data[i - value], data[i + 1]);
	}
}

int main() {
	std::ifstream fin("antiqs.in");
	int length;
	fin >> length;
	fin.close();

	std::vector<int> data(length);
	antiQSort(data);

	std::ofstream fout("antiqs.out");
	for (auto value : data) {
		fout << value << ' ';
	}
	fout.close();
	return 0;
}