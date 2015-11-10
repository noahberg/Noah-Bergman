#include "../lib/searcheng.h"
#include "../lib/util.h"
#include "../lib/merg.h"

using namespace std;

struct PageRankStruct {
	double rank;
	WebPage* page;
};

struct PageRankComp {
	bool operator()(PageRankStruct lhs, PageRankStruct rhs) {
		return lhs.rank > rhs.rank;
	}
};



SearchEng::SearchEng() {  };

SearchEng::~SearchEng() {
	for(map<string, WebPage*>::iterator it = index.begin(); it != index.end(); ++it) {
    	WebPage* temp = it->second;
    	delete temp;

  }
  };

 
void SearchEng::add_parse_page(string filename, PageParser* parser) { 
	WebPage* current = new WebPage(filename);
	current->parse(parser);
	index[filename] = current;
}

void SearchEng::add_parse_from_config_file(string config_file, PageParser* parser) {
	
	ifstream config(config_file.c_str());

	if(config.fail())
		return;

	while(!config.fail()) {
		string line;
		getline(config, line);
		if(!config.fail()) {
			if(!line.empty() && line[0] != '#') {
			
				if(line.substr(0, 11) == "OUTPUT_FILE") {
					bool started = false;
					for(unsigned int i = 11; i<line.length(); i++) {
						if(started) {
							if(line[i] != ' ') {
								index_file += line[i];
							}
						}
						else if(line[i] == '=') {
							started = true;
						}
					}
				}
				if(line.substr(0, 19) == "RESTART_PROBABILITY") {
					int equal_index = 0;
					for(unsigned int i = 19; i<line.length(); i++) {
						if(line[i] == '=') {
							equal_index = i+1;
						}
					}
					if(equal_index != 0) {
						string restart = line.substr(equal_index);
						restart_probability = atof(restart.c_str());
					}
				}
				if(line.substr(0, 11) == "STEP_NUMBER") {
					int equal_index = 0;
					for(unsigned int i = 11; i<line.length(); i++) {
						if(line[i] == '=') {
							equal_index = i+1;
						}
					}
					if(equal_index != 0) {
						string step = line.substr(equal_index);
						step_number = atof(step.c_str());
					}
				}
			}
		}
	}
	config.close();

	ifstream files(index_file.c_str());
	while(!files.fail()) {
		string line;
		getline(files, line);
		if(!files.fail()) {
			if(!line.empty()) {
				add_parse_page(line, parser);
			}
		}

	}


}

void SearchEng::add_parse_no_config(PageParser* parser) {

	string config_file;
	config_file = "config.txt";
	ifstream config(config_file.c_str());

	if(config.fail())
		return;

	while(!config.fail()) {
		string line;
		getline(config, line);
		if(!config.fail()) {
			if(!line.empty() && line[0] != '#') {
				
				if(line.substr(0, 11) == "OUTPUT_FILE") {
					bool started = false;
					for(unsigned int i = 11; i<line.length(); i++) {
						if(started) {
							if(line[i] != ' ') {
								index_file += line[i];
							}
						}
						else if(line[i] == '=') {
							started = true;
						}
					}
				}
				if(line.substr(0, 19) == "RESTART_PROBABILITY") {
					int equal_index = 0;
					for(unsigned int i = 19; i<line.length(); i++) {
						if(line[i] == '=') {
							equal_index = i+1;
						}
					}
					if(equal_index != 0) {
						string restart = line.substr(equal_index);
						restart_probability = atof(restart.c_str());
					}
				}
				if(line.substr(0, 11) == "STEP_NUMBER") {
					int equal_index = 0;
					for(unsigned int i = 11; i<line.length(); i++) {
						if(line[i] == '=') {
							equal_index = i+1;
						}
					}
					if(equal_index != 0) {
						string step = line.substr(equal_index);
						step_number = atof(step.c_str());
					}
				}
			}
		}
	}

	ifstream files(index_file.c_str());
	while(!files.fail()) {
		string line;
		getline(files, line);
		if(!files.fail()) {
			if(!line.empty()) {
				add_parse_page(line, parser);
			}
		}

	}


}

void SearchEng::link_pages() {

	for(map<string, WebPage*>::iterator it = index.begin(); it != index.end(); ++it) {
		MySet<std::string> olinks = (it->second)->outgoing_links_string();
		for(set<string>::iterator ite = olinks.begin(); ite != olinks.end(); ++ite) {
			if(index.find(*ite) != index.end()) {
				(it->second)->add_outgoing_link(index[*ite]);
				index[*ite]->add_incoming_link(it->second);
			}
		}
	}

}

void SearchEng::search(string query, MySet<WebPage*>* results) {
	for(map<string, WebPage*>::iterator it = index.begin(); it != index.end(); ++it) {
		MySet<std::string> words = (it->second)->all_words_lowercase();
		if(words.count(convToLower(query))) {
			results->insert(it->second);
			*results = results->set_union(it->second->outgoing_links());
			*results = results->set_union(it->second->incoming_links());
		}
	}

}

void SearchEng::search(vector<string> queries, bool AND, MySet<WebPage*>* results) {
	MySet<WebPage*> newResults = *results;
	for(unsigned int i = 0; i < queries.size(); i++) {
		MySet<WebPage*> temp;
		search(queries[i], &temp);
		if(AND) {
			if(i == 0)
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

vector<WebPage*> SearchEng::pageRank(MySet<WebPage*>* candidates) {
	double n = candidates->size();

	vector<PageRankStruct> prevRank;
	vector<PageRankStruct> newRank;
	for(set<WebPage*>::iterator it = candidates->begin(); it != candidates->end(); ++it) {
		PageRankStruct temp1;
		temp1.page = *it;
		temp1.rank = 1/n;
		prevRank.push_back(temp1);
		PageRankStruct temp2;
		temp2.page = *it;
		temp2.rank = 0;
		newRank.push_back(temp2);
	}

	map<WebPage*, double> outgoingNumber;
	for(set<WebPage*>::iterator it = candidates->begin(); it != candidates->end(); ++it) {
		MySet<WebPage*> outgoing = (*it)->outgoing_links();
		outgoing = outgoing.set_intersection(*candidates);
		if(outgoing.count(*it) != 0) {
			outgoingNumber[*it] = outgoing.size();
		}
		else {
			outgoingNumber[*it] = outgoing.size() + 1;
		}

	}

	for(int i = 0; i< step_number; i++) {
		for(unsigned int i = 0; i < prevRank.size(); i++) {
			newRank[i].rank = 0;
			double rank = 0;
			for(unsigned int j = 0; j < prevRank.size(); j++) {
				if(i == j) {
					double contribution;
					contribution = (prevRank[j].rank)/(outgoingNumber[prevRank[j].page]);
					rank+=contribution;
				}
				else if((prevRank[j].page->outgoing_links()).count(prevRank[i].page) != 0) {
					double contribution;
					contribution = (prevRank[j].rank)/(outgoingNumber[prevRank[j].page]);
					rank += contribution;
				}
			}
			//cout << rank << endl;
			rank = rank*(1-restart_probability);
			rank += restart_probability/n;
			newRank[i].rank = rank;
		}
		for(unsigned int j = 0; j < prevRank.size(); j++) {
			prevRank[j] = newRank[j];
		}

	}

	PageRankComp a;
	mergeSort(prevRank, a);

	vector<WebPage*> result;
	double sum = 0;
	for(unsigned int j = 0; j < prevRank.size(); j++) {
		//cout << prevRank[j].page->filename() << " " << prevRank[j].rank << endl;
		sum+=prevRank[j].rank;
		result.push_back(prevRank[j].page);
	}
	//cout << "SUM " << sum << endl;


	return result;



}


