/*********************************************************************************************************************************************************** Program: state_facts.cpp
** Author: Emerald Seale
** Date: 4/11/18
** Description: Contains all function definitions and bodies
** Input: Filename, number of states, income to be compared, printing to the screen or saving to a .txt file
** Output: Facts about given states and counties from the file either to the screen or to a file
*********************************************************************************************************************************************************/
#include "./state_facts.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

/*********************************************************************************************************************************************************** Function: delete_info
** Description: Deletes all dynamic arrays of state, county, and city structs
** Parameters: Pointer to the dynamic 1D array of state structs and integer amount of states
** Input: None
** Output: None
*********************************************************************************************************************************************************/
void delete_info (state** stateDB, int numOfStates) {

	for (int i = 0; i < numOfStates; i++) {
		for (int j = 0; j < (*stateDB)[i].counties; j++) {
			delete [] (*stateDB)[i].c[j].city;
			(*stateDB)[i].c[j].city = NULL;
		}
	}
	for (int i = 0; i < numOfStates; i++) {
		delete [] (*stateDB)[i].c;
		(*stateDB)[i].c = NULL;
	}
	delete [] (*stateDB);
	(*stateDB) = NULL;
}

/*********************************************************************************************************************************************************** Function: delete_dyn_arr
** Description: Deletes a dynamic, 1D array 
** Parameters: Pointer to a dynamic, 1D array
** Input: None
** Output: None
*********************************************************************************************************************************************************/
void delete_dyn_arr (char** arr) {

	delete [] (*arr);
	arr = NULL;
}

/*********************************************************************************************************************************************************** Function: print_or_save
** Description: Asks the user to input whether they would like to print the information to the screen or save it to a file
** Parameters: None
** Input: 1 or 2 corresponding with printing to the screen or saving to a file
** Output: 1 or 2, whichever the user chooses
*********************************************************************************************************************************************************/
int print_or_save () {

	char temp = 0;
	int num = 0;
	do {
		cout << "\nWould you like to print your state and county facts to the screen or save them to a file?" << endl;
		cout << "Enter 1 to print to the screen. Enter 2 to save to a file." << endl;
		cin >> temp;
		num = (temp - 48);
	} while (num != 1 && num != 2);
	return num;
}

/*********************************************************************************************************************************************************** Function: swap_string
** Description: Swaps two strings within a given array
** Parameters: Pointer to strings one and two
** Input: None
** Output: None
*********************************************************************************************************************************************************/
void swap_string (string* one, string* two) {

	string temp = *one;
	*one = *two;
	*two = temp;
}

/*********************************************************************************************************************************************************** Function: swap_int
** Description: Swaps two integers within a given array
** Parameters: Pointer to integers one and two
** Input: None
** Output: None
*********************************************************************************************************************************************************/
void swap_int (int* one, int* two) {

	int temp = *one;
	*one = *two;
	*two = temp;
}

/*********************************************************************************************************************************************************** Function: largest_state_pop
** Description: Determines which state has the largest population in a given array of state structs
** Parameters: 1D array of state structs stateDB and integer numOfStates
** Input: None
** Output: String largest
*********************************************************************************************************************************************************/
string largest_state_pop (state* stateDB, int numOfStates) {

	string largest = "";
	int biggest = 0;
	for (int i = 0; i < numOfStates; i++) {
		if (biggest < stateDB[i].population) {
			biggest = stateDB[i].population;
			largest = stateDB[i].name;	
		}
	}
	return largest;
}

/*********************************************************************************************************************************************************** Function: largest_county_pop
** Description: Determines which county has the largest population in a given array of county structs
** Parameters: 1D array of state structs stateDB and integer numOfStates
** Input: None
** Outpute: Integer largest
*********************************************************************************************************************************************************/
string largest_county_pop (state* stateDB, int numOfStates) {

	string largest = "";
	int biggest = 0;
	for (int i = 0; i < numOfStates; i++) {
		for (int j = 0; j < stateDB[i].counties; j++) {
			if (biggest < stateDB[i].c[j].population) {
				biggest = stateDB[i].c[j].population;
				largest = stateDB[i].c[j].name;
			}
		}
	}
	return largest;
}

/*********************************************************************************************************************************************************** Function: avg_household_cost
** Description: Determines the average county household cost for each state
** Parameters: 1D array of state structs stateDB, integer numOfCounties
** Input: None
** Output: Float average amount
*********************************************************************************************************************************************************/
float avg_household_cost (county* countyDB, int numOfCounties) {
	
	float cost = 0;
	for (int i = 0; i < numOfCounties; i++) {
			cost += countyDB[i].avg_house;
	}
	cost = cost / (float)numOfCounties;
	return cost;
}

/*********************************************************************************************************************************************************** Function: sort_states_name
** Description: Sorts all states by name in alphabetical order
** Parameters: 1D array of state structs stateDB, integer numOfStates
** Input: None
** Output: Prints list to the screen
*********************************************************************************************************************************************************/
void sort_states_name (state* stateDB, int numOfStates) {

	for (int i = 0; i < (numOfStates - 1); i++) {
		for (int j = 0; j < (numOfStates - i - 1); j++) {
			if (stateDB[j].name > stateDB[(j + 1)].name) {
				swap_string(&stateDB[j].name, &stateDB[(j + 1)].name);
			}
		}
	}
	cout << "\nStates sorted by name:";
	for (int i = 0; i < numOfStates; i++) {
		cout << "\n" << stateDB[i].name;
	}
	cout << endl;
}

/*********************************************************************************************************************************************************** Function: sort_states_pop
** Description: Sorts all states by population, highest to lowest
** Parameters: 1D dynamic array of state structs stateDB, integer number of states
** Input: None
** Output: Prints list to the screen
*********************************************************************************************************************************************************/
void sort_states_pop (state* stateDB, int numOfStates) {

	for (int i = 0; i < (numOfStates - 1); i++) {
		for (int j = 0; j < (numOfStates - i - 1); j++) {
			if (stateDB[j].population < stateDB[(j + 1)].population) {
				swap_int(&stateDB[j].population, &stateDB[(j + 1)].population);
				swap_string(&stateDB[j].name, &stateDB[(j + 1)].name);
			}
		}
	}
	cout << "\nStates sorted by population:";
	for (int i = 0; i < numOfStates; i++) {
		cout << "\n" << stateDB[i].name;
	}
	cout << endl;

}

/*********************************************************************************************************************************************************** Function: sort_counties_name
** Description: Sorts all the counties by name in alphabetical order
** Parameters: 1D dynamic array of counties countyDB, integer number of counties
** Input: None
** Output: Prints list to the screen
*********************************************************************************************************************************************************/
void sort_counties_name (county* countyDB, int numOfCounties) {

	for (int i = 0; i < (numOfCounties - 1); i++) {
		for (int j = 0; j < (numOfCounties - i - 1); j++) {
			if (countyDB[j].name > countyDB[(j + 1)].name) {
				swap_string(&countyDB[j].name, &countyDB[(j + 1)].name);
			}
		}
	}
	for (int i = 0; i < numOfCounties; i++) {
		cout << "\n" << countyDB[i].name;
	}
	cout << endl;
}

/*********************************************************************************************************************************************************** Function: sort_counties_pop
** Description: Sorts al the counties by population, highest to lowest
** Parameters: 1D dynamic array of counties countyDB, integer number of counties
** Input: None
** Output: Prints a list to the screen
*********************************************************************************************************************************************************/
void sort_counties_pop (county* countyDB, int numOfCounties) {

	for (int i = 0; i < (numOfCounties - 1); i++) {
		for (int j = 0; j < (numOfCounties - i - 1); j++) {
			if (countyDB[j].population < countyDB[(j + 1)].population) {
				swap_int(&countyDB[j].population, &countyDB[(j + 1)].population);
				swap_string(&countyDB[j].name, &countyDB[(j + 1)].name);
			}
		}
	}
	for (int i = 0; i < numOfCounties; i++) {
		cout << "\n" << countyDB[i].name;
	}
	cout << endl;
}

/*********************************************************************************************************************************************************** Function: organize_facts_print
** Description: Calls all fact functions 
** Parameters: 1D array of state structs stateDB, integer numOfStates
** Input: Income to be compared 
** Output: Prints facts to the screen
*********************************************************************************************************************************************************/
void organize_facts_print (state* stateDB, int numOfStates) {

	int incomeAbove = 0;
	cout << "\nPlease enter an income to compare: ";
	cin >> incomeAbove;
	string largestStatePop = largest_state_pop(stateDB, numOfStates);
	cout << "\nThe state with the largest population is: " << largestStatePop << "." << endl;
	string largestCountyPop = largest_county_pop(stateDB, numOfStates);
	cout << "\nThe county with the largest population is: " << largestCountyPop << "." << endl;
	cout << "\nThe counties above the input income are: ";
	for (int i = 0; i < numOfStates; i++) {
		for (int j = 0; j < stateDB[i].counties; j++) {
			if (incomeAbove < stateDB[i].c[j].avg_income) {
				cout << "\n" << stateDB[i].c[j].name; 
			}
		}
	}
	cout << endl;
	for (int i = 0; i < numOfStates; i++) {
		cout << "\nThe average household cost of all counties in " << stateDB[i].name << " is: ";
		float avg_cost = avg_household_cost(stateDB[i].c, stateDB[i].counties);
		cout << avg_cost << endl;
	}
	sort_states_name(stateDB, numOfStates);
	sort_states_pop(stateDB, numOfStates);
	cout << "\nCounties sorted by name:";
	for (int i = 0; i < numOfStates; i++) {
		cout << "\n" << stateDB[i].name << ":";
		sort_counties_name(stateDB[i].c, stateDB[i].counties);
	}
	cout << "\nCounties sorted by population:";
	for (int i = 0; i < numOfStates; i++) {
		cout << "\n" << stateDB[i].name << ":";
		sort_counties_pop(stateDB[i].c, stateDB[i].counties);
	}
}

/*********************************************************************************************************************************************************** Function: sort_states_name_save
** Description: Sorts all states by name in alphabetical order
** Parameters: 1D array of state structs stateDB, integer numOfStates
** Input: None
** Output: Saves list to the file
*********************************************************************************************************************************************************/
void sort_states_name_save (state* stateDB, int numOfStates, ofstream& w) {

	for (int i = 0; i < (numOfStates - 1); i++) {
		for (int j = 0; j < (numOfStates - i - 1); j++) {
			if (stateDB[j].name > stateDB[(j + 1)].name) {
				swap_string(&stateDB[j].name, &stateDB[(j + 1)].name);
			}
		}
	}
	w << "\nStates sorted by name:";
	for (int i = 0; i < numOfStates; i++) {
		w << "\n" << stateDB[i].name;
	}
	w << endl;
}

/*********************************************************************************************************************************************************** Function: sort_states_pop_save
** Description: Sorts all states by population, highest to lowest
** Parameters: 1D dynamic array of state structs stateDB, integer number of states
** Input: None
** Output: Saves list to the file
*********************************************************************************************************************************************************/
void sort_states_pop_save (state* stateDB, int numOfStates, ofstream &w) {

	for (int i = 0; i < (numOfStates - 1); i++) {
		for (int j = 0; j < (numOfStates - i - 1); j++) {
			if (stateDB[j].population < stateDB[(j + 1)].population) {
				swap_int(&stateDB[j].population, &stateDB[(j + 1)].population);
				swap_string(&stateDB[j].name, &stateDB[(j + 1)].name);
			}
		}
	}
	w << "\nStates sorted by population:";
	for (int i = 0; i < numOfStates; i++) {
		w << "\n" << stateDB[i].name;
	}
	w << endl;

}

/*********************************************************************************************************************************************************** Function: sort_counties_name_save
** Description: Sorts all the counties by name in alphabetical order
** Parameters: 1D dynamic array of counties countyDB, integer number of counties
** Input: None
** Output: Saves list to the file
*********************************************************************************************************************************************************/
void sort_counties_name_save (county* countyDB, int numOfCounties, ofstream& w) {

	for (int i = 0; i < (numOfCounties - 1); i++) {
		for (int j = 0; j < (numOfCounties - i - 1); j++) {
			if (countyDB[j].name > countyDB[(j + 1)].name) {
				swap_string(&countyDB[j].name, &countyDB[(j + 1)].name);
			}
		}
	}
	for (int i = 0; i < numOfCounties; i++) {
		w << "\n" << countyDB[i].name;
	}
	w << endl;
}

/*********************************************************************************************************************************************************** Function: sort_counties_pop_save
** Description: Sorts al the counties by population, highest to lowest
** Parameters: 1D dynamic array of counties countyDB, integer number of counties
** Input: None
** Output: Saves a list to the file
*********************************************************************************************************************************************************/
void sort_counties_pop_save (county* countyDB, int numOfCounties, ofstream &w) {

	for (int i = 0; i < (numOfCounties - 1); i++) {
		for (int j = 0; j < (numOfCounties - i - 1); j++) {
			if (countyDB[j].population < countyDB[(j + 1)].population) {
				swap_int(&countyDB[j].population, &countyDB[(j + 1)].population);
				swap_string(&countyDB[j].name, &countyDB[(j + 1)].name);
			}
		}
	}
	for (int i = 0; i < numOfCounties; i++) {
		w << "\n" << countyDB[i].name;
	}
	w << endl;
}
/*********************************************************************************************************************************************************** Function: organize_facts_save
** Description: Calls fact functions and saves them to a file
** Parameters: Array of states stateDB and integer number of states
** Input: Income integer to be compared, name of file
** Output: Facts into given file
*********************************************************************************************************************************************************/
void organize_facts_save (state* stateDB, int numOfStates, ofstream& w) {

	int incomeAbove = 0;
	cout << "\nPlease enter an income to compare: ";
	cin >> incomeAbove;
	string largestStatePop = largest_state_pop(stateDB, numOfStates);
	w << "\nThe state with the largest population is: " << largestStatePop << "." << endl;
	string largestCountyPop = largest_county_pop(stateDB, numOfStates);
	w << "\nThe county with the largest population is: " << largestCountyPop << "." << endl;
	w << "\nThe counties above the input income are: ";
	for (int i = 0; i < numOfStates; i++) {
		for (int j = 0; j < stateDB[i].counties; j++) {
			if (incomeAbove < stateDB[i].c[j].avg_income) {
				w << "\n" << stateDB[i].c[j].name; 
			}
		}
	}
	w << endl;
	for (int i = 0; i < numOfStates; i++) {
		w << "\nThe average household cost of all counties in " << stateDB[i].name << " is: ";
		float avg_cost = avg_household_cost(stateDB[i].c, stateDB[i].counties);
		w << avg_cost << endl;
	}
	sort_states_name_save(stateDB, numOfStates, w);
	sort_states_pop_save(stateDB, numOfStates, w);
	w << "\nCounties sorted by name:";
	for (int i = 0; i < numOfStates; i++) {
		w << "\n" << stateDB[i].name << ":";
		sort_counties_name_save(stateDB[i].c, stateDB[i].counties, w);
	}
	w << "\nCounties sorted by population:";
	for (int i = 0; i < numOfStates; i++) {
		w << "\n" << stateDB[i].name << ":";
		sort_counties_pop_save(stateDB[i].c, stateDB[i].counties, w);
	}
}
/*********************************************************************************************************************************************************** Function: enter_num_states
** Description: Gets the number of states as input from the user if the command line argument is found to be invalid
** Parameters: None
** Input: Integer number of states
** Output: Integer number of states
*********************************************************************************************************************************************************/
int enter_num_states () {
	
	char temp = 0;
	int numOfStates = 0;
	cout << "\nIt looks like you've either entered a non-valid integer or your file doesn't exist." << endl;
	do {
		cout << "Please enter your number of states as a valid, non-zero integer: ";
		cin >> temp;
		numOfStates = (temp - 48);
	} while (numOfStates < 1);
	return numOfStates;
}

/*********************************************************************************************************************************************************** Function: enter_filename
** Description: Gets the filename as input from the user if the command line argument is found to be invalid
** Parameters: None
** Input: String filename
** Output: C-style string filename
*********************************************************************************************************************************************************/
string enter_filename () {

	fstream f;
	string fileName = "";
	bool flag = 0;
	do {
		cout << "Please enter a valid, existing filename ending in .txt: ";
		getline(cin, fileName);
		char* temp = new char[fileName.length() + 1];
		strcpy(temp, fileName.c_str());
		f.open(temp);
		delete_dyn_arr(&temp);	
		if (f.fail()) {
			f.close();
			flag = 0;	
		} else {
			f.close();
			flag = 1;
		}
	} while (flag == 0);
	return fileName;
}

/*********************************************************************************************************************************************************** Function: get_num_states
** Description: Gets the number of states from the command line and returns it as an integer
** Parameters: 2D dynamic array argv
** Input: None
** Output: Integer number of states
*********************************************************************************************************************************************************/
int get_num_states (char** argv) {

	int final_num = ((argv[2][0] - 48) * pow(10, 0));
	
	return final_num;	
}

/*********************************************************************************************************************************************************** Function: create_states
** Description: Creates a 1D dynamic array of state structs
** Parameters: Integer number of states
** Input: None
** Output: 1D dynamic array of state structs
*********************************************************************************************************************************************************/
state* create_states (int numOfStates) {

	state* temp = new state[numOfStates];
	return temp;
}

/*********************************************************************************************************************************************************** Function: get_num_counties
** Description: Finds the number of counties within a given state 
** Paramters: ifstream object f
** Input: None
** Output: Integer number of counties
*********************************************************************************************************************************************************/
int get_num_counties (ifstream& f) {

	int num = 0;
	while (!f.eof()) {
		f >> num;
		if (num < 10 && num > 0) {
			return num;
		}
	}
}

/*********************************************************************************************************************************************************** Function: get_state_pop
** Description: Finds the population of a state from the file
** Parameters: ifstream object f
** Input: None
** Output: Integer population of state
*********************************************************************************************************************************************************/
int get_state_pop (ifstream& f) {

	int num = 0;
	f >> num;
	return num;
}

/*********************************************************************************************************************************************************** Function: create_counties
** Description: Creates a 1D dynamic array of county structs
** Parameters: Integer number of counties within a given state
** Input: None
** Output: Pointer to a 1D dynamic array of county structs
*********************************************************************************************************************************************************/
county* create_counties (int numOfCounties) {

	county* temp = new county[numOfCounties];
	return temp;
}

/*********************************************************************************************************************************************************** Function: get_state_data
** Description: Populates the array of state structs with information from the given file
** Parameters: Array of state structs stateDB, integer number of states, ifstring object f
** Input: None
** Output: None
*********************************************************************************************************************************************************/
void get_state_data (state* stateDB, int numOfStates, ifstream& f) {

	int numOfCounties = 0;
	for (int i = 0; i < numOfStates; i++) {
		f >> stateDB[i].name;
		int pop = get_state_pop(f);
		stateDB[i].population = pop;
		numOfCounties = get_num_counties(f);
		stateDB[i].counties = numOfCounties;
		stateDB[i].c = create_counties(stateDB[i].counties);
		for (int i = 0; i <= numOfCounties; i++) {
			f.ignore(365, '\n');
		}
	}
}

/*********************************************************************************************************************************************************** Function: get_county_data
** Description: Populates the array of counties with information from the given file
** Parameters: Array of county structs countyDB, integer number of counties, ifstring object f
** Input: None
** Output: None
*********************************************************************************************************************************************************/
void get_county_data (county* countyDB, int numOfCounties, ifstream& f) {

	for (int i = 0; i < numOfCounties; i++) {
		f.ignore(365, '\n');
		f >> countyDB[i].name;
		f >> countyDB[i].population;
		f >> countyDB[i].avg_income;
		f >> countyDB[i].avg_house;
		f >> countyDB[i].cities;
		countyDB[i].city = new string[countyDB[i].cities];
	}
	f.ignore(365, '\n');
}

/*********************************************************************************************************************************************************** Function: parse_filename
** Descrption: Parses the command line 2D dynamic array argv for the filename
** Parameters: 2D dynamic array argv
** Input: None
** Output: Returns 1D dynamic array temp
*********************************************************************************************************************************************************/
char* parse_filename (char** argv) {

	int i = 0;
	int count = 0;
	while (argv[4][i] != '\0') {
		count++;
		i++;
	}
	char* temp = new char[count];
	for (int i = 0; i < count; i++) {
		temp[i] = argv[4][i];
	}
	return temp;
}

/*********************************************************************************************************************************************************** Function: is_valid_arguments
** Description: Checks to see if command line argument from the user is valid
** Parameters: Dynamic 2D array argv and integer argc
** Input: Command line argument from the user
** Output: True or false
*********************************************************************************************************************************************************/
bool is_valid_arguments (char** argv, int argc) {

	fstream f;
	if (argc != 5) {
		return false;
	} else if (argv[1][0] != '-' || argv[1][1] != 's' || argv[3][0] != '-' || argv[3][1] != 'f') {
		return false;
	} else if ((int)(argv[2][0]) < 49 || (int)(argv[2][0]) > 57) {
		return false;	
	}
	char* fileName = parse_filename(argv); 
	f.open(fileName);
	delete_dyn_arr(&fileName);	
	if (f.fail()) {
		f.close();
		return false;
	}
	f.close();
	return true;
}

/*********************************************************************************************************************************************************** Function: close_or_recover
** Description: Determines in what way the user input is invalid, and either closes or repromts the user depending
** Parameters: 2D character array argv and integer argc
** Input: None
** Output: An integer corresponding with what kind of error occured
*********************************************************************************************************************************************************/int close_or_recover (char** argv, int argc) {

	fstream f;
	if (argc != 5) {
		return 0;
	} else if (argv[1][0] != '-' || argv[1][1] != 's' || argv[3][0] != '-' || argv[3][1] != 'f') {
		return 0;
	} else if ((int)(argv[2][0]) < 49 || (int)(argv[2][0]) > 57) {
		return 1;	
	}
	char* fileName = parse_filename(argv); 
	f.open(fileName);
	delete_dyn_arr(&fileName);	
	if (f.fail()) {
		f.close();
		return 1;
	}
}

/*********************************************************************************************************************************************************** Function: arguments_correct
** Description: Is called when the command line arguments are correct, main program
** Parameters: ifstream object f and ofstream object w, char** argv and int argc
** Input: None
** Output: State and counties facts either to the screen or to a file
*********************************************************************************************************************************************************/void arguments_correct (ifstream& f, ofstream& w, char** argv, int argc) {
		
	int numOfStates = get_num_states(argv);
	char fileName[64];
		for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-f") == 0) {
			strcpy(fileName, argv[i+1]);
		}
	}
	f.open(fileName);
	state* stateDB = create_states(numOfStates); 
	get_state_data(stateDB, numOfStates, f); 
	f.clear();
	f.seekg(0, ios::beg);
	for (int i = 0; i < numOfStates; i++) {
		get_county_data(stateDB[i].c, stateDB[i].counties, f);
	}
	f.close();
	if (print_or_save() == 1) {
		organize_facts_print(stateDB, numOfStates);	
	} else {
		string fileNameWrite = "";
		cout << "Enter the name of the file you would like to save to: ";
		cin >> fileNameWrite;
		w.open(fileNameWrite.c_str());
		organize_facts_save(stateDB, numOfStates, w);
		w.close();
	}
	delete_info(&stateDB, numOfStates);
}

/*********************************************************************************************************************************************************** Function: arguments_incorrect
** Description: Runs if command line arguments are found invalid, main program
** Parameters: ifstream object f and ofstream object w
** Input: Correct state number and filename
** Output: Facts about states and counties to the screen or file
*********************************************************************************************************************************************************/
void arguments_incorrect(ifstream& f, ofstream& w) {

	int numOfStates = enter_num_states();
	string tempFileName = enter_filename();
	char fileName[64];
	strcpy(fileName, tempFileName.c_str());
	f.open(fileName);
	state* stateDB = create_states(numOfStates); 
	get_state_data(stateDB, numOfStates, f); 
	f.clear();
	f.seekg(0, ios::beg);
	for (int i = 0; i < numOfStates; i++) {
		get_county_data(stateDB[i].c, stateDB[i].counties, f);
	}
	f.close();
	if (print_or_save() == 1) {
		organize_facts_print(stateDB, numOfStates);	
	} else {
		string fileNameWrite = "";
		cout << "Enter the name of the file you would like to save to: ";
		cin >> fileNameWrite;
		w.open(fileNameWrite.c_str());
		organize_facts_save(stateDB, numOfStates, w);
		w.close();
	}
	delete_info(&stateDB, numOfStates);
}

