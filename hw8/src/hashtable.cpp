#include "../lib/hashtable.h"

using namespace std;

HashTable::HashTable() {
	this->size=31;
	this->entries=0;

	data = new list<pair<string, int> >*[size];
	for(int i = 0; i < size; i++) {
		data[i] = new list<pair<string, int> >;
	}
}

HashTable::~HashTable() {
	for(int i = 0; i < size; i++) {
		delete data[i];
	}
	delete data;
}

string HashTable::convToLower(string src) const
{
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

long long HashTable::hash(string key) const {

	long long power = 1;
	string nKey = key;
	nKey = convToLower(nKey);
	long long index = 0;

	for(int i = nKey.length()-1; i >= 0; i--) {

		long long contribution = ((int)nKey[i] - 97)*power;
		index += contribution;
		power *= 29;
	}
	index = index%size;
	return index;
}

void HashTable::resize() {
	int prevsize = size;
	size = 2*size + 1;
	list<pair<string, int> >** oData = data;
	data = new list<pair<string, int> >*[size];


	for(int i = 0; i<prevsize; i++) {
		for(list<pair<string, int> >::iterator it = oData[i]->begin(); it != oData[i]->end(); ++it) {

			long long h = hash(it->first);
			data[h]->push_back(*it);
		}
		delete oData[i];
	}
	delete oData;
}



void HashTable::add(pair<string, int> new_item) {
	if((entries+1)/size > 1)
		resize();
	entries++;
	long long h =  hash(new_item.first);
	for(list<pair<string, int> >::iterator it = data[h]->begin(); it != data[h]->end(); ++it) {
		if(it->first == new_item.first) {
			throw invalid_argument("key already exists");
		}
	}
	data[h]->push_back(new_item);
}
const int& HashTable::find(string key) const {
	long long h = hash(key);
	for(list<pair<string, int> >::iterator it = data[h]->begin(); it != data[h]->end(); ++it) {
		if(it->first == key) {
			return it->second;
		}
	}
	throw invalid_argument("key does not exist");
}

void HashTable::remove(std::string key) {
	long long h = hash(key);
	for(list<pair<string, int> >::iterator it = data[h]->begin(); it != data[h]->end(); ++it) {
		if(it->first == key) {
			data[h]->erase(it);
			entries--;
			return;
		}
	}
	throw invalid_argument("key does not exist");
}

void HashTable::update(pair<string, int> new_value) {
	long long h = hash(new_value.first);
	for(list<pair<string, int> >::iterator it = data[h]->begin(); it != data[h]->end(); ++it) {
		if(it->first == new_value.first) {
			it->second = new_value.second;
			return;
		}
	}
	throw invalid_argument("key does not exist");

}