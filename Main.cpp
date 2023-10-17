/**
 * Main.cpp
 * CSE 332S
 * Lab Num: 1
 * Author: 
 * Lab 1 definitions. Program parses a file, printing each string that contains non-numeric
 * characters, followed by each fully numeric string.
*/

#include "Main.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

/**
 * Creates an ifstream and opens the file, returning could_not_open_file if file is not open.
 * Returns invalid_file if the file has non-character contents, or if extraction fails before
 * the end of the file. Pushes non-empty strings into result vector. Returns success if
 * end of file could be reached without errors or invalid strings.
 * Return values: success - function succeeded, could_not_open_file - file could not be opened,
 * invalid_file - file could be opened, but contains at least one non-character value.
 */
return_value parse_file (vector<string> & result, char * file_name) {
    ifstream ifs (file_name); // create ifstream with file name passed into function

    if (ifs.is_open()) { // skip this if file could not be opened
        string str;

        /* While loop that extracts from the ifstream into str, terminating when extraction fails.
         * Empty strings are skipped. Even if extraction succeeds, we still check that str contains
         * valid characters, which also catches invalid file formats such as images.
         * Valid, non-empty strings are pushed into result. */
        while (ifs >> str) {
            if (!str.empty()) {

                if (check_invalid(str)) {
                    return invalid_file;
                }

                result.push_back(str);
            }
        }

        /* If the while loop terminated because the end of the file was reached, return success.
         * Otherwise, there was an error with extraction, and invalid_file is returned. */
        if (ifs.eof()) {
            return success;
        }
        cout << "Error: file could not be read" << endl;
        return invalid_file;

    }
    cout << "Error: could not open file" << endl; // reached if file could not be opened
    return 0;
}

/**
 * Iterates through each character in a string with a for loop. Returns true if any non-ascii
 * characters are found. This prevents non-standard characters as well as invalid file types,
 * such as images, that may be allowed by the ifstream. Since characters are chars with an associated
 * numeric value, they can be compared with constants. Ascii characters have values between 0 and 127,
 * which are the possible positive values of a char.
 */
bool check_invalid (string& str) {
    for (char& c : str) {
        if (c < 0 || c > CHAR_MAX) { // only valid ascii characters are allowed
            cout << "Error: file could not be read" << endl;
            return true;
        }
    }
    return false;
}

/**
 * Iterates through each character of a string with a for loop. Checks whether they're numeric using
 * the isdigit() function. If any non-numeric characters are found, returns false. Returns true otherwise.
 */
bool check_numeric (string& str) {
    for (char& c : str) {
        if (!isdigit(c)) { // if any non-numeric characters are present, return false
            return false;
        }
    }
    return true; // return true if every character is numeric
}

/**
 * Uses an iterator to loop through a vector strings. If a string is completely numeric, declares an
 * istringstream and extracts it into a newly declared int. It then verifies that the ints's to_string
 * is equal to the original string. If it isn't, the number held by the string is too large to be stored
 * as an int. In this case, I elected to keep it in the strings vector, and print it along with
 * the non-numeric strings, rather than change the value. If the string is numeric and can be stored as an
 * int, it is pushed into the ints vector and removed from the strings vector. Removing automatically
 * iterates, and if the string is not removed we iterate manually.
 */
void int_remover (vector<string>& strings, vector<int>& ints) {

    auto str = strings.begin();
    while (str != strings.end()) {

        if (check_numeric(*str)) { // move on if string is non-numeric
            istringstream iss (*str);
            int j;
            iss >> j;

            if (to_string(j) == *str) { // if not equal, value was modified when extracting because it was too large
                ints.push_back(j);
                str = strings.erase(str);
                continue; // skip past the iteration. since we removed, str is already pointing to the next string.
            }
        }
        ++str;
    }
}

/**
 * To be called when the program is called incorrectly. Prints a usage message and returns the
 * relevant error code.
 */
return_value usage_message (char* program_name) {
    cout << "usage: " << program_name << " <input_file_name>" << endl;
    return incorrect_usage;
}

/**
 * If there isn't exactly 1 command line argument (in addition to the program name), prints a usage message
 * and returns the code corresponding to an improper call. Otherwise, declares a vector of strings and calls
 * parse_file on it with the passed file name. Upon failure, returns the corresponding error code. Upon success,
 * declares a vector of ints and calls int_remover on it and the vector of strings. Once completed, prints
 * the contents of the vector of strings, followed by the contents of the vector of ints, and returns the success code.
 */
int main (int argc, char* argv[]) {
    if (argc == numArgs) { // 2 arguments (program name and file name)

        vector<string> strings;
        return_value rv = parse_file(strings, argv[file]); // store return value of parse

        if (rv == success) {

            vector<int> ints;
            int_remover(strings, ints); // move numeric int-sized strings into ints

            for (string& s : strings) { // prints strings
                cout << s << endl;
            }

            for (int& i : ints) { // print ints
                cout << i << endl;
            }
        }
        return rv; // return code of parse_file
    }
    return usage_message(argv[program]); // call usage message with program name
}
