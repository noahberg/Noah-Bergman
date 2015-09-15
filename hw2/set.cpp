#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <locale>
#include <set>

using namespace std;

void user_query(set<string>& container);

int main(int argc, char* argv[]) {
	if(argc == 1) {
		cout << "Please provide the name of a text file as a command line arguement";
		return 1;
	}
	if(argc > 2) {
		cout << "Please provide only on arguement, the name of a text file";
		return 1;
	}

	ifstream input(argv[1]);
	if(input.fail()) {
		cout << "Could not find input file" << endl;
		return 1;
	}
	set<string> container;
	string s;
	while(!input.fail()) {
		char c;
		input.get(c);
		if(!input.fail()) {
			if(isalpha(c)) {
				c = tolower(c);
				s = s + c;
			}
			else {
				if(!s.empty())
				container.insert(s);
				s.clear();
			}
		}
	}

	user_query(container);

}

void user_query(set<string>& container) {
	cout << "Please enter a query string: ";
	string q; 
	getline(cin, q);
	if(q.empty()) {
		return;
	}
	else {
		for(unsigned int i=0; i < q.length(); i++) {
			q[i] = tolower(q[i]);
		}
		int contains = container.count(q);
		if(contains == 0) 
			cout << "not in the file" << endl;
		else
			cout << "in the file" << endl;
		user_query(container);
	}
}