#pragma once
#include "components.h"

// convert string to TCHAR
void string2TCHAR(std::string * pInput, TCHAR * output, const int SIZE) // SIZE of TCHAR
{
	// copies chars over
	for (int i = 0; i < pInput->length() && i < SIZE; i++) 
	{
		output[i] = pInput->at(i);
	}

	// insert null terminator
	if (SIZE > pInput->length())
	{
		output[pInput->length()] = '\0'; // if the input length is less than the TCHAR size, insernt the null terminator at the end of the copied string
	}
	else
	{
		output[SIZE - 1] = '\0'; // if the input was cut off, or filled the entire TCHAR, then insert the terminator at the end of the TCHAR
	}
}

// TCHAR to string
void TCHAR2String(TCHAR* input, const int SIZE, std::string* pOutput) // TCHAR, its size, and then output string
{
	// copies chars over
	for (int i = 0; i < SIZE && input[i] != '\0'; i++)
	{
		pOutput->push_back(input[i]);
	}
}

void TCHARClear(TCHAR* input, const int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		input[i] = 0;
	}
	input[0] = '\0';
}




// begin: solver code!

/********namespaces*******/
using namespace std;

/********function prototypes*******/
bool mult_div(vector<string>&, vector <string>);
bool sort_eq(vector<string>&, vector<string>);
void add_sub(vector<string>&, vector<string>);
void solve(vector<string>&);
vector<string> create_new_labels(vector<string>);

/********functions*******/

/*
* @summary intakes a tokenized equation and mutliplies/divides its terms
* @exception will not work correctly if two variables are multiplied (i.e. squares)
* @param token_eq an equation broken into tokens, "returns" the condensed equation
* @param label_eq an equation broken into token labels
* @return whether the equation has fully multiplied/divided or not
*/
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

			if (label_eq[i - 1] == "var" || label_eq[i + 1] == "var") {
				str_result += "x";
			}
			step = true;
		}
		else if (label_eq[i] == "/op") {
			el1 = stof(token_eq[i - 1]);
			el2 = stof(token_eq[i + 1]);
			result = el1 / el2;
			str_result = to_string(result);

			if ((label_eq[i - 1] == "var" || label_eq[i + 1] == "var") && (label_eq[i - 1] != label_eq[i + 1])) {
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

/*
* @summary intakes a multiplied equation and sorts it so variables are on one side and constants on the other
* @param token_eq a multiplied equation broken into tokens, "returns" the sorted equation
* @param label_eq a multiplied equation broken into token labels
* @return whether the equation has been fully sorted or not
*/
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

/*
* @summary intakes a sorted equation and adds its like terms
* @param token_eq a sorted equation broken into tokens, "returns" the condensed equation
* @param label_eq a sorted equation broken into token labels
*/
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

/*
* @summary intakes an added equation and solves it for the variable on the lhs
* @param token_eq an added equation broken into tokens
*/
void solve(vector<string>& token_eq) {
	float var_el = stof(token_eq[0]);
	float const_el = stof(token_eq[2]);

	const_el /= var_el;

	token_eq[0] = "x";
	token_eq[2] = to_string(const_el);
}

/*
* @summary intakes a tokenized equation and produces labels for its tokens
* @param token_eq an equation broken into tokens
* @return labels for the tokenized equation
*/
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





// solves one step of linear algebra problem
bool laStep(std::vector<std::string>* solution)
{
	// TODO: actually make this solve for the next step in a solution.

	// for example (TODO: remove this when the function is actually implemented)
	//solution->push_back("Successful laStep() call! Thanks for using the beta.");
	char delim = ' ';
	string orig_eq = solution->back();
	string result = "";
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

	// take care of * and / operations
	bool md = false;
	while (!md) {
		md = mult_div(token_eq, labels_eq);
		labels_eq = create_new_labels(token_eq);
	}

	// put consts and vars each to one side
	bool sorted = false;
	while (!sorted) {
		sorted = sort_eq(token_eq, labels_eq);
		labels_eq = create_new_labels(token_eq);
	}


	// take care of + and - operations
	while (token_eq.size() > 3) {
		add_sub(token_eq, labels_eq);
		labels_eq = create_new_labels(token_eq);
	}

	// solve
	solve(token_eq);

	for (int i = 0; i < token_eq.size();i++)
	{
		result.append(token_eq.at(i));
	}
	solution->push_back(result);

	return true;
}