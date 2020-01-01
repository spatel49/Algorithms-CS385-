/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : Siddhanth Y. Patel
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : October 18, 2019
 * Description   : Implements the quickselect algorithm found on page 160 in
 *                 Algorithms, 3e by Anany Levitin.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

size_t lomuto_partition(int array[], size_t left, size_t right) {
    // TODO
    int pivot = array[left];
    size_t s = left;
    for (size_t i = left + 1; i <= right; i++){
        if (array[i] < pivot){
            s++;
            swap(array[s],array[i]);
        }
    }
    swap(array[left], array[s]);
    return s;
}

int quick_select(int array[], size_t left, size_t right, size_t k) {
    // TODO
    size_t s = lomuto_partition(array, left, right);
    if (s == k-1){
        return array[s];
    }
    if (s > k - 1) {
        return quick_select(array, left, s-1, k);
    }
    return quick_select(array, s+1, right, k);
}

int quick_select(int array[], const size_t length, size_t k) {
    return quick_select(array, 0, length - 1, k);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <k>" << endl;
        return 1;
    }

    int k;
    istringstream iss;
    iss.str(argv[1]);
    if ( !(iss >> k) || k <= 0 ) {
        cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    iss.clear();
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    int num_values = values.size();
    if (num_values == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    // TODO - error checking k against the size of the input
    if (num_values < k) {
        if (num_values == 1){
            cerr << "Error: Cannot find smallest element " << k << " with only 1 value." << endl;
        } else {
            cerr << "Error: Cannot find smallest element " << k << " with only " << num_values << " values." << endl;
        }
        return 1;
    }

    // TODO - call the quick_select function and display the result
    cout << "Smallest element " << k << ": " << quick_select(&values[0], num_values, k) << endl;
    return 0;
}
