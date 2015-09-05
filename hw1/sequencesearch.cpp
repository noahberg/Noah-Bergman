#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
	// check if number of arguements is correct
   if(argc != 3) {
      cout << "Wrong number of command line arguements" << endl;
      return 1;
    }
    
   // check if valid input file given 
   ifstream input(argv[1]);
   if(input.fail()) {
      cout << "Could not find input file" << endl;
      return 1;
    }

    // read in number of rows from test file
    int nRows;
    input >> nRows;

    // create 2d array of length nRows
    double** grid = new double*[nRows+1];
    // initialize first row of grid with lengths of other rows
    grid[0] = new double[nRows]; 
    for(int i=0; i<nRows; ++i) {
    	int nCol; 
    	input >> nCol;
    	grid[0][i] = nCol;
    
    }

    // initialize grid with input from file
    for(int i=1; i<nRows+1; ++i) {
    	int length = grid[0][i-1];
    	grid[i] = new double[length]; 
    	for(int j=0; j<length; ++j) {
    		double num;
    		input >> num; 
    		grid[i][j] = num;
    		
    	}

    }
    
    // max strictly increasing sequence for whole grid
    int max_grid = 0;
   
   /*
   		nested for loops to find longest strictly increasing sequence 
   		moving through rows left to right
   	*/
    for(int i=1; i<nRows+1; ++i) {
    	int max_row = 0;
    	// current streak of increasing numbers
    	int current_streak;
    	double length = grid[0][i-1];
    	double prev;
    	for(int j =0; j<length; ++j) {
    		if(j==0) {
    			current_streak = 1;
    		}
    		else{
    			if(grid[i][j] > prev) {
    				current_streak++;
    			}
    			else {
    				current_streak = 1;
    			}
    		}
    		if(current_streak > max_row) {
    			max_row = current_streak;
    		}
    		prev = grid[i][j];
    		

    	}

    	if(max_row > max_grid)
    		max_grid = max_row;

    }

 	/*
 		nested for loops to find largest increasing sequecnce
 		moving through rows from right to left
 	*/
    for(int i=1; i<nRows+1; ++i) {
    	int max_row = 0;
    	// current streak of increasing numbers
    	int current_streak;
    	double length = grid[0][i-1];
    	double prev;
    	for(int j =length-1; j>=0; --j) {
    		if(j==length-1) {
    			current_streak = 1;
    		}
    		else{
    			if(grid[i][j] > prev) {
    				current_streak++;
    			}
    			else {
    				current_streak = 1;
    			}
    		}
    		if(current_streak > max_row) {
    			max_row = current_streak;
    		}
    		prev = grid[i][j];
    		


    	}
    	
    	if(max_row > max_grid)
    		max_grid = max_row;
    }

    // find longest length of rows for next loop
    int max_length = 0;
    for(int i=0; i<nRows; i++) {
    	if(grid[0][i] > max_length)
    		max_length = grid[0][i];
    }
    
    /*
    	nested for loops to find largest strictly increasing sequence 
    	moving both up and down columns
    */
    for(int i=0; i<max_length; ++i) {
    	int max_row_in = 0;
    	int max_row_de = 0;
    	// current streak of increasing numbers moving down columns
    	int current_streak_in;
    	// current streak moving up columns
    	int current_streak_de;
    	double prev;
    	bool isFirst = true;
    	for(int j =1; j<nRows+1; j++) {

    		if(isFirst)  {
    			current_streak_in=1;
    			current_streak_de=1;
    			// check if row has number in this column
    			if(i<grid[0][j-1]) {
    				prev = grid[j][i];
    				isFirst = false;
    			}
    			
    		}
    		else {
    			// check if row has number in this column
    			if(i < grid[0][j-1]) {
    				
    				if(grid[j][i] > prev) {
    					current_streak_in++;
    				}
    				else 
    					current_streak_in = 1;
    				if(grid[j][i] < prev) {
    					current_streak_de++;
    					
    				}
    				else
    					current_streak_de=1;
    				prev = grid[j][i];
    				
    			}
    		}
    		if(current_streak_in>max_row_in) {
    			max_row_in = current_streak_in;
    		}
    		if(current_streak_de>max_row_de) {
    			max_row_de = current_streak_de;
    		}
    		
    	
    	}
    	if(max_row_de > max_grid) {
    		max_grid = max_row_de;
    	}
    	if(max_row_in > max_grid) {
    		max_grid = max_row_in;
    	}
    	
    }  
   
   ofstream output(argv[2]);
   output << max_grid;

   // delete dynamically allocated array
    for(int i=0; i<nRows+1; ++i) {
    	delete[] grid[i];
    }
    delete grid;

    // close streams
    output.close();
    input.close();
		      
}
