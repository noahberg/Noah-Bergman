#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"
#include "util.h"

class SearchEng {
 public:
  SearchEng();
  ~SearchEng();
  void add_parse_from_index_file(std::string index_file, 
				 PageParser* parser);
  void add_parse_page(std::string filename, 
		      PageParser* parser);
  void mem_leaks_suck();

  void link_pages();

  void search(std::string query, MySetWebPage* results);

  void search(std::vector<std::string> queries, bool AND, MySetWebPage* results);

  std::map<std::string, WebPage*> get_index();
  /**** Add other desired member functions here *****/


 private:
 	std::map<std::string, WebPage*> index;
  /**** Add other desired data members here *****/


};

#endif
