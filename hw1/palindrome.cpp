#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;

// to be defined later
void makePalindromes(ostream& ofile, char* options, int size);
void makePalindromeHelper(ostream& ofile, char* options, int len, int size, string pal);

int main(int argc, char* argv[])
{
	//check for correct number of command line arguements
  if(argc < 4){
    cerr << "Please provide an output file, a string of characters, and the max length" << endl;
    return 1;
  }


  ofstream ofile(argv[1]);
  int len = atoi(argv[3]);
  makePalindromes(ofile, argv[2], len);
  ofile.close();
  return 0;
}
 
void makePalindromes(ostream& ofile, char* options, int size) {
	string letters(options);
	// call helper function for empty string
	makePalindromeHelper(ofile, options, 0, size, "");
	int length = letters.length();

	// call helper function for each letter given in command line arguement
	for(int i=0; i<length; i++) {
		string s;
		s.push_back(options[i]);
		makePalindromeHelper(ofile, options, 1, size, s);
	}

}

void makePalindromeHelper(ostream& ofile, char* options, int len, int size, string pal) {
	// output given palindrome
	ofile << pal << endl;

	// for each letter given recursively call function for letter + pal + letter
	string letters(options);
	int length = letters.length();
	if(len+2 <=size) {
		for(int i=0; i<length; i++)	{
			string s;
			s.push_back(options[i]);
			string palin = s + pal + s;
	
			makePalindromeHelper(ofile, options, len+2, size, palin);
		}
	}
}