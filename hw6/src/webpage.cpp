#include "../lib/webpage.h"
#include "../lib/pageparsermarkdown.h"

#include <fstream>
#include <string>
#include <cctype>
#include <stdexcept>


WebPage::WebPage() { }

WebPage::~WebPage() { }

WebPage::WebPage(std::string filename) :
	filename_(filename)
{	

}

void WebPage::parse(PageParser* parser) {
	parser->parse(filename_, words_, olinksString_, olinksVector_);
	for(std::set<std::string>::iterator it = words_.begin(); it != words_.end(); ++it) {
		words_lowercase.insert(convToLower(*it));
	}
}

std::vector<std::string> WebPage::outgoing_links_vector() {
	return olinksVector_;
}

void WebPage::filename(std::string fname) {
	filename_ = fname;
	
}

std::string WebPage::filename() const {
	return filename_;
}

void WebPage::all_words(const MySet<std::string>& words) {
	words_ = words_.set_union(words);
}

MySet<std::string> WebPage::all_words() const {
	return words_;
}

MySet<std::string> WebPage::all_words_lowercase() const {
	return words_lowercase;
}

void WebPage::add_incoming_link(WebPage* wp) {
	ilinks_.insert(wp);
}

MySet<WebPage*> WebPage::incoming_links() const { 
	return ilinks_;
}

void WebPage::add_outgoing_link(WebPage* wp) {
	olinks_.insert(wp);
}

MySet<std::string> WebPage::outgoing_links_string() const {
	return olinksString_;
}

MySet<WebPage*> WebPage::outgoing_links() const {
	return olinks_;
}

std::ostream& operator<<(std::ostream& os, const WebPage& page) {
	std::ifstream file(page.filename().c_str());

	if(file.fail()) {
		return os;
	}

	while(!file.fail()) {
		char c;
		file.get(c);
		if(!file.fail()) {
			if(c != '[') {
				os << c;
			}
			else {
				os << c;
				while(!file.fail()) {
					file.get(c);
					if(!file.fail()) {
						if(c == ']') {
							os << c;
							break;
						}
						else
							os << c;
					}
				}
				file.get(c);
				if(!file.fail()) {
					if(c != '(')
						throw std::invalid_argument("File is misformated. No ( signaling start of link after ] indicating end to anchor text");
					while(!file.fail()) {
						file.get(c);
						if(!file.fail()) {
							if(c == ')')
								break;
						}
					}

				}
			}
		}
	}

	return os;

}

