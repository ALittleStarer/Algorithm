#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class T>
class HEAP
{
private:
	vector<T> values;
	bool greater;
public:
	HEAP(bool isGreater = true) {
		greater = isGreater;
	}
	void put(T val);
	void doAdjustUp();
	void doAdjustDown();
	int getFaIndex(int index);
	int getSonIndex(int index);
	void putArray(vector<T>& input);
	vector<T> Sort(vector<T>& input);
};

template<class T>
void HEAP<T>::put(T val)
{

	values.push_back(val);
	doAdjustUp();
}

template<class T>
void HEAP<T>::putArray(vector<T>& input)
{
	for (int i = 0; i < input.size(); i++) {
		put(input[i]);
	}
}

template<class T>
int HEAP<T>::getFaIndex(int index)
{
	if (index == 0) {
		return 0;
	}
	else {
		return (index - 1) / 2;
	}
}

template<class T>
void HEAP<T>::doAdjustUp()
{
	int index = values.size() - 1;
	while ((values[getFaIndex(index)] > values[index]) == greater) {
		swap(values[getFaIndex(index)], values[index]);
		index = getFaIndex(index);
		if (index == 0) {
			break;
		}
	}
}

template<class T>
int HEAP<T>::getSonIndex(int index)
{
	int nextIndex1 = (index + 1) * 2 - 1;
	int nextIndex2 = (index + 1) * 2;
	if (nextIndex1 >= values.size()) {
		return index;
	}
	else if (nextIndex2 >= values.size()) {
		return nextIndex1;
	}
	else {
		if ((values[nextIndex1] < values[nextIndex2]) == greater) {
			return nextIndex1;
		}
		else {
			return nextIndex2;
		}
	}
}

template<class T>
void HEAP<T>::doAdjustDown()
{
	int index = 0;
	if (getSonIndex(index) == index) {
		return;
	}
	while ((values[getSonIndex(index)] < values[index]) == greater){
		int next = getSonIndex(index);
		swap(values[next], values[index]);
		index = next;
		if(getSonIndex(index)==index){
			break;
		}
	}
}

template<class T>
vector<T> HEAP<T>::Sort(vector<T>& input)
{
	vector<T> result;
	putArray(input);
	int sizeStart = values.size();
	for (int i = 0; i < sizeStart; i++) {
		result.push_back(values[0]);
		swap(values[0], values[values.size() - 1]);
		values.pop_back();
		doAdjustDown();
	}
	return result;
}