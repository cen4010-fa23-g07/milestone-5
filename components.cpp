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




// begin: single solver code!

/********namespaces*******/
using namespace std;

/********function prototypes*******/
bool mult_div(vector<string>&, vector <string>);
bool sort_eq(vector<string>&, vector<string>);
void add_sub(vector<string>&, vector<string>);
void solve(vector<string>&);
vector<string> create_new_labels0(vector<string>);

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
vector<string> create_new_labels0(vector<string> token_eq) {
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





// solves all steps of linear algebra problem
void laSolve(std::vector<std::string>* solution)
{
	char delim = ' ';
	string orig_eq = solution->back();
	string result = "";
	stringstream ss(orig_eq);

	// holds separated equation
	vector<string> token_eq;
	while (getline(ss, orig_eq, delim)) {
		token_eq.push_back(orig_eq);
	}

	// holds labels for each element in separated equation
	vector<string> labels_eq = create_new_labels0(token_eq);

	// take care of * and / operations
	bool md = false;
	while (!md) {
		md = mult_div(token_eq, labels_eq);
		labels_eq = create_new_labels0(token_eq);
	}
	for (int i = 0; i < token_eq.size(); i++)
	{
		result.append(token_eq.at(i));
	}
	solution->push_back(result);
	result.clear();

	// put consts and vars each to one side
	bool sorted = false;
	while (!sorted) {
		sorted = sort_eq(token_eq, labels_eq);
		labels_eq = create_new_labels0(token_eq);
	}

	for (int i = 0; i < token_eq.size(); i++)
	{
		result.append(token_eq.at(i));
	}
	solution->push_back(result);
	result.clear();

	// take care of + and - operations
	while (token_eq.size() > 3) {
		add_sub(token_eq, labels_eq);
		labels_eq = create_new_labels0(token_eq);
	}
	for (int i = 0; i < token_eq.size(); i++)
	{
		result.append(token_eq.at(i));
	}
	solution->push_back(result);
	result.clear();
	// solve
	solve(token_eq);

	for (int i = 0; i < token_eq.size();i++)
	{
		result.append(token_eq.at(i));
	}
	solution->push_back(result);
	result.clear();
}


// begin double solver code

/********function prototypes*******/
void case1(vector<vector<string>>&, vector<vector<string>>&, string&, string&, std::vector<std::string>* solution);
void case2(vector<vector<string>>&, vector<vector<string>>&, string&, string&, std::vector<std::string>* solution);
void case3(vector<vector<string>>&, vector<vector<string>>&, string&, string&, std::vector<std::string>* solution);
void sort_add_solve(vector<string>&, vector<string>&, string);
bool sort_eq(vector<string>&, vector<string>, string);
bool format_eq(vector<string>&, string);
void solve_eq(vector<string>&, string);
bool add_sub(vector<string>&);
vector<string> create_new_labels(vector<string>);
int determine_case(vector<vector<string>>);
string trim_white(string);

/********functions*******/

/*
* @summary solves 2 equations in the case where both contain 2 variables
* @param token_eq the two equations broken into tokens
* @param label_eq the two equations broken into token labels
* @param x_soln "returns" the answer to x
* @param y_soln "returns" the answer to y
*/
void case1(vector<vector<string>>& token_eq, vector<vector<string>>& label_eq, string& x_soln, string& y_soln, std::vector<std::string>* solution) {
	string result;
	
	// isolate x in first equation
	sort_add_solve(token_eq[0], label_eq[0], "varx");

	// isoalte x in second equation
	sort_add_solve(token_eq[1], label_eq[1], "varx");

	// magic solution grabber -v
	for (int i = 0; i < token_eq[0].size(); i++)
	{
		result.append(token_eq[0][i]);
	}
	result.push_back(';');
	for (int i = 0; i < token_eq[1].size(); i++)
	{
		result.append(token_eq[1][i]);
	}
	solution->push_back(result);
	result.clear();
	// magic solution grabber -^


	// plug solution from first equation into second equation
	cout << "plug into second eq" << endl;
	token_eq[1].erase(token_eq[1].begin());
	token_eq[1].insert(token_eq[1].begin(), token_eq[0][4]);
	token_eq[1].insert(token_eq[1].begin(), token_eq[0][3]);
	token_eq[1].insert(token_eq[1].begin(), token_eq[0][2]);
	label_eq[1] = create_new_labels(token_eq[1]);

	// magic solution grabber -v
	for (int i = 0; i < token_eq[0].size(); i++)
	{
		result.append(token_eq[0][i]);
	}
	result.push_back(';');
	for (int i = 0; i < token_eq[1].size(); i++)
	{
		result.append(token_eq[1][i]);
	}
	solution->push_back(result);
	result.clear();
	// magic solution grabber -^

	// solve for y in second equation
	sort_add_solve(token_eq[1], label_eq[1], "vary");
	y_soln = token_eq[1][2];
	cout << "y = " << y_soln << endl;

	// magic solution grabber -v
	for (int i = 0; i < token_eq[0].size(); i++)
	{
		result.append(token_eq[0][i]);
	}
	result.push_back(';');
	for (int i = 0; i < token_eq[1].size(); i++)
	{
		result.append(token_eq[1][i]);
	}
	solution->push_back(result);
	result.clear();
	// magic solution grabber -^

	// isolate y in first equation
	sort_add_solve(token_eq[0], label_eq[0], "vary");

	// magic solution grabber -v
	for (int i = 0; i < token_eq[0].size(); i++)
	{
		result.append(token_eq[0][i]);
	}
	result.push_back(';');
	for (int i = 0; i < token_eq[1].size(); i++)
	{
		result.append(token_eq[1][i]);
	}
	solution->push_back(result);
	result.clear();
	// magic solution grabber -^

	// plug y into first equation
	cout << "plug y into eq 1" << endl;
	token_eq[0][0] = y_soln;
	label_eq[0] = create_new_labels(token_eq[0]);

	// magic solution grabber -v
	for (int i = 0; i < token_eq[0].size(); i++)
	{
		result.append(token_eq[0][i]);
	}
	result.push_back(';');
	for (int i = 0; i < token_eq[1].size(); i++)
	{
		result.append(token_eq[1][i]);
	}
	solution->push_back(result);
	result.clear();
	// magic solution grabber -^

	// solve first equation for x
	sort_add_solve(token_eq[0], label_eq[0], "varx");
	x_soln = token_eq[0][2];

	// magic solution grabber -v
	for (int i = 0; i < token_eq[0].size(); i++)
	{
		result.append(token_eq[0][i]);
	}
	result.push_back(';');
	for (int i = 0; i < token_eq[1].size(); i++)
	{
		result.append(token_eq[1][i]);
	}
	solution->push_back(result);
	result.clear();
	// magic solution grabber -^
}

/*
* @summary solves 2 equations in the case where one contains 1 variable, and the other contains 2 variables
* @param token_eq the two equations broken into tokens
* @param label_eq the two equations broken into token labels
* @param x_soln "returns" the answer to x
* @param y_soln "returns" the answer to y
*/
void case2(vector<vector<string>>& token_eq, vector<vector<string>>& label_eq, string& x_soln, string& y_soln, std::vector<std::string>* solution) {
	string solo_var, opp_var, result;
	int solo_eq, opp_eq;

	// if first equation has two variables
	if ((find(label_eq[0].begin(), label_eq[0].end(), "varx") != label_eq[0].end()) && (find(label_eq[0].begin(), label_eq[0].end(), "vary") != label_eq[0].end())) {
		solo_eq = 1;
		opp_eq = 0;
	}
	// else first equation has one variable
	else {
		solo_eq = 0;
		opp_eq = 1;
	}

	// determine solo variable
	if (find(label_eq[solo_eq].begin(), label_eq[solo_eq].end(), "varx") != label_eq[solo_eq].end()) {
		solo_var = "varx";
		opp_var = "vary";
	}
	else {
		solo_var = "vary";
		opp_var = "varx";
	}

	// solve for one variable
	sort_add_solve(token_eq[solo_eq], label_eq[solo_eq], solo_var);
	if (solo_var == "varx") {
		x_soln = token_eq[solo_eq][2];
		cout << "x = " << x_soln << endl;
	}
	else {
		y_soln = token_eq[solo_eq][2];
		cout << "y = " << y_soln << endl;
	}

	// magic solution grabber -v
	for (int i = 0; i < token_eq[0].size(); i++)
	{
		result.append(token_eq[0][i]);
	}
	result.push_back(';');
	for (int i = 0; i < token_eq[1].size(); i++)
	{
		result.append(token_eq[1][i]);
	}
	solution->push_back(result);
	result.clear();
	// magic solution grabber -^

	// isolate that variable in opp equation
	sort_add_solve(token_eq[opp_eq], label_eq[opp_eq], solo_var);

	// magic solution grabber -v
	for (int i = 0; i < token_eq[0].size(); i++)
	{
		result.append(token_eq[0][i]);
	}
	result.push_back(';');
	for (int i = 0; i < token_eq[1].size(); i++)
	{
		result.append(token_eq[1][i]);
	}
	solution->push_back(result);
	result.clear();
	// magic solution grabber -^

	// plug solution from solo equation into opp equation
	token_eq[opp_eq][0] = token_eq[solo_eq][2];
	label_eq[opp_eq] = create_new_labels(token_eq[opp_eq]);

	// magic solution grabber -v
	for (int i = 0; i < token_eq[0].size(); i++)
	{
		result.append(token_eq[0][i]);
	}
	result.push_back(';');
	for (int i = 0; i < token_eq[1].size(); i++)
	{
		result.append(token_eq[1][i]);
	}
	solution->push_back(result);
	result.clear();
	// magic solution grabber -^

	// solve for opposite variable
	sort_add_solve(token_eq[opp_eq], label_eq[opp_eq], opp_var);
	if (solo_var == "varx") {
		y_soln = token_eq[opp_eq][2];
	}
	else {
		x_soln = token_eq[opp_eq][2];
	}

	// magic solution grabber -v
	for (int i = 0; i < token_eq[0].size(); i++)
	{
		result.append(token_eq[0][i]);
	}
	result.push_back(';');
	for (int i = 0; i < token_eq[1].size(); i++)
	{
		result.append(token_eq[1][i]);
	}
	solution->push_back(result);
	result.clear();
	// magic solution grabber -^
}

/*
* @summary solves 2 equations in the case where both contain only 1 variable
* @param token_eq the two equations broken into tokens
* @param label_eq the two equations broken into token labels
* @param x_soln "returns" the answer to x
* @param y_soln "returns" the answer to y
*/
void case3(vector<vector<string>>& token_eq, vector<vector<string>>& label_eq, string& x_soln, string& y_soln, std::vector<std::string>* solution) {
	string result;
	if (find(label_eq[0].begin(), label_eq[0].end(), "varx") != label_eq[0].end()) {
		sort_add_solve(token_eq[0], label_eq[0], "varx");
		x_soln = token_eq[0][2];

		// magic solution grabber -v
		for (int i = 0; i < token_eq[0].size(); i++)
		{
			result.append(token_eq[0][i]);
		}
		result.push_back(';');
		for (int i = 0; i < token_eq[1].size(); i++)
		{
			result.append(token_eq[1][i]);
		}
		solution->push_back(result);
		result.clear();
		// magic solution grabber -^

		sort_add_solve(token_eq[1], label_eq[1], "vary");
		y_soln = token_eq[1][2];

		// magic solution grabber -v
		for (int i = 0; i < token_eq[0].size(); i++)
		{
			result.append(token_eq[0][i]);
		}
		result.push_back(';');
		for (int i = 0; i < token_eq[1].size(); i++)
		{
			result.append(token_eq[1][i]);
		}
		solution->push_back(result);
		result.clear();
		// magic solution grabber -^

	}
	else {
		sort_add_solve(token_eq[0], label_eq[0], "vary");
		y_soln = token_eq[0][2];

		// magic solution grabber -v
		for (int i = 0; i < token_eq[0].size(); i++)
		{
			result.append(token_eq[0][i]);
		}
		result.push_back(';');
		for (int i = 0; i < token_eq[1].size(); i++)
		{
			result.append(token_eq[1][i]);
		}
		solution->push_back(result);
		result.clear();
		// magic solution grabber -^

		sort_add_solve(token_eq[1], label_eq[1], "varx");
		x_soln = token_eq[1][2];

		// magic solution grabber -v
		for (int i = 0; i < token_eq[0].size(); i++)
		{
			result.append(token_eq[0][i]);
		}
		result.push_back(';');
		for (int i = 0; i < token_eq[1].size(); i++)
		{
			result.append(token_eq[1][i]);
		}
		solution->push_back(result);
		result.clear();
		// magic solution grabber -^
	}
}

/*
* @summary intakes an equation broken into tokens and solves it
* @param token_eq an equation broken into tokens, "returns" the solved equation
* @param label_eq an equation broken into token labels
* @param variable the label to be solved for, either "varx" or "vary"
*/
void sort_add_solve(vector<string>& token_eq, vector<string>& label_eq, string variable) {
	bool sorted = false;
	while (!sorted) {
		sorted = sort_eq(token_eq, label_eq, variable);
		label_eq = create_new_labels(token_eq);
	}

	bool added = false;
	while (!added) {
		added = add_sub(token_eq);
		label_eq = create_new_labels(token_eq);
	}

	solve_eq(token_eq, variable);
	label_eq = create_new_labels(token_eq);
}

/*
* @summary intakes an equation broken into tokens and sorts it so that one variable is on the lhs, while the other & constants are on the rhs
* @param token_eq an equation broken into tokens, "returns" the sorted equation
* @param label_eq an equation broken into token labels
* @param variable the label to be on the lhs of the equation, either "varx" or "vary"
* @return whether the equation has finished sorting or not
*/
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

	for (int i = 0; i < token_eq.size(); i++) {
		cout << token_eq[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < label_eq.size(); i++) {
		cout << label_eq[i] << "\t";
	}
	cout << endl;

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

/*
* @summary intakes a sorted equation and sorts the rhs so that variables are right after =op and constants are at the end
* @param token_eq a sorted equation broken into tokens, "returns" the formatted equation
* @param label_eq a sorted equation broken into token labels
* @param variable the label to be on the lhs of the equation, either "varx" or "vary"
* @return whether the equation has finished formatting or not
*/
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

	// get rid of any double negatives
	for (int i = 0; i < token_eq.size(); i++) {
		if (token_eq[i].find("--") != string::npos) {
			token_eq[i].erase(0, token_eq[i].find_first_not_of("--"));
		}
	}

	if (ret == true) {
		return true;
	}
	else {
		return false;
	}
}

/*
* @summary intakes an added equation and outputs the solution to the variable on the lhs
* @param token_eq an added equation broken into tokens, "returns" the solved equation
* @param label_eq an added equation broken into token labels
* @param variable the label to be on the lhs of the equation, either "varx" or "vary"
*/
void solve_eq(vector<string>& token_eq, string variable) {
	if (variable == "varx") {
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

		token_eq[0] = "1x";
	}
	else {
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

		token_eq[0] = "1y";
	}
}

/*
* @summary intakes a sorted equation and adds like terms
* @param token_eq a sorted equation broken into tokens, "returns" the condensed equation
* @return whether the equation has finished adding like terms or not
*/
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

/*
* @summary intakes a tokenized equation and creates labels for its tokens
* @param token_eq an equation broken into tokens, to be used to generate token labels
* @return the equation, broken into its token labels
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

/*
* @summary determines how many variables each equation has and breaks it into cases dependent on that
* @param labels_eq an equation broken into token labels
* @return case number
*/
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
	else if (eq_x[0] == 1 && eq_y[0] == 1) {
		if (eq_x[1] == 0 && eq_y[1] == 1) {
			eq_case = 2;
		}
		else if (eq_x[1] == 1 && eq_y[1] == 0) {
			eq_case = 2;
		}
		else if (eq_x[0] == 1 && eq_y[1] == 1) {
			eq_case = 1;
		}
	}

	return eq_case;
}

/*
* @summary trims a string of " " at its beginning and end
* @param str string to be trimmed of " "
* @return string trimmed of " "
*/
string trim_white(string str) {
	str.erase(str.find_last_not_of(" ") + 1);
	str.erase(0, str.find_first_not_of(" "));
	return str;
}

// solves all steps of a system of problems
void sysSolve(std::vector<std::string>* solution)
{
	string orig_input = solution->front(); // = "3x + 3 = 2x + 8y; 5y + 10y = -18";
	char delim_sys = ';';
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

	// determine which case
	// case 1: both equations contain x & y
	// case 2: one equation contains one variable, the other contains both
	// case 3: each equation contains a separate variable
	int eq_case = determine_case(labels_eq);
	cout << eq_case << endl;

	string x_soln, y_soln;

	if (eq_case == 1) {
		case1(token_eq, labels_eq, x_soln, y_soln, solution);
	}
	else if (eq_case == 2) {
		case2(token_eq, labels_eq, x_soln, y_soln, solution);
	}
	else {
		case3(token_eq, labels_eq, x_soln, y_soln, solution);
	}

}