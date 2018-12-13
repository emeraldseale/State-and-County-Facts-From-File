/*********************************************************************************************************************************************************** Program: run_facts.cpp
** Author: Emerald Seale
** Date: 4/11/18
** Description: Contains the main function for the program
** Input: Command line arguments argc and argv 
** Output: Message for when the user inputs too few arguments or doesn't include -s or -f
*********************************************************************************************************************************************************/
#include "state_facts.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

/*********************************************************************************************************************************************************** Function: main
** Description: Main function, runs at program start and calls other functions
** Parameters: Integer argc and 2D character array argv
** Input: 2D character array argv
** Output: Prints facts to the screen or writes them to a file of the user's choosing
*********************************************************************************************************************************************************/
int main (int argc, char** argv) {

	ifstream f;
	ofstream w;
	if (is_valid_arguments(argv, argc) == true) {
		arguments_correct(f, w, argv, argc);
	} else {
		int num = close_or_recover(argv, argc);
		if (num == 0) {
			cout << "It looks like you forgot to include -f or -s, or have included too few arguments. The program will now close." << endl;
		} else if (num == 1) {
			arguments_incorrect(f, w);
		}
	}

	return 0;
}
