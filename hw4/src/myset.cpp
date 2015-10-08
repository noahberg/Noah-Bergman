#include "../lib/myset.h"
#include "../lib/webpage.h"

MySetString::MySetString() : std::set<std::string>() {}

MySetString MySetString::set_intersection(const MySetString& other) {
	MySetString temp;
	for(std::set<std::string>::iterator it = other.begin(); it != other.end(); ++it) {
		if(this->count(*it) != 0)
			temp.insert(*it);
	}

	return temp;
}

MySetString MySetString::set_union(const MySetString& other) {
	MySetString temp;
	for(std::set<std::string>::iterator it = this->begin(); it != this->end(); ++it) {
		temp.insert(*it);
	}
	for(std::set<std::string>::iterator it = other.begin(); it != other.end(); ++it) {
		temp.insert(*it);
	}
	return temp;


}

MySetWebPage::MySetWebPage() : std::set<WebPage*>() {}

MySetWebPage MySetWebPage::set_intersection(const MySetWebPage& other) {
	MySetWebPage temp;
	for(std::set<WebPage*>::iterator it = other.begin(); it != other.end(); ++it) {
		if(this->count(*it) != 0)
			temp.insert(*it);
	}
	return temp;

}

MySetWebPage MySetWebPage::set_union(const MySetWebPage& other) {
	MySetWebPage temp;
	for(std::set<WebPage*>::iterator it = this->begin(); it != this->end(); ++it) {
		temp.insert(*it);
	}
	for(std::set<WebPage*>::iterator it = other.begin(); it != other.end(); ++it) {
		temp.insert(*it);
	}
	return temp;

}
