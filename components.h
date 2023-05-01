#pragma once

// 3rd party microsoft & and cpp headers
#include <windows.h> // windows.h required for windows app
#include <tchar.h> // defines TCHAR macro whe unicode is not enabled || consider getting rid of tchar for string. research says tchar is outdated, as non unicode compiles will not occur.
#include <new> // required for using the new operator
#include <commctrl.h> // user control intefaces
#include <windowsx.h> // windows such as buttons and input boxes
#include <math.h> // this will help with the calculator functions.
#include <vector> // for linear algebra and sys eq solvers.
#include <string> // not silly like tchar
#include <sstream>
#include <iostream>
#include <fstream>

// custom compenents

// string to TCHAR
void string2TCHAR(std::string *, TCHAR *, const int); // string, output TCHAR, and then its size

// TCHAR to string
void TCHAR2String(TCHAR*, const int, std::string*); // TCHAR, its size, and then output string

//TCHAR clear
void TCHARClear(TCHAR*, const int); // tchar then size

// required for la_step
std::vector<std::string> step(std::vector < std::string>, std::vector<std::string>);
std::vector<std::string> create_new_eq(std::vector<std::string>, int, std::string, std::string);
std::vector<std::string> create_new_labels(std::vector<std::string>);


// laSolve solves all steps of a given solution vector<string>. 
void laSolve(std::vector<std::string>* solution);

// sysSolve solves all steps of a given solutions vector<string>. 
void sysSolve(std::vector<std::string>* solution);
