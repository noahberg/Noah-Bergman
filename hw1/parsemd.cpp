#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]) {
    // check for correct number of input file
   if(argc != 3) {
      cout << "Wrong number of command line arguements" << endl;
      return 1;
    }
    
   ifstream input(argv[1]);
   // check to see if input file can be found
   if(input.fail()) {
      cout << "Could not find input file" << endl;
      return 1;
    }
    ofstream output(argv[2]);

    // bool of whether current char is part of a link
    bool currently_link = false;
    while(!input.fail()) {
    	char c;
    	input.get(c);
        // make sure end of file has not been reached
    	if(!input.fail()) {
            // '[' could denote start of a link or could not
    		if(c=='[') {
                // remember current position
    			streampos position = input.tellg();
    			char f;
    			input.get(f);
                // loop to see if '[' is the start of a link
    			while(!input.fail()) {
    				input.get(f);
    				if(f == '[' || f=='(') {
    					break;
    				}
    				if(f==']') {
    					input.get(f);
    					if(f == '(')
    						currently_link = true;
    					break;
    				}
    			}
                // go back to previous position
    			input.seekg(position);

    		}
            // '(' automatically denotes start of link
    		if(c == '(')
    			currently_link = true;
            // c is the start of a link, format and output the link
    		if(currently_link) {
                // link starting with '['
    			if(c == '[') {
    				output << "LINK ";
                    string anchor = "";
    				while(c != ']') {
    					input.get(c);
    					if(c != ']') {
    						anchor = anchor + c;
    					}
    				}
    				input.get(c);
    				string link = "";
    				while(c!= ')') {
    					input.get(c);
    					if(c != ')') {
    						link = link + c;  
     					}
    				}
    				output << "(" << link << ", " << anchor << ")" << endl;
    			}
                // link starting with '('
    			else {
    				output << "LINK ";
    				string link = "";
    				while(c!=')') {
    					input.get(c);
    					if(c!=')') {
    						link = link +c;
    					}
    				}
    				output << "(" << link << ", " << link << ")" << endl;
    			}
    			currently_link = false;
    		}
            // if c is not part of a link output if a letter, if not start a new line
    		else {
    			if(isalpha(c)) {
    				output << c;
    				if(!isalpha(input.peek())) {
    					output << endl;
    				}
    			}
    		
    		}
    		
		}
    }
     // close streams
    input.close();
	output.close();
	
}


