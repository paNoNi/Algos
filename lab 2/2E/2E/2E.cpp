#include <iostream>
#include <fstream>
#include <vector>


int findOrderStatistic(std::vector<int> arr, int k) {
	k--;
	int left_idx = 0;
	int right_idx = arr.size() - 1;

	while (left_idx < right_idx) {
		int left_itr = left_idx, right_itr = right_idx;

		if (arr[left_itr] > arr[right_itr])
			std::swap(arr[left_itr], arr[right_itr]);
		if (arr[right_itr] < arr[k])
			std::swap(arr[k], arr[right_itr]);
		if (arr[left_itr] > arr[k])
			std::swap(arr[left_itr], arr[k]);

		int pivot = arr[k];

		while ((left_itr < k) && (k < right_itr)) {
			do
				left_itr++;
			while (arr[left_itr] < pivot);

			do
				right_itr--;
			while (pivot < arr[right_itr]);

			std::swap(arr[left_itr], arr[right_itr]);
		}
		left_itr++;
		right_itr--;

		if (right_itr < k) {
			while (arr[left_itr] < pivot)
				left_itr++;
			left_idx = left_itr;
		}

		if (k < left_itr) {
			while (pivot < arr[right_itr])
				right_itr--;
			right_idx = right_itr;
		}
	}
	return arr[k];
}

int main() {
	int length, k;
	int A, B, C;
	std::vector<int> arr(2);

	std::ifstream fin("kth.in");
	fin >> length >> k;
	fin >> A >> B >> C >> arr[0] >> arr[1];
	fin.close();

	for (int i = 2; i < length; i++)
		arr.push_back(arr[i - 2] * A + arr[i - 1] * B + C);

	std::ofstream fout("kth.out");
	fout << findOrderStatistic(arr, k);
	fout.close();
	return 0;
}