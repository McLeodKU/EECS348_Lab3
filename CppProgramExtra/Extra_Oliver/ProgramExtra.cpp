/*
 * Author: Michael Oliver
 * Date: 2/16/2023
 * Last Edit: 2/19/2023
 * KU ID: 3016991
 * Purpose: EECS 348 Lab exercise - bonus 
 * Key take away: Learning to code in C++ and also learn to solve the stable marriage problem (Gale-Shapley Algorithm)  -- this was horribly hard 
 * I mean this in a respectful way a lot of the tools for this to work didn't come from class -- kinda rubs me the wrong way -- learned a lot about C++ tho :)
 * Area for improvement: I need to find a way to handle a bigger file size -- file IO is confusing in C and C++ 
 */
#include <iostream> // all the import statements 
#include <fstream>
#include <sstream>
#include <vector>   // the bottom three of include are the main ones we care about they handle a lot of the work in stable_matching()  
#include <algorithm> //Note to self: any niche docs go here https://www.geeksforgeeks.org/vector-in-cpp-stl/ , https://www.geeksforgeeks.org/c-magicians-stl-algorithms/, https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/
#include <unordered_map> // these three libaries made life so much easier not sure what I would of done without them 

using namespace std;
const int MAX_SIZE = 5;

unordered_map<int, int> match_maker(vector<vector<int>> department_prefs, vector<vector<int>> programmer_prefs) {   // takes in two 5x5 vectors 
    /*
     * docs for stuff less understood -- or I want more docs over 
     * find() is used to search an element inside a certain range and then returns the first occurance of it 
     * .begin() and .end() are used to traverse the unordered maps and vectors 
    */
    int departments = department_prefs.size();  // gets size of the department_prefs vector 
    int programmers = programmer_prefs.size();  // gets size of the programmer_prefs vector 

    vector<bool> free_departments(departments, true);
    unordered_map<int, int> department_matches;
    vector<int> programmer_status(programmers, -1);
                                                                
    while (find(free_departments.begin(), free_departments.end(), true) != free_departments.end()) { // while loop to assign preferred programmers to departments 
        int single_department;
        for (single_department = 0; single_department < departments; single_department++) { // find a free department 
            if (free_departments[single_department]) {
                break;  // found department
            }
        }
        int preferred_programmer = department_prefs[single_department][0]; // find the preferred programmer for the department 

        if (programmer_status[preferred_programmer] == -1) {    // assign the programmer to the department 
            programmer_status[preferred_programmer] = single_department;
            department_matches[single_department] = preferred_programmer;
            free_departments[single_department] = false;
        }
        else {  // if the programmer is assigned -- check their prefernces 
            int current_department = programmer_status[preferred_programmer];
            if (find(programmer_prefs[preferred_programmer].begin(), programmer_prefs[preferred_programmer].end(), single_department) <
                find(programmer_prefs[preferred_programmer].begin(), programmer_prefs[preferred_programmer].end(), current_department)) {   // check if we have a better option -- gross but it works 
                department_matches[current_department] = -1;    // better option found! reassign and a free up department 
                programmer_status[preferred_programmer] = single_department;
                department_matches[single_department] = preferred_programmer;
                free_departments[current_department] = true;
                free_departments[single_department] = false;
            }
            else {
                department_prefs[single_department].erase(department_prefs[single_department].begin()); // remove the current department from the preferred programmers choices -- try again 
            }
        }
    }
return department_matches; // return best matches 
}

void transpose(int arr[][MAX_SIZE], int rows) { // tranpost array for mean input file :( 
    int temp;                                   // taking advantage of the fact the imput file will always be 10x5 
    for (int i = 0; i < rows; i++) {
        for (int j = i; j < MAX_SIZE; j++) {
            temp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = temp;
        }
    }
}

int main() {
    std::string filename;       // gets a filename from the user 
    std::cout << "Please enter the name of the file: ";
    std::cin >> filename;

    std::ifstream infile(filename);
    if (infile.is_open()) {     // File is open
    }
    else {                      // file is not open 
        std::cout << "Error opening file." << std::endl;
    }

    int arr[10][MAX_SIZE]; // makes a 10x5 array 

    string line;
    int row = 0;
    while (getline(infile, line) && row < 10) { // reads file and populates array 
        stringstream ss(line);
        int col = 0;
        int num;
        while (ss >> num && col < MAX_SIZE) {
            arr[row][col] = num-1; // changes it to indexs not raw value from file 
            col++;
        }
        row++;
    }
    
    int departmentPrefs[MAX_SIZE][MAX_SIZE];    // make two other arrays 
    int programmerPrefs[MAX_SIZE][MAX_SIZE];

    for (int i = 0; i < MAX_SIZE; i++) {        // populate arrays from 10x5 array 
        for (int j = 0; j < MAX_SIZE; j++) {
            departmentPrefs[i][j] = arr[i][j];
            programmerPrefs[i][j] = arr[i + MAX_SIZE][j];
        }
    }

    transpose(departmentPrefs, MAX_SIZE);   // transpose both arrays
    transpose(programmerPrefs, MAX_SIZE);
 
    std::vector<std::vector<int>> department_prefs;     // vectors -- bad naming convention on my part -- I always opt for _ normally 
    std::vector<std::vector<int>> programmer_prefs;

    for (int i = 0; i < 5; i++) {       // populate both vectors with transposed arrays -- I'm sure that there is a way to do this faster -- unsure how tho 
        std::vector<int> dept_row;      // meaning going from file directly to vectors 
        std::vector<int> prog_row;
        for (int j = 0; j < 5; j++) {
            dept_row.push_back(departmentPrefs[i][j]);
            prog_row.push_back(programmerPrefs[i][j]);
        }
        department_prefs.push_back(dept_row);
        programmer_prefs.push_back(prog_row);
    }
    cout << "Note: Reads by row and it's INDEX prefs \n"; // these are all left over verfication checks for myself -- basically verify what I did was correct -- could be left out but I like them 

    cout << "Department preferences:\n";
    for (auto& prefs : department_prefs) {
        for (auto& pref : prefs) {
            cout << pref << " ";
        }
        cout << "\n";
    }

    cout << "Programmer preferences:\n";
    for (auto& prefs : programmer_prefs) {
        for (auto& pref : prefs) {
            cout << pref << " ";
        }
        cout << "\n";
    }

    unordered_map<int, int> matches = match_maker(department_prefs, programmer_prefs);  // call for stable matching 

    // Print the matches
    for (auto match : matches) { // first time using auto -- kinda cool -- instead of making me declare the varible it detects it for me  
        cout << "Department " << match.first+1 << " is matched with Programmer " << match.second+1 << "\n";
    }

    return 0;
}
