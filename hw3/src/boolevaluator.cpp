#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>

#include "../lib/stackint.h"

using namespace std;

const int AND = -1;
const int OR = -2;
const int NOT = -3;
const int LEFT_PAREN = -4;
const int RIGHT_PAREN = -5;
const int BAD_SUBF = -10;
const int EMPTY_SUBF = -11;

bool parseVariables(char* file, map<int, bool>& variables);
void parseFormula(string formula, map<int, bool> const & variables);
int eval_subFormula(int * formula, int size);
int operation(int* formula, int start, int end, int o_index);
int final_eval(int* formula, int size);

int main(int argc, char* argv[]) {
	if(argc != 3) {
		cout << "Please provide two command line arguements: First the name of formula file then name of variable file" << endl;
		return 1;
	}

	map<int, bool> vars;
	bool parsed = parseVariables(argv[2], vars);
	if(!parsed) {
		cout << "Could not find input file" << endl;
		return 1;
	}

	

	ifstream for_file(argv[1]);
	if(for_file.fail()) {
		cout << "Could not find formula file" << endl;
	}
	while(!for_file.fail()) {
		string line;
		getline(for_file, line);
		if(!for_file.fail())
			parseFormula(line, vars);

	}

	return 0;
}

bool parseVariables(char* file, map<int, bool>& variables) {
	ifstream var_file(file);
	if(var_file.fail()) {
		return false;
	}

	while(!var_file.fail()) {
		int key;
		var_file >> key;
		char v;
		var_file >> v;
		bool value;
		if(v == 'T' || v == 't') 
			value = true;
		else
			value = false;
		if(!var_file.fail())
			variables.insert(make_pair(key, value));

	}

	return true;
}
void parseFormula(string formula, map<int, bool> const & variables) {
	if(formula.empty())
		return;
	StackInt stack;
	string::iterator it;
	int subf_size = 0;
	for(it = formula.begin(); it != formula.end(); ++it) {
		char c = (*it);
		if(c==' '){}
		else if(isdigit(c)) {
			string num = "";
			num += c;
			while(isdigit(c) && it != formula.end()) {
				++it;
				if(it != formula.end()) {
					c = (*it);
					if(isdigit(c)) {
						num += c;
					}
				}
			}
			--it;
			int var = atoi(num.c_str());
			if(variables.find(var) != variables.end()) {

				stack.push(variables.find(var)->second);
				subf_size++;
			}
			else {
				cout << "Unkown Variable" << endl;
				return;
			}
		}
		else if(c=='F') {
			stack.push(0);
			subf_size++;
		}
		else if(c == 'T'){
			stack.push(1);
			subf_size++;
		}
		else if(c=='&') {
			stack.push(AND);
			subf_size++;
		}
		else if(c=='|') {
			stack.push(OR);
			subf_size++;
		}
		else if(c=='~') {
			stack.push(NOT);
			subf_size++;
		}
		else if(c=='(') {
			stack.push(LEFT_PAREN);
			subf_size++;
		}
		else if(c==')') {
			int save_size = subf_size;
			int* subfunc = new int[subf_size];
			int count = 0;
			int t = 0;
			while(!stack.empty()) {
				t = stack.top();
				subf_size--;
				stack.pop();
				if(t==LEFT_PAREN) {
					break;
				}
				else {
					subfunc[count] = t;
					count++;
				}
			}
			if(t!=LEFT_PAREN) {
				cout << "Malformed" << endl;
				delete[] subfunc;
				return;
			}
			int* reversed = new int[save_size];
			for(int i = count-1; i >= 0; i--) {
				reversed[i] = subfunc[count-1-i];
			}
			int* p_temp = subfunc;
			subfunc = reversed;
			delete[] p_temp;
			int temp = eval_subFormula(subfunc, count);
			delete[] subfunc;
			if(temp == BAD_SUBF) {
				cout << "Malformed" << endl;
				return;
			}

			stack.push(temp);
			subf_size++;
		}
	}

	if(stack.empty()) {
		cout << "Malformed" << endl;
		return;
	}
	int last = stack.top();
	stack.pop();
	if(stack.empty()) {
		if(last == 0)
			cout << "F" << endl;
		else if(last == 1)
			cout << "T" << endl;
		else
			cout << "Malformed" << endl;
		return;
	}
	int * subf = new int[subf_size];
	int count = subf_size;
	count--;
	subf[count] = last;
	while(!stack.empty()) {
		int t = stack.top();
		stack.pop();
		count--;
		subf[count] = t;
	}
	int answer = final_eval(subf, subf_size);
	delete[] subf;
	if(answer== BAD_SUBF)
		cout << "Malformed" << endl;
	else if(answer == 0)
		cout << "F" << endl;
	else
		cout << "T" << endl;
}



int eval_subFormula(int* formula, int size) {
	if(size == 0) {
		return BAD_SUBF;
	}
	if(size == 1) {
		return BAD_SUBF;
	}
	int oper = false;
	int lastoper = 0;
	int o_index = -1;
	int used_operator = -90;
	for(int i = 0; i < size; i++) {
		if(oper) {
			 if(formula[i] == 0 || formula[i] == 1) {
				int start = lastoper;
				int end = i;


				formula[i] = operation(formula, start, end, o_index);
				if(formula[i] == BAD_SUBF)
					return BAD_SUBF;
				lastoper = i;
				oper = false;
			}
			else if(formula[i] != NOT) {
				return BAD_SUBF;
			}
		} 
		else {
			if(formula[i] == AND || formula[i] == OR) {
				oper = true;
				o_index = i;
				if(used_operator != -90) {
					if(used_operator != formula[i])
						return BAD_SUBF;
				}
				else
					used_operator = formula[i]; 
			}
		}
	}
	if(o_index == -1) {
		return BAD_SUBF;
	}
	if(oper) {
		return BAD_SUBF;
	}
	if(lastoper == size - 1) {
		return formula[size - 1];
	}

	int start = lastoper;
	return operation(formula, start, size-1, o_index);
	
}


int n(int i, int num_nots) {

	if(num_nots%2 == 0) {
		return i;
	}
	else
		return !i;
}

int a(int i, int y) {

	return (int)(i&&y);
}

int o(int i, int y) {

	return (int)(i||y);
}

int final_eval(int* formula, int size) {
	int num_nots= 0;
	for(int i =0; i <= size-2; ++i) {

		if(formula[i] != NOT) {

			return BAD_SUBF;
		}
		num_nots++;
	}

	if((formula[size-1] == 1) || (formula[size-1] == 0)) {

		int answer = n(formula[size-1], num_nots);
		return answer;
	}
	else {

		return BAD_SUBF;
	}


}

int operation(int * formula, int start, int end, int o_index) {
	int left = -100;
	int num_nots1 = 0;
	for(int i = start; i < o_index; ++i) {
		if(formula[i] == 0 || formula[i] == 1) {
			if(left != -100)
				return BAD_SUBF;
			left = formula[i];
		}
		else
			num_nots1++;
	}
	if(left == -100) {
		return BAD_SUBF;
	}
	if(num_nots1 != 0) {
		left = n(left, num_nots1);
	}

	int right = -100;
	int num_nots2 = 0;
	for(int i = o_index+1; i <= end; i++) {
		if(formula[i] == 0 || formula[i] == 1) {
			if(right != -100)
				return BAD_SUBF;
			right = formula[i];
		}
		else 
			num_nots2++;
	}
	if(right == -100) {
		return BAD_SUBF;
	}
	if(num_nots2 != 0) {
		right = n(right, num_nots2);
	}


	if(formula[o_index] == AND) {
		return a(left, right);
	}
	if(formula[o_index] == OR) {
		return o(left, right);
	}
	else
		return BAD_SUBF;
}