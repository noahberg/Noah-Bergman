#ifndef MARK_PARSER_H
#define MARK_PARSER_H

#include <string>
#include <vector>
#include "pageparser.h"
#include "myset.h"


class PageParserMarkdown : public PageParser {

public:
	~PageParserMarkdown();
	PageParserMarkdown();
	void parse(std::string filename,
		     MySet<std::string>& allWords,
		     MySet<std::string>& allLinks, std::vector<std::string>& olinks);


};

#endif
