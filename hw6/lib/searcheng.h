#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <fstream>
#include <vector>
#include <string>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"
#include "util.h"


class SearchEng {
 public:
  SearchEng();
  ~SearchEng();
  void add_parse_from_config_file(std::string config_file, 
				 PageParser* parser);
  void add_parse_no_config(PageParser* parser);

  void add_parse_page(std::string filename, 
          PageParser* parser);

  void link_pages();

  void search(std::string query, MySet<WebPage*>* results);

  void search(std::vector<std::string> queries, bool AND, MySet<WebPage*>* results);

  std::vector<WebPage*> pageRank(MySet<WebPage*>* candidates);

  std::map<std::string, WebPage*> get_index();
  /**** Add other desired member functions here *****/


 private:
 	std::map<std::string, WebPage*> index;
  std::string index_file;
  double restart_probability;
  double step_number;
  /**** Add other desired data members here *****/


};

#endif
