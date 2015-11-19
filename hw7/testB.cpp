#include <iostream>

#include "rbbst.h"


int main() 
{
	RedBlackTree<int, int> tree;
	/*for(int i = 0; i<10; i++) {
		std::pair<int, int> item;
		item.first = i; item.second = i;
		tree.insert(item);
	}*/
	std::pair<int, int> item;
	item.first = 0; item.second = 0;
	tree.insert(item);	
	tree.print();
	item.first = 1; item.second = 1;
	tree.insert(item);
	tree.print();
	item.first = 2; item.second = 2;
	tree.insert(item);
	tree.print();
	item.first = 3; item.second = 2;
	tree.insert(item);
	tree.print();
	item.first = 4; item.second = 2;
	tree.insert(item);
	tree.print();
	item.first = 6; item.second = 2;
	tree.insert(item);
	tree.print();
	item.first = 1; item.second = 2;
	tree.insert(item);
	tree.print();
	for(BinarySearchTree<int, int>::iterator it = tree.begin(); it != tree.end(); ++it) {
		std::cout << it->first << " ";
	}
	return 0;
}