/*********************************************************************************************************************************************************** Program: state_facts.h
** Author: Emerald Seale
** Date: 4/11/18
** Description: Holds the state and county structs, as well as all function declarations for state_facts.cpp
** Input: None
** Output: None
*********************************************************************************************************************************************************/
#include <string>
#include <fstream>

using namespace std;

//STRUCTS:

struct county {

	string name;
	
	string* city;

	int cities;

	int population;

	float avg_income;

	float avg_house;
};

struct state {

	string name;
	
	county* c;
	
	int counties;
	
	int population;	
};

//FUNCTION DECLARATIONS:

void arguments_correct(ifstream&, ofstream&, char**, int);
void arguments_incorrect(ifstream&, ofstream&);
void sort_states_name_save(state*, int, ofstream&);
void sort_states_pop_save(state*, int, ofstream&);
void sort_counties_name_save(county*, int, ofstream&);
void sort_counties_pop_save(county*, int, ofstream&);
void organize_facts_print(state*, int);
void organize_facts_save(state*, int, ofstream&);
void sort_states_name(state*, int);
void sort_states_pop(state*, int);
void sort_counties_name(county*, int);
void sort_counties_pop(county*, int);
void swap_string(string*, string*);
void swap_int(int*, int*);
float avg_household_cost(county*, int);
string largest_state_pop(state*, int);
string largesr_county_pop(state*, int);
int print_or_save();
int get_state_pop(ifstream&);
void delete_dyn_arr(char**);
string enter_filename();
int enter_num_states();
int get_num_states(char*[]);
int get_num_counties(ifstream&);
int close_or_recover(char*[], int);
char* parse_filename(char*[]);
bool is_valid_arguments (char*[], int);
state* create_states (int);
void get_state_data (state*, int, ifstream&);
county* create_counties (int);
void get_county_data (county*, int, ifstream&);
void delete_info (state**, int);
