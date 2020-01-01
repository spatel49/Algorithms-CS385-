/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Siddhanth Y. Patel
 * Version     : 1.0
 * Date        : October 23, 2019
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.

static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */

long count_inversions_slow(int array[], int length) {
    // TODO
    long counter = 0;
    for (int i=0; i< length; i++){
        for (int j =i; j < length; j++){
            if (array[i] > array[j]){
                counter++;
            }
        }
    }
    return counter;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */

long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int *blank= new int[length];
    long numofinversions = mergesort(array, blank, 0, length-1);
    return numofinversions;

}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    if (low < high){
        long counter = 0;
        int mid = low + (high - low)/2;
        counter += mergesort(array, scratch, low, mid);
        counter += mergesort(array, scratch, mid + 1, high);
        int L = low;
        int H = mid + 1;
        for (int k = low; k <= high; k++){
            if (L <= mid && (H > high || array[L] <= array[H])){
                scratch[k] = array[L];
                L++;
            } else {
                counter += (mid + 1 - L);
                scratch[k] = array[H];
                H++;
            }
        }
        for (int i = low; i <= high; i++){
            array[i] = scratch[i];
        }
        return counter;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    if (argc == 0 || argc > 2){
        cout << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }
    if (argc == 2){
        string slow = argv[1];
        if(slow != "slow") {
            cout << "Error: Unrecognized option '" << slow <<"'." << endl;
            return 1;
        }
    }
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
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
    if (values.empty()){
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    int lengthofarray = values.size();
    if (argc == 2){
        cerr << "Number of inversions: "<< count_inversions_slow(&values[0], lengthofarray) << endl;
        return 0;
        }
    else{
        cerr << "Number of inversions: "<< count_inversions_fast(&values[0], lengthofarray) << endl;
        return 0;
    }

}
