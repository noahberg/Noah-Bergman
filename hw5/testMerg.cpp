#include <fstream>
#include <string>
#include <iostream>

#include "merg.h"

using namespace std;

  struct AlphaStrComp {
    bool operator()(const string& lhs, const string& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return rhs.size() < lhs.size(); 
    }
  };

  struct LengthStrComp {
    bool operator()(const string& lhs, const string& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs.size() < rhs.size(); 
    }
  };

int main(int argc, char* argv[]) {
	
	string words[] = {"hey", "manager", "computer", "programming", 
						"size", "alpha", "comparator", "confusion", "tired",
						"mergeSort", "immediate"};
	vector<string> a;
	vector<string> l;
	for(int i = 0; i < 11; i++) {
		a.push_back(words[i]);
		l.push_back(words[i]);
	}
	AlphaStrComp alpha;
	LengthStrComp length;

	cout << "Here is original list: " <<  endl << endl;
	for(unsigned int i = 0; i<11; i++) {
		cout << words[i].size() << " ";
	}
	cout << endl << endl;
mergeSort(a, alpha);
	mergeSort(l, length);
	cout << "Here is list sorted with one comp (should be decreasing): " << endl << endl;
	for(unsigned int i = 0; i<a.size(); i++) {
		cout << a[i].size() << " ";
	}
	cout << endl << endl;

	cout << "Here is list sorted with other (should be increasing): " << endl << endl;
	for(unsigned int i = 0; i<l.size(); i++) {
		cout << l[i].size() << " ";
	}
	cout << endl << endl;
}