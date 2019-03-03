#include <iostream>
#include <fstream>
#include <vector>



long long inversionsCountAlgo(std::vector<int> &data, int left, int mid, int right) {
	std::vector<int> left_part;
	std::vector<int> right_part;

	for (int i = left; i <= right; i++) {
		if (i <= mid)
			left_part.push_back(data[i]);
		else
			right_part.push_back(data[i]);
	}

	int left_itr = 0, right_itr = 0;
	long long inversions_counter = 0;
	for (int i = left; i <= right; i++) {
		if (left_itr >= left_part.size()) {
			data[i] = right_part[right_itr];
			right_itr++;
		}
		else if (right_itr >= right_part.size()) {
			data[i] = left_part[left_itr];
			left_itr++;
		}
		else if (left_part[left_itr] <= right_part[right_itr]) {
			data[i] = left_part[left_itr];
			left_itr++;
		}
		else {
			data[i] = right_part[right_itr];
			right_itr++;
			inversions_counter += left_part.size() - left_itr;
		}
	}
	return inversions_counter;
}


long long inversionsCount(std::vector<int> &data, int left, int right) {
	long long inversions_counter = 0;
	if (left < right) {
		int mid = (left + right) / 2;
		inversions_counter += inversionsCount(data, left, mid);
		inversions_counter += inversionsCount(data, mid + 1, right);
		inversions_counter += inversionsCountAlgo(data, left, mid, right);
	}
	return inversions_counter;
}

long long inversionsCount(std::vector<int> data) {
	return inversionsCount(data, 0, data.size() - 1);
}

int main() {
	std::ifstream fin("inversions.in");
	int number;
	fin >> number;

	std::vector<int> data;
	for (int i = 0; i < number; i++) {
		int new_value;
		fin >> new_value;
		data.push_back(new_value);
	}
	fin.close();

	std::ofstream fout("inversions.out");
	fout << inversionsCount(data);
	fout.close();
	return 0;
}