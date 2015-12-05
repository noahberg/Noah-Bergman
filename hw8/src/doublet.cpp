#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <set>
#include <map>

#include "../lib/minheap.h"

using namespace std;

struct word {
	word* parent;
	string data;
	int h;
	int g;
	int f;
	int priority;
};

string convToLower(string src);


int incorrectLetters(string s, string target);

int main(int argc, char* argv[]) {

	if(argc != 4) {
		cout << "Please provide three command line arguements: head tail word.txt" << endl;
		return 1;
	}

	ifstream wordFile(argv[3]);
	if(wordFile.fail()) {
		cout << "Please provide a valid word file" << endl;
		return 1;
	}

	string s54(argv[1]);
	string head = convToLower(s54);
	string s65(argv[2]);
	string tail = convToLower(s65);
	int targetLength = head.length();

	set<string> words;
	MinHeap open(3);
	map<string, word*> wordObjects; 
	set<string> closed;


	int numWords;
	string num;
	getline(wordFile, num);
	if(wordFile.fail()) {
		cout << "Please provide a properly formatted word file" << endl;
		return 1;
	}

	numWords = atoi(num.c_str());
	int foundWords = 0;
	while(!wordFile.fail() && (foundWords < numWords)) {
		string w;
		getline(wordFile, w);
		if(wordFile.fail()) {
			break;
			
		}
		
		w.erase(remove_if(w.begin(), w.end(), ::isspace), w.end());
		int wLength = w.length();
		if(wLength == 0) {

		}
		else if(wLength == targetLength) {
			string q = convToLower(w);
			words.insert(q);
			foundWords++;
		}
		
	}

	

	
	word* headObject = new word;
	headObject->data = head;
	headObject->parent = NULL;
	headObject->g = 0;
	headObject->h = incorrectLetters(head, tail);
	headObject->f = 0;
	headObject->priority = 0;
	wordObjects.insert(pair<string, word*>(head, headObject));
	open.add(head, 0);
	word* tailObject = NULL;
	int expansions = 0;

	while(!open.isEmpty()) {
		
		string highest = open.peek();
		open.remove();
		closed.insert(highest);
		expansions++;
		word* current = wordObjects[highest]; 
		

		for(int i = 0; i < targetLength; i++) {
			
			for(int j = 97; j <= 122; j++) {
				
				string query = highest;
				char t = j;
				query[i] = t;
				
				if((words.count(query) && !closed.count(query)) && (query != highest)) {
					
					if(wordObjects.count(query) == 0) {
						
						word* newWord = new word;
						newWord->data = query;
						newWord->parent = current;
						newWord->g = (current->g)+1;
						newWord->h = incorrectLetters(query, tail);
						if(newWord->h == 0) {
							tailObject = newWord;

							goto finished;
						}
						
						newWord->f = newWord->g + newWord->h; 
						newWord->priority = newWord->f*(targetLength+1) + newWord->h;
						open.add(query, newWord->priority);
						wordObjects[query] = newWord; 
					}
					else {
						
						int newPriority = ((current->g) + 1 + (wordObjects[query]->h)) * (targetLength+1) + (wordObjects[query]->h);
						if(newPriority < (wordObjects[query])->priority) {
							open.update(query, newPriority);
							wordObjects[query]->priority = newPriority;
						}

					}
					
				}
			}
		}
	}
	

	

		for(map<string, word*>::iterator it = wordObjects.begin(); it != wordObjects.end(); ++it) {
			word* temp = it->second;
			delete temp;
		}
		cout << "could not find a solution " << endl;
		return 1;

		finished:

		vector<string> path;
		word* old = tailObject;
		while(tailObject !=NULL ) {
			path.push_back(tailObject->data);
			tailObject = tailObject->parent;
		}
		for(int i = path.size() - 1; i >= 0; i--) {
			cout << path[i]  << " ";
		}
		cout << endl << "expansions = " << expansions << endl;
		for(map<string, word*>::iterator it = wordObjects.begin(); it != wordObjects.end(); ++it) {
			word* temp = it->second;
			delete temp;
		}
		delete old;
		return 0; 
		
		
}

string convToLower(string src) {
	std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}


int incorrectLetters(string s, string target) {
	if(s.length() != target.length()) {
		return 100;
	}
	int numD = 0;
	for(unsigned int i = 0; i<s.length(); i++) {
		if(s[i] != target[i])
			numD++;
	}
	return numD;
}






