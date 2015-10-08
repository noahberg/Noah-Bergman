#ifndef MARK_PARSER_H
#define MARK_PARSER_H

#include "pageparser.h"
#include "myset.h"
#include <string>

class PageParserMarkdown : public PageParser {

public:
	~PageParserMarkdown();
	PageParserMarkdown();
	void parse(std::string filename,
		     MySetString& allWords,
		     MySetString& allLinks);


};

#endif
