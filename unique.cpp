/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Siddhanth Y. Patel
 * Date        : September 20, 2019
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    if (s.length()==0){
        return true;
    }
    bool check = true;
    for (int i = 0; i<(int)s.length(); i++) {
        if (islower(s.at(i))) {
            check = check && true;
        }
        else {
            check = false;
        }
    }
    return check;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
    if (s.length()==0){
        return true;
    }
    unsigned int newstr = 0;
    int bstr = 1;
    bool check2 = true;
    for (int i = 0; i< (int)s.length(); i++) {
        int shift = s.at(i)-97;
        if (((bstr << shift) & newstr) == 0) {
            bstr <<= shift;
            newstr |= bstr;
            bstr = 1;
        }
        else{
            check2 = false;
            break;
        }
    }
    return check2;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    if(argc == 1){
        cerr << "Usage: ./unique <string>";
        return 1;
    }
    if(argc > 2){
        cerr << "Usage: ./unique <string>";
        return 1;
    }
    string x = argv[1];
    if(is_all_lowercase(x) == false){
        cerr << "Error: String must contain only lowercase letters.";
        return 1;
    }
    if(all_unique_letters(x) == true){
        cerr << "All letters are unique.";
        return 0;
    }
    if(all_unique_letters(x) == false){
        cerr << "Duplicate letters found.";
        return 1;
    }
}
