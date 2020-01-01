/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Siddhanth Y. Patel
 * Date        : September 29, 2019
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> ways;
    vector<int> none;
    if (num_stairs <= 0) {
        ways.push_back(none);
    }
    else {
        for (int i = 1; i <= 3 ; i ++) {
            vector<vector<int>> result = get_ways(num_stairs - i);
            if (num_stairs >= i) {
                for (unsigned int j = 0; j < result.size(); j++) {
                    result.at(j).push_back(i);
                    ways.push_back(result.at(j));
                }
            }
            sort(ways.begin(), ways.end());
        }
    }
    return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int spaces = 0;
    unsigned int x = 1;
    while (ways.size() >= x) {
	    spaces ++;
	    x *= 10;
	    }
    for (unsigned int i = 0; i < ways.size(); i++) {
        cout << setw(spaces) << (i+1) << ". [";
        for (unsigned int j = 0; j < ways[i].size(); j++){
            if (j == ways[i].size() - 1){
                cout << ways[i][j] << "]" << endl;
            }
            else {
                cout << ways[i][j] << ", ";
            }
        }
    }
}

int main(int argc, char * const argv[]) {
    int numberofstairs;
    if (argc == 1) {
        cerr << "Usage: ./stairclimber <number of stairs>";
        return 1;
    }
    if (argc > 2) {
        cerr << "Usage: ./stairclimber <number of stairs>";
        return 1;
    }
    istringstream iss(argv[1]);
    if (!(iss >> numberofstairs)){
        cerr << "Error: Number of stairs must be a positive integer.";
        return 1;
    }
    if (numberofstairs <= 0) {
        cerr << "Error: Number of stairs must be a positive integer.";
        return 1;
    }
    vector<vector<int>> full_list;
    full_list = get_ways(numberofstairs);
    if (numberofstairs == 1) {
        cout << "1 way to climb 1 stair." <<endl;
        cout << "1. [1]";
        return 0;
    }
    else {
        cout << full_list.size() << " ways to climb " << argv[1] << " stairs." <<endl;
        display_ways(full_list);
        return 0;
    }
}
