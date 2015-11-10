#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <iostream>

#include "lib/webpage.h"
#include "lib/myset.h"
#include "lib/pageparser.h"
#include "lib/util.h"



using namespace std;


void crawl_helper(WebPage* current, PageParser* parser, ofstream& output, map<string, WebPage*>* index);

int main(int argc, char* argv[]) {

	std::string index_file;
	std::string output_file;
	std::map<std::string, WebPage*> index;
	ifstream config;
	if(argc >3){
    	std::cerr << "usage: ./search config_file...Please provide only configuration file" << std::endl;
    	return 1;
  	}
  	else if(argc == 2) {
  		config.open(argv[1]);
  		if(config.fail()) {
		std::cerr << "Could not find file...Please provide a valid configuration file" << std::endl;
    	return 1;
	}
  	}
  	else {
  		string file = "config.txt";
  		config.open(file.c_str());
  		if(config.fail()) {
			std::cerr << "Could not find output.txt" << std::endl;
    		return 1;
		}
  	}


	while(!config.fail()) {
		string line;
		getline(config, line);
		if(!config.fail()) {
			if(!line.empty() && line[0] != '#') {
				if(line.substr(0, 10) == "INDEX_FILE") {
					bool started = false;
					for(unsigned int i = 10; i<line.length(); i++) {
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
				if(line.substr(0, 11) == "OUTPUT_FILE") {
					bool started = false;
					for(unsigned int i = 11; i<line.length(); i++) {
						if(started) {
							if(line[i] != ' ') {
								output_file += line[i];
							}
						}
						else if(line[i] == '=') {
							started = true;
						}
					}
				}
			
			}
		}
	}

	PageParserMarkdown p;
	PageParser* parser = &p;

	ifstream indexFile(index_file.c_str());
	ofstream output(output_file.c_str());

	while(!indexFile.fail()) {
		string line;
		getline(indexFile, line);
		if(!line.empty()) {
			WebPage* current = new WebPage(line);
			try{
				current->parse(parser);
				index[line] = current;
				crawl_helper(current, parser, output, &index);
			}
			catch(...){
				delete current;
			}
		}

	}
}


void crawl_helper(WebPage* current, PageParser* parser, ofstream& output, map<string, WebPage*>* index) {
 	output << current->filename() << endl;
 	vector<string> outgoing = current->outgoing_links_vector();

 	for(unsigned int i = 0; i < outgoing.size(); i++) {

 		if(index->count(outgoing[i]) == 0) {

 			WebPage* child = new WebPage(outgoing[i]);
			try{
				child->parse(parser);
				(*index)[outgoing[i]] = child;
				crawl_helper(child, parser, output, index);
			}
			catch (...){
				delete child;
			}
 		}
 	}
}



