#include "llistint.h"
#include <iostream>

using namespace std;

int main() {
	LListInt* list = new LListInt();
	int passed = 0;
	int total_tests = 0;
	if(!list->empty())
		cout << "Failure, test at line 10" << endl;
	else
		passed++;
	total_tests++;


	/*
		tests for insert function
	*/

	// test inserting at wrong position
	list->insert(3, 0);
	if(list->size() != 0)
		cout << "Failure, test at line 23" << endl;
	else
		passed++;
	total_tests++;
	// test inserting on empty list
	list->insert(0, 4);
	if(list->size() != 1 || list->get(0) != 4)
		cout << "Failure, test at line 30" << endl;
	else 
		passed++;
	total_tests++;
	// test inserting at end of list
	list->insert(1, 21);
	if(list->size() != 2 || list->get(1) != 21)
		cout << "Failure, test at line 36" << endl;
	else 
		passed++;
	total_tests++;
	// test inserting at beginning of list
	list->insert(0, 42);
	if(list->size() != 3 || list->get(0) != 42 || list->get(1) != 4)
		cout << "Failure, test at line 43" << endl;
	else
		passed++;
	total_tests++;;
	// test inserting in the middle of list 
	list->insert(2, -35);
	if(list->size() != 4 || list->get(2) != -35 || list->get(1) != 4 || list->get(3) != 21)
		cout << "Failure, test at line 51"<< endl;
	else 
		passed++;
	total_tests++;
	// test inserting at a negative number (should do nothing)
	list->insert(-3, 34);
	if(list->size() !=4)
		cout << "Failure, test at line 58"<< endl;
	else
		passed++;
	total_tests++;
	// test inserting at a pos greater than size (should do nothing)
	list->insert(5, 54);
	if(list->size() !=4)
		cout << "Failure, test at line 64"<< endl;
	else
		passed++;
	total_tests++;


	/*
		tests for remove function 
	*/

	// test for removing at a position greater than size -1
	list->remove(4);
	if(list->size() !=4)
		cout << "Failure, test at line 77"<< endl;
	else
		passed++;
	total_tests++;
	// test for removing at a negative position
	list->remove(-2);
	if(list->size() !=4)
		cout << "Failure, test at line 84"<< endl;
	else
		passed++;
	total_tests++;
	// test for removing at the beginning of list
	list->remove(0);
	if(list->size() != 3 || list->get(0) != 4)
		cout << "Failure, test at line 92"<< endl;
	else
		passed++;
	total_tests++;
	// test for removing at the middle of a list
	list->remove(1);
	if(list->size() != 2 || list->get(0) != 4 || list->get(1) != 21)
		cout << "Failure, test at line 99"<< endl;
	else
		passed++;
	total_tests++;
	// test for removing at end of list
	list->remove(1);
	if(list->size() != 1 || list->get(0) != 4)
		cout << "Failure, test at line 105"<< endl;
	else
		passed++;
	total_tests++;
	// test for removing only item in a list
	list->remove(0);
	if(!list->empty())
		cout << "Failure, test at line 112"<< endl;
	else
		passed++;
	total_tests++;



	cout << passed << " tests passed out of " << total_tests << " total tests" << endl;

	delete list;

}