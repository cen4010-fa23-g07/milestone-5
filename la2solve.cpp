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
void case3(vector<vector<string>>&, vector<vector<string>>&, string&, string&);
bool sort_eq(vector<string>&, vector<string>, string);
bool format_eq(vector<string>&, string);
void solve_x(vector<string>&);
void solve_y(vector<string>&);
bool add_sub(vector<string>&);
vector<string> create_new_labels(vector<string>);
int determine_case(vector<vector<string>>);
string trim_white(string);

/********functions*******/
void case3(vector<vector<string>>& token_eq, vector<vector<string>>& label_eq, string& x_soln, string& y_soln) {
	if (find(label_eq[0].begin(), label_eq[0].end(), "varx") != label_eq[0].end()) {
		bool x_sorted = false;
		while (!x_sorted) {
			x_sorted = sort_eq(token_eq[0], label_eq[0], "varx");
			label_eq[0] = create_new_labels(token_eq[0]);
		}

		bool x_added = false;
		while (!x_added) {
			x_added = add_sub(token_eq[0]);
			label_eq[0] = create_new_labels(token_eq[0]);
		}

		solve_x(token_eq[0]);
		x_soln = token_eq[0][2];

		bool y_sorted = false;
		while (!y_sorted) {
			y_sorted = sort_eq(token_eq[1], label_eq[1], "vary");
			label_eq[1] = create_new_labels(token_eq[1]);
		}

		bool y_added = false;
		while (!y_added) {
			y_added = add_sub(token_eq[1]);
			label_eq[1] = create_new_labels(token_eq[1]);
		}

		solve_y(token_eq[1]);
		y_soln = token_eq[1][2];

	}
	else {
		bool y_sorted = false;
		while (!y_sorted) {
			y_sorted = sort_eq(token_eq[0], label_eq[0], "vary");
			label_eq[0] = create_new_labels(token_eq[0]);
		}

		bool y_added = false;
		while (!y_added) {
			y_added = add_sub(token_eq[0]);
			label_eq[0] = create_new_labels(token_eq[0]);
		}

		solve_y(token_eq[0]);
		y_soln = token_eq[0][2];

		bool x_sorted = false;
		while (!x_sorted) {
			x_sorted = sort_eq(token_eq[1], label_eq[1], "varx");
			label_eq[1] = create_new_labels(token_eq[1]);
		}

		bool x_added = false;
		while (!x_added) {
			x_added = add_sub(token_eq[1]);
			label_eq[1] = create_new_labels(token_eq[1]);
		}

		solve_x(token_eq[1]);
		x_soln = token_eq[1][2];
	}
}

bool sort_eq(vector<string>& token_eq, vector<string> label_eq, string variable) {
	bool lhs = true;
	int pos_equals;

	for (int i = 0; i < token_eq.size(); i++) {
		if (label_eq[i] == "=op") {
			pos_equals = i;
			break;
		}
	}

	string other_var;
	if (variable == "varx") {
		other_var = "vary";
	}
	else {
		other_var = "varx";
	}

	for (int i = 0; i < token_eq.size(); i++) {
		if (label_eq[i] == "=op") {
			lhs = false;
			//pos_equals = i;
			continue;
		}

		// if on left side of =op and element is const or vary
		if (lhs && (label_eq[i] == "const" || label_eq[i] == other_var)) {
			string el = token_eq[i];
			string el_op = "null";
			// if element is not first
			if (i != 0) {
				el_op = label_eq[i - 1];
				// erase element's op
				token_eq.erase(token_eq.begin() + (i - 1));
				pos_equals--;

				// erase element
				token_eq.erase(token_eq.begin() + (i - 1));
				pos_equals--;
			}
			else {
				// erase element
				token_eq.erase(token_eq.begin() + i);
				pos_equals--;
			}

			// if const, put element & op onto end of rhs
			if (el_op == "null" || el_op == "+op") {
				token_eq.push_back("-");
			}
			else {
				token_eq.push_back("+");
			}
			token_eq.push_back(el);
			return false;
		} // end of lhs
		// if on right side of =op and element is varx
		else if (!lhs && label_eq[i] == variable) {
			string el = token_eq[i];
			string el_op = "null";

			// if element is not first after =op
			if (i != (pos_equals + 1)) {
				el_op = label_eq[i - 1];
				// erase element's op
				token_eq.erase(token_eq.begin() + (i - 1));

				// erase element
				token_eq.erase(token_eq.begin() + (i - 1));
			}
			else {
				// erase element
				token_eq.erase(token_eq.begin() + i);
			}
			// put element and op onto end of lhs
			if (el_op == "null" || el_op == "+op") {
				token_eq.insert(token_eq.begin() + (pos_equals), "-");
			}
			else {
				token_eq.insert(token_eq.begin() + (pos_equals), "+");
			}
			token_eq.insert(token_eq.begin() + (pos_equals + 1), el);

			return false;
		}	// end of rhs
	}	// end of for

	// if nothing on lhs
	if (pos_equals == 0 && variable == "varx") {
		token_eq.insert(token_eq.begin(), "0x");
	}
	else if (pos_equals == 0 && variable == "vary") {
		token_eq.insert(token_eq.begin(), "0y");
	}
	// if nothing on rhs
	if (pos_equals == (token_eq.size() - 1)) {
		token_eq.push_back("0");
	}

	// get rid of ops of first elements on sides
	if (label_eq[0] == "+op") {
		token_eq.erase(token_eq.begin());
		return false;
	}
	else if (label_eq[0] == "-op") {
		string el = "-";
		el += token_eq[1];

		token_eq[1] = el;
		token_eq.erase(token_eq.begin());
		return false;
	}

	if (label_eq[pos_equals + 1] == "+op") {
		token_eq.erase(token_eq.begin() + (pos_equals + 1));
	}
	else if (label_eq[pos_equals + 1] == "-op") {
		string el = "-";
		el += token_eq[pos_equals + 2];

		token_eq[pos_equals + 2] = el;
		token_eq.erase(token_eq.begin() + (pos_equals + 1));
	}

	bool formatted = false;
	while (!formatted) {
		formatted = format_eq(token_eq, variable);
	}
	
	return true;
}

bool format_eq(vector<string>& token_eq, string variable) {
	bool ret = true;
	vector<string> label_eq = create_new_labels(token_eq);

	int pos_equals;
	for (int i = 0; i < token_eq.size(); i++) {
		if (label_eq[i] == "=op") {
			pos_equals = i;
			break;
		}
	}

	string other_var;
	if (variable == "varx") {
		other_var = "vary";
	}
	else {
		other_var = "varx";
	}

	// insert + before first element after =op
	token_eq.insert(token_eq.begin() + (pos_equals + 1), "+");
	label_eq = create_new_labels(token_eq);

	for (int i = 0; i < token_eq.size(); i++) {
		cout << token_eq[i] << "\t";
	}
	cout << endl;

	// from first element after =op, ensure other var and consts are grouped together
	for (int i = pos_equals + 1; i < token_eq.size(); i++) {
		// if element is vary and not first
		if (label_eq[i] == other_var && i != pos_equals + 1) {
			if (label_eq[i - 2] == "const") {
				cout << "i is " << i << ", pos is " << pos_equals + 1 << endl;
				string el = token_eq[i];
				string el_op = token_eq[i - 1];
				// erase op
				token_eq.erase(token_eq.begin() + (i - 1));
				// erase el
				token_eq.erase(token_eq.begin() + (i - 1));
				// insert just after =op
				token_eq.insert(token_eq.begin() + (pos_equals + 1), el);
				token_eq.insert(token_eq.begin() + (pos_equals + 1), el_op);
				ret = false;
				break;
			}
		}
	}

	label_eq = create_new_labels(token_eq);

	// get rid of any ops before element & after =op
	if (label_eq[pos_equals + 1] == "+op") {
		token_eq.erase(token_eq.begin() + (pos_equals + 1));
	}
	else if (label_eq[pos_equals + 1] == "-op") {
		string el = "-";
		el += token_eq[pos_equals + 2];

		token_eq[pos_equals + 2] = el;
		token_eq.erase(token_eq.begin() + (pos_equals + 1));
	}

	if (ret == true) {
		return true;
	}
	else {
		return false;
	}
}

void solve_x(vector<string>& token_eq) {
	float x_el = stof(token_eq[0]);
	float const_el, y_el;

	// if two variables
	if (token_eq.size() == 5) {
		cout << "two vars" << endl;
		y_el = stof(token_eq[2]);
		const_el = stof(token_eq[4]);

		y_el /= x_el;
		const_el /= x_el;

		token_eq[2] = to_string(y_el);
		token_eq[2] += "y";
		token_eq[4] = to_string(const_el);
	}
	// else if one variable
	else {
		const_el = stof(token_eq[2]);

		const_el /= x_el;
		token_eq[2] = to_string(const_el);
	}

	token_eq[0] = "x";
}

void solve_y(vector<string>& token_eq) {
	float y_el = stof(token_eq[0]);
	float const_el, x_el;

	// if two variables
	if (token_eq.size() == 5) {
		x_el = stof(token_eq[2]);
		const_el = stof(token_eq[4]);

		x_el /= y_el;
		const_el /= y_el;

		token_eq[2] = to_string(x_el);
		token_eq[2] += "x";
		token_eq[4] = to_string(const_el);
	}
	// else if one variable
	else {
		const_el = stof(token_eq[2]);

		const_el /= y_el;
		token_eq[2] = to_string(const_el);
	}

	token_eq[0] = "y";
}

bool add_sub(vector<string>& token_eq) {
	vector<string> label_eq = create_new_labels(token_eq);

	for (int i = 1; i < token_eq.size(); i++) {
		float el1, el2, result;
		string str_result;
		bool step = false;
		// if const + const or var + var
		if (label_eq[i] == "+op" && label_eq[i - 1] == label_eq[i + 1]) {
			el1 = stof(token_eq[i - 1]);
			el2 = stof(token_eq[i + 1]);
			result = el1 + el2;
			str_result = to_string(result);
			if (label_eq[i - 1] == "varx") {
				str_result += "x";
			}
			else if (label_eq[i - 1] == "vary") {
				str_result += "y";
			}
			step = true;
		}
		else if (label_eq[i] == "-op" && label_eq[i - 1] == label_eq[i + 1]) {
			el1 = stof(token_eq[i - 1]);
			el2 = stof(token_eq[i + 1]);
			result = el1 - el2;
			str_result = to_string(result);
			if (label_eq[i - 1] == "varx") {
				str_result += "x";
			}
			else if (label_eq[i - 1] == "vary") {
				str_result += "y";
			}
			step = true;
		}

		if (step) {
			token_eq.erase(token_eq.begin() + (i - 1));
			token_eq.erase(token_eq.begin() + (i - 1));
			token_eq.erase(token_eq.begin() + (i - 1));
			token_eq.insert(token_eq.begin() + (i - 1), str_result);
			//break;
			return false;
		}

	}

	return true;
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
	string orig_input = "3x + 3 = 2x, 5y + 10y = -18";
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

	string x_soln, y_soln;

	if (eq_case == 1) {
		//case1();
	}
	else if (eq_case == 2) {
		//case2();
	}
	else {
		case3(token_eq, labels_eq, x_soln, y_soln);
	}

	cout << "x = " << x_soln << endl;
	cout << "y = " << y_soln << endl;

	///*************test****************/
	//bool sorted = false;
	//while (!sorted) {
	//	sorted = sort_eq(token_eq[0], labels_eq[0], "vary");
	//	labels_eq[0] = create_new_labels(token_eq[0]);
	//}

	//for (int i = 0; i < token_eq[0].size(); i++) {
	//	cout << token_eq[0][i] << "\t";
	//}
	//cout << endl;
	//for (int i = 0; i < labels_eq[0].size(); i++) {
	//	cout << labels_eq[0][i] << "\t";
	//}
	//cout << endl;

	//bool added = false;
	//while (!added) {
	//	added = add_sub(token_eq[0]);
	//	labels_eq[0] = create_new_labels(token_eq[0]);
	//}

	//for (int i = 0; i < token_eq[0].size(); i++) {
	//	cout << token_eq[0][i] << "\t";
	//}
	//cout << endl;
	//for (int i = 0; i < labels_eq[0].size(); i++) {
	//	cout << labels_eq[0][i] << "\t";
	//}
	//cout << endl;

	//solve_x(token_eq[0]);
	//for (int i = 0; i < token_eq[0].size(); i++) {
	//	cout << token_eq[0][i] << "\t";
	//}
	//cout << endl;
}
