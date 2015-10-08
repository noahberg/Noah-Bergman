#include "../lib/pageparsermarkdown.h"
#include "../lib/util.h"

#include <fstream> 
#include <cstdlib>
#include <cctype>
#include <stdexcept>
#include <iostream>

PageParserMarkdown::~PageParserMarkdown() { }

PageParserMarkdown::PageParserMarkdown() { }

void PageParserMarkdown::parse(std::string filename, MySetString& allWords, MySetString& allLinks) {

	std::ifstream file(filename.c_str());

	if(file.fail()) {
		throw std::invalid_argument("Could not find file");
	}

	std::string current;
	while(!file.fail()) {
		char c;
		file.get(c);
		if(!file.fail()) {
			if(isalnum(c)) {
				current += c;
			}
			else if(c == '[') {
				if(!current.empty()) {
					allWords.insert(current);
					current.clear();
				}
				std::string anchor;
				while(!file.fail()) {
					file.get(c);
					if(!file.fail()) {
						if(isalnum(c)) {
							anchor += c;
						}
						else {
							if(!anchor.empty()) {
								allWords.insert(anchor);
								anchor.clear();
							}
						}
						if(c == ']')
							break;
					}
				}
				file.get(c);
				if(!file.fail()) {
					if(c != '(')
						throw std::invalid_argument("File is misformated. No ( signaling start of link after ] indicating end to anchor text");
					file.get(c);
					std::string link;
					link += c;
					while(!file.fail()) {
						file.get(c);
						if(!file.fail()) {
							if(c != ')') {
								link += c;
							}
							else {
								if(!link.empty())
									allLinks.insert(link);
								break;
							}
						}
					}
				}
			}
			else {
				if(!current.empty()) {
					allWords.insert(current);
					current.clear();
				}
			}
		}
	}
	if(!current.empty()) {
		allWords.insert(current);
	}
}


