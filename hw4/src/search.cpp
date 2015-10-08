#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>

#include "../lib/webpage.h"
#include "../lib/searcheng.h"

using namespace std;

void display_results(set<WebPage*>& results);
vector<string> process_query(string query);

int main(int argc, char* argv[])
{
  if(argc < 2 || argc >3){
    cerr << "usage: ./search index_file...Please provide an index file" << endl;
    return 1;
  }

  SearchEng engine;
  PageParserMarkdown p;
  PageParser* parser = &p;
  engine.add_parse_from_index_file(string(argv[1]), parser);

  map<string, WebPage*> index = engine.get_index();
  engine.link_pages();

 





  /****************   Add code to ***************************/
  /* Initialize your search engine and parse all the pages */



  
  string myline;
  bool done = false;
  while( !done ){
    cout << "\n++++++++++++++++++++" << endl;
    cout << "Enter search terms: " << endl;
    getline(cin, myline);
    cout << "++++++++++++++++++++\n" << endl;
    if(myline == ".")
    	done = true;
    else {
    	vector<string> queries = process_query(myline);
    	bool invalid = false;
    	MySetWebPage results;
    	if(queries.size() == 0) {
    		cout << "Please enter a query" << endl;
    		invalid = true;
    	}
    	else if(queries.size() == 1) {
    		engine.search(queries[0], &results);
    	}
    	else if(queries[0] != "AND" && queries[0] != "OR") {
    		cout << "ERROR: Please enter a valid query." << endl;
    		invalid = true;
    	}
    	else {
    		if(queries[0] == "AND")
    			engine.search(queries, true, &results);
    		else
    			engine.search(queries, false, &results);
    	}

    	if(!invalid)	
    		display_results(results);
    }


    /* Add your code here and feel free to modify    */
    /*  what is above but don't change the display.  */
    /* Call display_results() with the set of pages  */
    /*  that match the search. It will display the   */
    /*  matching results to the screen for you.      */

    }
 
  engine.mem_leaks_suck();
  return 0;
}

vector<string> process_query(string query) {
	vector<string> queries;
	string current;
	for(unsigned int i = 0; i<query.length(); ++i) {
		if(query[i] == ' ' || query[i] == '\t' || query[i] == '\v') {
			if(!current.empty()) {
				queries.push_back(current);
				current.clear();
			}

		}
		else
			current += query[i];

	}
	if(!current.empty()) {
		queries.push_back(current);
	}

	return queries;
}

void display_results(set<WebPage*>& results)
{
  int hits = results.size();
  cout << hits << " hits." << endl;
  cout << "=====" << endl;
  int i=0;
  for(set<WebPage*>::iterator it = results.begin();
      it != results.end();
      ++it)
    {
      cout << (*it)->filename() << endl;
      cout << "+---+" << endl;
      cout << (**it) << "\n" << endl;
      i++;
    }
  
}
