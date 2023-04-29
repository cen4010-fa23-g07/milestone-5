// lasolve_new.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/********include directives*******/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

/********namespaces*******/
using namespace std;

/********function prototypes*******/
bool mult_div(vector<string>&, vector <string>);
bool sort_eq(vector<string>&, vector<string>);
void add_sub(vector<string>&, vector<string>);
void solve(vector<string>&);
vector<string> create_new_labels(vector<string>);

/********functions*******/
bool mult_div(vector<string>& token_eq, vector<string> label_eq) {
	for (int i = 1; i < token_eq.size(); i++) {
		float el1, el2, result;
		string str_result;
		bool step = false;

		if (label_eq[i] == "*op") {
			el1 = stof(token_eq[i - 1]);
			el2 = stof(token_eq[i + 1]);
			result = el1 * el2;
			str_result = to_string(result);

			if (label_eq[i-1] == "var" || label_eq[i+1] == "var") {
				str_result += "x";
			}
			step = true;
		}
		else if (label_eq[i] == "/op") {
			el1 = stof(token_eq[i - 1]);
			el2 = stof(token_eq[i + 1]);
			result = el1 / el2;
			str_result = to_string(result);

			if ( (label_eq[i - 1] == "var" || label_eq[i + 1] == "var") && (label_eq[i - 1] != label_eq[i + 1]) ) {
				str_result += "x";
			}
			step = true;
		}

		if (step) {
			token_eq.erase(token_eq.begin() + (i - 1));
			token_eq.erase(token_eq.begin() + (i - 1));
			token_eq.erase(token_eq.begin() + (i - 1));
			token_eq.insert(token_eq.begin() + (i - 1), str_result);
			return false;
		}
	}
	return true;
}

bool sort_eq(vector<string>& token_eq, vector<string> label_eq) {
	bool lhs = true;
	int pos_equals;

	for (int i = 0; i < token_eq.size(); i++) {
		if (label_eq[i] == "=op") {
			lhs = false;
			pos_equals = i;
			continue;
		}

		// if on the left of =op and element is a const
		if (lhs && label_eq[i] == "const") {
			string el = token_eq[i];
			string el_label = label_eq[i];
			string el_op = "null";
			// if element is not first
			if (i != 0) {
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

			// put element & op onto end of rhs
			if (el_op == "null" || el_op == "+op") {
				token_eq.push_back("-");
			}
			else {
				token_eq.push_back("+");
			}
			token_eq.push_back(el);
			// end not successfully reached
			return false;
		}	// end of lhs && const
		// if on right side of =op and element is a var
		else if (!lhs && label_eq[i] == "var") {
			string el = token_eq[i];
			string el_label = label_eq[i];
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
			// end not successfully reached
			return false;
		}	// end of rhs && var
	}	// end of for

	// if nothing on lhs
	if (pos_equals == 0) {
		token_eq.insert(token_eq.begin(), "0x");
	}
	// if nothing on rhs
	else if (pos_equals == (token_eq.size() - 1)) {
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

	return true;
}

void add_sub(vector<string>& token_eq, vector<string> label_eq) {
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
			if (label_eq[i - 1] == "var") {
				str_result += "x";
			}
			step = true;
		}
		else if (label_eq[i] == "-op" && label_eq[i - 1] == label_eq[i + 1]) {
			el1 = stof(token_eq[i - 1]);
			el2 = stof(token_eq[i + 1]);
			result = el1 - el2;
			str_result = to_string(result);
			if (label_eq[i - 1] == "var") {
				str_result += "x";
			}
			step = true;
		}

		if (step) {
			token_eq.erase(token_eq.begin() + (i - 1));
			token_eq.erase(token_eq.begin() + (i - 1));
			token_eq.erase(token_eq.begin() + (i - 1));
			token_eq.insert(token_eq.begin() + (i - 1), str_result);
			break;
		}

	}
}

void solve(vector<string>& token_eq) {
	float var_el = stof(token_eq[0]);
	float const_el = stof(token_eq[2]);

	const_el /= var_el;

	token_eq[0] = "x";
	token_eq[2] = to_string(const_el);
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
			labels[i] = "var";
		}
		else {
			labels[i] = "const";
		}
	}

	return labels;
}

/********driver*******/
int main()
{
	string orig_eq = "- 3 + 5x / 5x = 5x";
	char delim = ' ';
	stringstream ss(orig_eq);

	// holds separated equation
	vector<string> token_eq;
	while (getline(ss, orig_eq, delim)) {
		token_eq.push_back(orig_eq);
	}

	for (int i = 0; i < token_eq.size(); i++) {
		cout << token_eq[i] << "\t";
	}
	cout << endl;

	// holds labels for each element in separated equation
	vector<string> labels_eq = create_new_labels(token_eq);

	for (int i = 0; i < labels_eq.size(); i++) {
		cout << labels_eq[i] << "\t";
	}
	cout << endl;
	
	// take care of * and / operations
	bool md = false;
	while (!md) {
		md = mult_div(token_eq, labels_eq);
		labels_eq = create_new_labels(token_eq);
	}

	for (int i = 0; i < token_eq.size(); i++) {
		cout << token_eq[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < labels_eq.size(); i++) {
		cout << labels_eq[i] << "\t";
	}
	cout << endl;

	// put consts and vars each to one side
	bool sorted = false;
	while (!sorted) {
		sorted = sort_eq(token_eq, labels_eq);
		labels_eq = create_new_labels(token_eq);
	}

	for (int i = 0; i < token_eq.size(); i++) {
		cout << token_eq[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < labels_eq.size(); i++) {
		cout << labels_eq[i] << "\t";
	}
	cout << endl;


	// take care of + and - operations
	while (token_eq.size() > 3) {
		add_sub(token_eq, labels_eq);
		labels_eq = create_new_labels(token_eq);
	}

	for (int i = 0; i < token_eq.size(); i++) {
		cout << token_eq[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < labels_eq.size(); i++) {
		cout << labels_eq[i] << "\t";
	}
	cout << endl;

	// solve
	solve(token_eq);

	for (int i = 0; i < token_eq.size(); i++) {
		cout << token_eq[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < labels_eq.size(); i++) {
		cout << labels_eq[i] << "\t";
	}
	cout << endl;
}

