#ifndef MYSET_H
#define MYSET_H

#include <set>
#include <string>

// avoid circular reference
class WebPage;

class MySetString : public std::set<std::string>
{
public:
  MySetString();
  MySetString set_intersection(const MySetString& other);
  MySetString set_union(const MySetString& other);
};

class MySetWebPage : public std::set<WebPage*>
{
public:
  MySetWebPage();
  MySetWebPage set_intersection(const MySetWebPage& other);
  MySetWebPage set_union(const MySetWebPage& other);
};

#endif
