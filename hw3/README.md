Directory contains the following source and header files: 

lib/alistint.h: 
	Header file for AListInt class. Behavior of functions is described in the documentation.

src/alistint.cpp
	Source file for AListInt class. Behavior of functions is described in documentation for alistint.h as well as documentation of alistint.cpp.

	To compile into object code: make alistint

src/alisttest.cpp
	Unit testing of the class AlistInt. Uses Google Test.

	To compile: make alisttest

lib/stackint.h
	Header file for StackInt class. Functions are described in the documentation.

src/stackint.cpp
	Source file for StackInt class. Functions are described in the documentation of stackint.h.

	To compile into object code: make stackint

src/stackinttest.cpp
	Program that tests stackint class. If only outputs "done", tests have succeeded.

	To compile: make stackinttest

src/boolevaluator
	Program to evaluate bool expressions. Expects two command line arguements: first the file of expressions, second an assignment file. Reads formulas and outputs "T", "F", "Malformed", or "Unkown Variable" for each.

	To compile: make boolevaluator

Directory also contains the answers to problem 4 in problem4.txt