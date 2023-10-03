/**
 * Main.h
 * CSE 332S
 * Lab Num: 1
 * Author: 
 * Lab 1 declarations. Program parses a file, printing each string that contains non-numeric
 * characters, followed by each fully numeric string.
*/

#ifndef CSE332LAB_MAIN_H
#define CSE332LAB_MAIN_H

#include <vector>
#include <string>

using namespace std;

// Indices of argv
enum indices {
    program, // Program name
    file, // Name of file to be parsed
    numArgs // The number of arguments to be passed into the program, and the correct value of argc
};

// Return codes for the program, which are also used by functions and passed back to main()
enum return_value {
    success, // Return value 0 indicates success
    could_not_open_file, // File with the given name could not be found, or could not be opened
    invalid_file, // File contains at least 1 non-character value and could not be parsed,
    incorrect_usage // Program was not run with a single additional command line argument
};

/**
 * Checks whether a string contains invalid characters.
 *
 * @param str the string to be checked
 * @return true if the string is invalid, false otherwise
 */
bool check_invalid(string& str);

/**
 * Opens and parses a file, pushing each non-empty string into the result vector.
 *
 * @param result a reference to a vector of strings, into which valid strings are pushed.
 * @param file_name a C style string, the name of a file to be parsed.
 * @return return code corresponding to the outcome of the funtion
 */
return_value parse_file(vector<string> & result, char * file_name);

/**
 * Searches a vector of strings for numeric, int-sized strings, moving them to a vector of ints.
 *
 * @param strings a reference to a vector of strings that may be numeric and int-sized.
 * @param ints a reference to an empty vector of ints where numeric strings will be moved.
 */
void int_remover (vector<string>& strings, vector<int>& ints);

/**
 * Checks whether a string contains only numeric characters.
 *
 * @param str the string to be checked
 * @return true if str is completely numeric, false otherwise
 */
bool check_numeric(string& str);

/**
 * Prints a helpful usage message indicating proper usage of the program.
 *
 * @param program_name the name of the program being run
 * @return incorrect_usage, the error code corresponding to improper arguments
 */
return_value usage_message (char* program_name);

#endif //CSE332LAB_MAIN_H
