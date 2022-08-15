#pragma once
#include<iostream>
using namespace std;
#include<vector>
template<class Type>
void bubbleSort(vector<Type>& values, bool greater = true)
{
	for (int i = 0; i < values.size() - 1; i++) {
		for (int j = 0; j < values.size() - 1; j++) {
			if ((values[j + 1] < values[j]) == greater) {
				swap(values[j], values[j + 1]);
			}
		}
	}
}

template<class Type>
void chooseSort(vector<Type>& values, bool greater = true)
{
	for (int i = 0; i < values.size() - 1; i++) {
		Type chooseValue = values[i];
		Type chooseIndex = i;
		for (int j = i + 1; j < values.size(); j++) {
			if ((values[j] < chooseValue) == greater) {
				chooseValue = values[j];
				chooseIndex = j;
			}
		}
		swap(values[i], values[chooseIndex]);
	}
}

template<class Type>
int partition(vector<Type>& values, int begin, int end, bool greater = true)
{
	int saveValue = values[end - 1];
	int curIndex = begin;
	for (int i = begin; i < end-1; i++) {
		if ((values[i] < saveValue) == greater) {
			swap(values[i], values[curIndex]);
			curIndex++;
		}
	}
	swap(values[curIndex], values[end - 1]);
	return curIndex;
}

template<class Type>
void quickSortIterator(vector<Type>& values, int begin, int end, bool greater = true)
{
	if (begin < end - 1) {
		int index = partition(values, begin, end, greater);
		quickSortIterator(values, begin, index, greater);
		quickSortIterator(values, index + 1, end, greater);
	}
}

template<class Type>
void quickSort(vector<Type>& values, bool greater = true)
{
	quickSortIterator(values, 0, values.size(), greater);
}


template<class Type>
void mergeSortIterator(vector<Type>& values, int begin, int end, bool greater = true)
{
	if (begin < end - 1) {
		int mid = (begin + end) / 2;
		mergeSortIterator(values, begin, mid, greater);
		mergeSortIterator(values, mid, end, greater);
		vector<Type> leftVector, rightVector;
		for (int i = begin; i < mid; i++) {
			leftVector.push_back(values[i]);
		}
		for (int i = mid; i < end; i++) {
			rightVector.push_back(values[i]);
		}
		int leftIndex = 0, rightIndex = 0, curIndex=begin;
		while (leftIndex < leftVector.size() && rightIndex < rightVector.size()) {
			if ((leftVector[leftIndex] < rightVector[rightIndex]) == greater) {
				values[curIndex] = leftVector[leftIndex];
				leftIndex++;
			}
			else {
				values[curIndex] = rightVector[rightIndex];
				rightIndex++;
			}
			curIndex++;
		}
		while (leftIndex < leftVector.size()) {
			values[curIndex] = leftVector[leftIndex];
			leftIndex++;
			curIndex++;
		}
		while (rightIndex < rightVector.size()) {
			values[curIndex] = rightVector[rightIndex];
			rightIndex++;
			curIndex++;
		}
	}
}

template<class Type>
void mergeSort(vector<Type>& values, bool greater = true)
{
	mergeSortIterator(values, 0, values.size(), greater);
}

