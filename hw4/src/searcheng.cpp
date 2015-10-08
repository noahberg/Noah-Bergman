#include "../lib/searcheng.h"
#include "../lib/util.h"

using namespace std;



SearchEng::SearchEng() {  };

SearchEng::~SearchEng() {  };

void SearchEng::add_parse_from_index_file(string index_file, PageParser* parser) {
	ifstream file(index_file.c_str());

	if(file.fail())
		return;

	while(!file.fail()) {
		string line;
		getline(file, line);
		if(!file.fail()) {
			if(!line.empty()) {
				add_parse_page(line, parser);
			}
		}

	}

}

void SearchEng::link_pages() {

	for(map<string, WebPage*>::iterator it = index.begin(); it != index.end(); ++it) {
		MySetString olinks = (it->second)->outgoing_links_string();
		for(set<string>::iterator ite = olinks.begin(); ite != olinks.end(); ++ite) {
			if(index.find(*ite) != index.end()) {
				(it->second)->add_outgoing_link(index[*ite]);
				index[*ite]->add_incoming_link(it->second);
			}
		}
	}

}

void SearchEng::search(string query, MySetWebPage* results) {
	for(map<string, WebPage*>::iterator it = index.begin(); it != index.end(); ++it) {
		MySetString words = (it->second)->all_words_lowercase();
		if(words.count(convToLower(query)))
			results->insert(it->second);
	}
}

void SearchEng::search(vector<string> queries, bool AND, MySetWebPage* results) {
	MySetWebPage newResults = *results;
	for(unsigned int i = 1; i < queries.size(); i++) {
		MySetWebPage temp;
		search(queries[i], &temp);
		if(AND) {
			if(i == 1)
				newResults = temp;
			else 
				newResults = newResults.set_intersection(temp);
		}
		else {
			newResults = newResults.set_union(temp);
		}
	}
	*results = newResults;
}

map<string, WebPage*> SearchEng::get_index() {
	return index;
}

void SearchEng::add_parse_page(string filename, PageParser* parser) { 
	WebPage* current = new WebPage(filename);
	current->parse(parser);
	index[filename] = current;
}

void SearchEng::mem_leaks_suck() {
	for(map<string, WebPage*>::iterator it = index.begin(); it != index.end(); ++it) {
    	WebPage* temp = it->second;
    	delete temp;

  }
}
