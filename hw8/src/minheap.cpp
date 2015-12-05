

#include "../lib/minheap.h"

using namespace std;

MinHeap::MinHeap(int d) {
	if(d<2) {
		dAry = 2;
	}
	else
		dAry = d;
	indices = new HashTable;
	heap = new vector<pair<string, int> >;

}

MinHeap::~MinHeap() {
	delete heap;
	delete indices;
}

void MinHeap::trickleDown(int index) {
	
	if((dAry*index+1) > heap->size()) return;

	int smallestChild = dAry*index+1;
	int currentChild = dAry*index+2;
	LessThanPair a;
	while((currentChild <= ((dAry*index)+dAry)) && (currentChild < heap->size())) {
		if(a((*heap)[currentChild], (*heap)[smallestChild])) {
			smallestChild = currentChild;
		}
		currentChild++;
	}
	if(a((*heap)[smallestChild], (*heap)[index])) {
		swap((*heap)[smallestChild], (*heap)[index]);
		pair<string, int> newIndex1;
		newIndex1.first = (*heap)[index].first;
		newIndex1.second = index;
		indices->update(newIndex1);
		pair<string, int> newIndex2;
		newIndex2.first = (*heap)[smallestChild].first;
		newIndex2.second = smallestChild;
		indices->update(newIndex2);
		trickleDown(smallestChild);
		return;
	}
	else 
		return;

}

void MinHeap::pushUp(int index) {
	if(index == 0) {
		return;
	}
	int parent = (index-1)/dAry;
	LessThanPair a;
	if(a((*heap)[index], (*heap)[parent])) {
		swap((*heap)[index], (*heap)[parent]);
		pair<string, int> newIndex1;
		newIndex1.first = (*heap)[index].first;
		newIndex1.second = index;
		indices->update(newIndex1);
		pair<string, int> newIndex2;
		newIndex2.first = (*heap)[parent].first;
		newIndex2.second = parent;
		indices->update(newIndex2);
		pushUp(parent);
	}
	else {
		return;
	}
}

void MinHeap::add(string item, int priority) {
	pair<string, int> newItem;
	newItem.first = item; newItem.second = priority;
	heap->push_back(newItem);
	pair<string, int> newIndex;
	newIndex.first = item; newIndex.second = heap->size() -1;
	indices->add(newIndex);
	pushUp(newIndex.second);
	
}

const string& MinHeap::peek() const {
	if(heap->size() == 0) {
		throw out_of_range("heap is empty");
	}
	return ((*heap)[0]).first;
}

void MinHeap::remove() {
	if(isEmpty()) {
		throw out_of_range("heap is empty");	
	}
	indices->remove((*heap)[0].first);
	(*heap)[0] = heap->back();
	heap->pop_back();
	trickleDown(0);
	
}

void MinHeap::update(string item, int priority) {
	try {
		indices->find(item);

	}
	catch(...) {
		throw invalid_argument("item does not exist");
	}
	
	int index = indices->find(item);
	int prevPriority = (*heap)[index].second;
	(*heap)[index].second = priority;
	if(prevPriority == priority) {
		return;
	}
	else if(priority < prevPriority) {
		pushUp(index);
	
		return;
	}
	else {
		trickleDown(index);
		return;
	}
}

bool MinHeap::isEmpty() {
	if(heap->size() == 0) 
		return true;
	else return false;
}

