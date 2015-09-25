#include "../lib/stackint.h"

#include <iostream>
void makeList();
int main() {
	makeList();
	StackInt* a = new StackInt;
	if(!a->empty())
		std::cout << "failure. line 7" << std::endl;
	for(int i = 0; i < 1000; ++i) {
		a->push(i);
	}
	if(a->empty())
		std::cout << "Failure. line 13" << std::endl;
	for(int i = 999; i >= 0; --i) {
		if(a->top() != i)
			std::cout << "failure, line 16" << std::endl;
		a->pop();
	}
	if(!a->empty())
		std::cout << "failure, line 21" << std::endl;
	a->pop();
	a->push(1);
	a->top();
	a->push(2);
	if(a->top() != 2)
		std::cout << "failure, line 26" << std::endl;

	delete a;
	std::cout << "done" << std::endl << std::endl;


}

void makeList() {
	StackInt b;
}