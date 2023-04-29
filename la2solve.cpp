// la2solve.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/********include directives*******/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

/********namespaces*******/
using namespace std;

/********function prototypes*******/
void case3(vector<vector<string>>, vector<vector<string>>);
vector<string> create_new_labels(vector<string>);
int determine_case(vector<vector<string>>);
string trim_white(string);

/********functions*******/
void case3(vector<vector<string>>& token_eq, vector<vector<string>>& label_eq) {
	if (find(label_eq[0].begin(), label_eq[0].end(), "varx") != label_eq[0].end()) {
		//sort_x(token_eq[0]);
		//solve_x(token_eq[0]);
		//sort_y(token_eq[1]);
		//solve_y(token_eq[1]);
	}
	else {
		//sort_y(token_eq[0]);
		//solve_y(token_eq[0]);
		//sort_x(token_eq[1]);
		//solve_x(token_eq[1]);
	}
}

vector<string> create_new_labels(vector<string> token_eq) {
	vector<string> labels(token_eq.size());

	for (int i = 0; i < token_eq.size(); i++) {
		if (token_eq[i] == "*") {
			labels[i] = "*op";
		}
		else if (token_eq[i] == "/") {
			labels[i] = "/op";
		}
		else if (token_eq[i] == "+") {
			labels[i] = "+op";
		}
		else if (token_eq[i] == "-") {
			labels[i] = "-op";
		}
		else if (token_eq[i] == "=") {
			labels[i] = "=op";
		}
		else if (token_eq[i].find("x") != string::npos) {
			labels[i] = "varx";
		}
		else if (token_eq[i].find("y") != string::npos) {
			labels[i] = "vary";
		}
		else {
			labels[i] = "const";
		}
	}

	return labels;
}

int determine_case(vector<vector<string>> labels_eq) {
	int eq_case = 0;
	bool eq_x[2] = { 0 };
	bool eq_y[2] = { 0 };

	for (int i = 0; i < labels_eq[0].size(); i++) {
		if (labels_eq[0][i] == "varx") {
			eq_x[0] = true;
		}
		else if (labels_eq[0][i] == "vary") {
			eq_y[0] = true;
		}
	}
	for (int i = 0; i < labels_eq[1].size(); i++) {
		if (labels_eq[1][i] == "varx") {
			eq_x[1] = true;
		}
		else if (labels_eq[1][i] == "vary") {
			eq_y[1] = true;
		}
	}

	if (eq_x[0] == 1 && eq_y[0] == 0) {
		if (eq_x[1] == 0 && eq_y[1] == 1) {
			eq_case = 3;
		}
		else if (eq_x[1] == 1 && eq_y[1] == 1) {
			eq_case = 2;
		}
	}
	else if (eq_x[0] == 0 && eq_y[0] == 1) {
		if (eq_x[1] == 1 && eq_y[1] == 0) {
			eq_case = 3;
		}
		else if (eq_x[1] == 1 && eq_y[1] == 1) {
			eq_case = 2;
		}
	}
	else {
		eq_case = 1;
	}

	return eq_case;
}

string trim_white(string str) {
	str.erase(str.find_last_not_of(" ") + 1);
	str.erase(0, str.find_first_not_of(" "));
	return str;
}

/********driver*******/
int main()
{
	string orig_input = "3x + 2 = 5, 5y + 10y = -18";
	char delim_sys = ',';
	stringstream ss_sys(orig_input);

	// separate equations
	vector<string> equations;
	while (getline(ss_sys, orig_input, delim_sys)) {
		equations.push_back(orig_input);
	}

	// trim whitespace
	for (int i = 0; i < equations.size(); i++) {
		equations[i] = trim_white(equations[i]);
	}

	for (int i = 0; i < equations.size(); i++) {
		cout << equations[i] << endl;
	}

	// separate individual equations into tokens
	char delim_ind = ' ';
	stringstream ss_ind_1(equations[0]);
	stringstream ss_ind_2(equations[1]);

	vector<vector<string>> token_eq(2);
	while (getline(ss_ind_1, equations[0], delim_ind)) {
		token_eq[0].push_back(equations[0]);
	}
	while (getline(ss_ind_2, equations[1], delim_ind)) {
		token_eq[1].push_back(equations[1]);
	}

	// hold labels for each element in separated equation
	vector<vector<string>> labels_eq(2);
	for (int i = 0; i < token_eq.size(); i++) {
		labels_eq[i] = create_new_labels(token_eq[i]);
	}

	for (int i = 0; i < labels_eq[0].size(); i++) {
		cout << labels_eq[0][i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < labels_eq[1].size(); i++) {
		cout << labels_eq[1][i] << "\t";
	}
	cout << endl;

	// determine which case
	// case 1: both equations contain x & y
	// case 2: one equation contains one variable, the other contains both
	// case 3: each equation contains a separate variable
	int eq_case = determine_case(labels_eq);
	cout << eq_case << endl;

	if (eq_case == 1) {
		//case1();
	}
	else if (eq_case == 2) {
		//case2();
	}
	else {
		case3(token_eq, labels_eq);
	}
}
