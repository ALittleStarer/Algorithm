#include"Sort.h"
#include"heap.h"
#include<time.h>

vector<int> RandomVector() {
	vector<int> nums(rand()%1000);
	for (int i = 0; i < nums.size(); i++) {
		nums[i] = rand() % 100000;
	}
	return nums;
}

bool isOrdered(vector<int>& nums, bool greater = true) {
	for (int i = 1; i < nums.size(); i++) {
		if ((nums[i] > nums[i - 1]) != greater && nums[i] != nums[i - 1]) {
			return false;
		}
	}
	return true;
}
int sortTest() {
	cout << "***********Start Test**********" << endl;
	cout << "-------------------------------" << endl;
	double right = 0;
	for (int i = 0; i < 20; i++) {
		cout << "Test" << i+1 << " : ";
		vector<int> nums = RandomVector();
		HEAP<int> heapS;
		vector<int> num = heapS.Sort(nums);
		if (isOrdered(num)) {
			cout << "True" << endl;
			right++;
		}
		else {
			cout << "False" << endl;
		}
	}
	cout << "-------------------------------" << endl;
	cout << "Score is :" << 100.0 * right / 20.0;
	return 0;
}