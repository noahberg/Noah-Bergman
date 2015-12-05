#include <iostream>
#include "../lib/minheap.h"
#include "../lib/hashtable.h"

using namespace std;

int main() {
	MinHeap heap(3);
	if(!heap.isEmpty()) {
		cout << "error 10";
	}
	
	heap.add("happy", 6);
	
	heap.add("alive", 6);
	
	heap.add("unusual", 9);
	
	heap.add("what", 15);
	
	heap.add("comsci", 2);
	if(heap.peek() != "comsci") {
		cout << heap.peek() << endl; 
	}

	heap.update("comsci", 20);
	if(heap.peek() != "alive") {
		cout << heap.peek() << endl;
	}
	heap.remove();
	if(heap.isEmpty()) {
		cout << "error 32";
	}
	if(heap.peek() != "happy") {
		cout << heap.peek();
	}

	heap.add("lifestyle", 7);
	heap.remove();
	if(heap.peek() != "lifestyle") {
		cout << heap.peek();
	}

}
