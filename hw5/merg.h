#ifndef MERGE_H
#define MERGE_H

#include <vector>
#include <iostream>

using namespace std;

template<class T, class Comparator> 
vector<T> merge(vector<T> left, vector<T> right, Comparator comp) {
	vector<T> result;
	while((int)left.size() > 0 || (int)right.size() > 0) {
		if((int)left.size() == 0) {

			result.push_back(right.front());
			right.erase(right.begin());
		}
		else if((int)right.size() == 0) {
			result.push_back(left.front());
			left.erase(left.begin());
		}
		else if(comp(left.front(), right.front())) {
			result.push_back(left.front());
			left.erase(left.begin());
		}
		else {
			result.push_back(right.front());
			right.erase(right.begin());
		}
	}
	return result;

}

template<class T, class Comparator> 
void merge_(vector<T>& merged, Comparator comp, int start, int mid, int end) {
	int currentL = start;
	int currentR = mid+1;
	vector<T> result;
	while((currentL < mid+1) || (currentR < end+1)) {
		if(currentL == mid+1) {
			result.push_back(merged[currentR]);
			currentR++;
		}
		else if(currentR == end + 1) {
			result.push_back(merged[currentL]);
			currentL++;
		}
		else if(comp(merged[currentL], merged[currentR])) {
			result.push_back(merged[currentL]);
			currentL++;
		}
		else {
			result.push_back(merged[currentR]);
			currentR++;
		}
	}
	
	int t = 0;
	for(int i = start; i<= end; i++) {

		merged[i] = result[t];
		t++;

	}


}

template<class T, class Comparator>
void mergeSort(vector<T>& myArray, Comparator comp) {
	myArray = mergeSortHelper(myArray, comp);
}

template<class T, class Comparator>
vector<T> mergeSortHelper(vector<T> myArray, Comparator comp) {
		if(myArray.size() <= 1)
			return myArray;
		int mid = myArray.size()/2;
		vector<T> left;
		for(int i = 0; i<mid; i++) {
			left.push_back(myArray[i]);
		}
		vector<T> right;
		for(unsigned int i = mid; i<myArray.size(); i++) {
			right.push_back(myArray[i]);
		}
		left = mergeSortHelper(left, comp);
		right = mergeSortHelper(right, comp);
		vector<T> merged;
		merged = merge(left, right, comp);
		return merged;

		
	
}

template<class T, class Comparator>
void mergeSort_(vector<T>& myArray, Comparator comp) {
	mergeSort_(myArray, comp, 0, myArray.size()-1);
}

template<class T, class Comparator>
void mergeSort_(vector<T>& myArray, Comparator comp, int start, int end) {
		if(start < end) {
			int mid = (end + start)/2;
			mergeSort(myArray, comp, start, mid);
			mergeSort(myArray, comp, mid+1, end);
			for(unsigned int i = start; i <= end; i++) {
				cout << myArray[i].size() << " " ;
			}
			cout << endl;
			merge(myArray, comp, start, mid, end);
		}
		else {
			cout << myArray[start].size() << " ";
			cout << endl;
		}
}


#endif