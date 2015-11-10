#ifndef MYSET_H
#define MYSET_H

#include <set>

// avoid circular reference
class WebPage;

template<class T>
class MySet : public std::set<T>
{
public:
  MySet();
  MySet set_intersection(const MySet& other);
  MySet set_union(const MySet& other);
};

template<class T>
MySet<T>::MySet() : std::set<T>() {}

template<class T>
MySet<T> MySet<T>::set_intersection(const MySet& other) {
	MySet temp;
	for(typename std::set<T>::iterator it = other.begin(); it != other.end(); ++it) {
		if(this->count(*it) != 0)
			temp.insert(*it);
	}

	return temp;
}

template<class T>
MySet<T> MySet<T>::set_union(const MySet& other) {
	MySet temp;
	for(typename std::set<T>::iterator it = this->begin(); it != this->end(); ++it) {
		temp.insert(*it);
	}
	for(typename std::set<T>::iterator it = other.begin(); it != other.end(); ++it) {
		temp.insert(*it);
	}
	return temp;


}

#endif