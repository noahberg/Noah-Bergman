#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Node {
    int value;
    Node *next;
};

void split (Node*& in, Node*& smaller, Node*& larger, int pivot);
void print(Node* list, int count);


int main() {
	
	srand (time(NULL));
	Node* array = new Node[150];
	Node* in = &array[0];
	array[0].value = 20;
	for(int i =1; i<150; i++) {
		array[i-1].next = &array[i];
		array[i].value = rand() % 200;
	}
	array[149].next = NULL;
	array[149].value = 1002;
	print(in, 0);
	cout << endl << endl;
	Node small;
	small.value = 5;
	small.next = NULL;
	Node* smaller = &small;
	Node large; 
	large.value = 65;
	large.next = NULL;
	Node* larger = &large;
	smaller = NULL;
	larger = NULL;
	split(in, smaller, larger, 75);

	print(smaller, 0);
	cout << endl << endl;
	print(larger, 0);
	cout << endl << endl;
	cout << in;
	cout << endl; 
	delete[] array;
}


void split (Node*& in, Node*& smaller, Node*& larger, int pivot) {
	if(in == NULL) 
		return;
	int value = in->value;
	Node* temp = in->next;

	if(value <= pivot) {
		in->next = smaller;
		smaller = in;
		in = temp;
		split(in, smaller, larger, pivot);
	}
	else {
		in->next = larger;
		larger = in;
		in = temp;
		split(in, smaller, larger, pivot);
	}
}


void print(Node* list, int count) {
	if(list == NULL)
		return;
	count++;
	cout << list->value << " ";
	if(list->next) {
		print(list->next, count);
	}
	else
		cout << endl << count;
	return;
}
