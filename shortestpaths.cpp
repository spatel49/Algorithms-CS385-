/*******************************************************************************
 * Name        : shortestpath.cpp
 * Author      : Siddhanth Y. Patel and Ethan Foskey
 * Date        : November 25, 2019
 * Description : Solves the all pairs shortest paths problem with Floyd’s algorithm.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <iomanip>
#include <typeinfo>
#include <string>
#include <map>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include<bits/stdc++.h>
#include <iterator>
#include <algorithm>

using namespace std;

long num_vertices = 0;
const long INF = std::numeric_limits<long>::max();
long** distancematrix;
long** matrix2;
long** matrix3;

/**
* Displays the matrix on the screen formatted as a table.
*/

int len(int value) {
     //  determine how many digits are in an integer
    int counter = 1;
    while(value >= 10){
       	counter++;
    	value = value / 10;
    }
    return value;
}

/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(long** const matrix, const string &label, long num_vertices, const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
	int max_cell_width = to_string(max(static_cast<long>(num_vertices - 1), max_val)).length();
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == INF) {
			cout << "-";
		} else if (use_letters) {
			cout << static_cast<char>(matrix[i][j] + 'A');
		} else {
			cout << matrix[i][j];
		}
	}
	cout << endl;
 }
 cout << endl;
}

vector<char> backtracker(int x, int y, long** matrix2, long** m3, long num_vertices){
    vector<char> left;
    if(m3[x][y] == m3[0][0]){
        char aChar = 'A' + x;
        char bChar = 'A' + y;
        left.push_back(bChar);
        if(aChar != bChar){
            left.push_back(aChar);
        }
        return left;
    }else{
        left = backtracker(x,matrix3[x][y], matrix2, m3, num_vertices);
        vector<char> right = backtracker(matrix3[x][y],y, matrix2, m3, num_vertices);
        right.insert(right.end(), left.begin()+1, left.end());
        return right;
    }
}

void floyds_alg(long** matrix1, long num_vertices){
    matrix2 = new long*[num_vertices];
    matrix3 = new long*[num_vertices];
    for(int i = 0; i < num_vertices; i++){
        matrix2[i] = new long[num_vertices];
        matrix3[i] = new long[num_vertices];
        fill_n(matrix3[i],num_vertices,INF);
    }
    for (int i = 0; i < num_vertices; i++){
        for (int j = 0; j < num_vertices; j++){
            matrix2[i][j] = matrix1[i][j];
        }
    }
    for (int k = 0; k < num_vertices; k++){
        for (int i = 0; i< num_vertices; i++){
            for (int j = 0; j < num_vertices; j++){
                if (matrix2[i][k] != INF && matrix2[k][j] != INF && matrix2[i][k] + matrix2[k][j] < matrix2[i][j]){
                    matrix2[i][j] = matrix2[i][k] + matrix2[k][j];
                    matrix3[i][j] = k;
                }
            }
        }
    }
    display_table(matrix1, "Distance matrix:", num_vertices, false);
    display_table(matrix2, "Path lengths:", num_vertices, false);
    display_table(matrix3, "Intermediate vertices:", num_vertices, true);
    vector<char> vectorpath;
	for(int i = 0; i < num_vertices; i++){
	    char aChar = 'A' + i;
		for(int j = 0; j < num_vertices; j++){
		    char bChar = 'A' + j;
            if (i==j){ // A->A
                cout << aChar << " -> " << bChar << ", distance: 0, path: " << aChar << endl;
            } else{
			vectorpath = backtracker(i,j, matrix2, matrix3, num_vertices);
			reverse(vectorpath.begin(),vectorpath.end());
			cout << aChar << " -> " << bChar << ", distance: ";
			if(matrix2[i][j] != INF){
				cout << matrix2[i][j] << ", path: " << vectorpath.at(0);
				for(unsigned int y = 1; y < vectorpath.size(); y++){
					cout << " -> " << vectorpath.at(y);
				}
			}
			else {
				cout << "infinity, path: none";
			}
			cout << endl;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    string line;
    vector<string> inputfile;
    ifstream myfile (argv[1]);
    if (myfile.is_open()){
        int i = 0;
        while (getline(myfile,line)){
           inputfile.push_back(line);
           i++;
        }
        myfile.close();
    } else {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // store all strings in a map with frequency of 1
    map<string, int> infomap;
    for (unsigned int i = 1; i < inputfile.size(); i++){
        if (infomap.find(inputfile[i])==infomap.end()){
            infomap.insert(pair<string,int>(inputfile[i], 1));
        }
    }
    string firstchecker = inputfile[0];
    bool firstcheck = true;
    for (long unsigned int jello = 0; jello < firstchecker.length(); jello++){
        if (isdigit(firstchecker[jello])==false){
            firstcheck = false;
        }
    }
    if (firstcheck == false){
        cerr << "Error: Invalid number of vertices '" << inputfile[0] << "' on line 1.";
        return 1;
    }
    int num_vertices = stoi(inputfile[0]);
    char asciiChar = 64 + num_vertices;
    if (num_vertices > 26 || num_vertices < 1){
        cerr << "Error: Invalid number of vertices '" << num_vertices << "' on line 1.";
        return 1;
    }
    for (unsigned int i = 1; i < inputfile.size(); i++){
        int numofspaces = 0;
        string inputline = inputfile[i];
        for (long unsigned int j = 0; j < inputline.length(); j++){
            string chartostring(1, inputline.at(j));
            if (chartostring == " "){
                numofspaces++;
            }
        }
        if (inputline.size() < 5 || numofspaces != 2){ // CHECKS FOR 3 components separated by 2 spaces
            cerr << "Error: Invalid edge data '" << inputline << "' on line " << i+1 << ".";
            return 1;
        }
        string chartostringone(1, inputline.at(1));
        string chartostringthree(1, inputline.at(3));
        string chartostringfour(1, inputline.at(4));
        string invalidstartvertex = "";
        string invalidendvertex = "";
        for (long unsigned int x = 0; x < inputline.length(); x++){
            if (inputline.at(x)== ' '){
                break;
            }
            invalidstartvertex += inputline[x];
        }
        for (long unsigned int x = 2; x < inputline.length(); x++){
            if (inputline.at(x) == ' '){
                break;
            }
            invalidendvertex += inputline[x];
        }
        if (inputline.at(0) < 65 || inputline.at(0) > (64 + num_vertices) || chartostringone != " "){
            cerr << "Error: Starting vertex '"<< invalidstartvertex <<"' on line "<< i+1 <<" is not among valid values A-"<< asciiChar <<".";
            return 1;
        }
        if (inputline.at(2) < 65 || inputline.at(2) > (64 + num_vertices) || chartostringthree != " "){
            cerr << "Error: Ending vertex '"<< invalidendvertex <<"' on line "<< i+1 <<" is not among valid values A-"<< asciiChar <<".";
            return 1;
        }
        if (chartostringfour == "-" || chartostringfour == "0"){
            string invalidweight = "";
            for (long unsigned int x = 4; x < inputline.length(); x++){
                invalidweight += inputline[x];
            }
            cerr << "Error: Invalid edge weight '"<< invalidweight <<"' on line "<< i+1 << ".";
            return 1;
        }
        string weightchecker = chartostringfour;
        for (long unsigned int i = 5; i < inputline.length(); i++){
            weightchecker += inputline[i];
        }
        bool weightcheck = true;
        for (long unsigned int j = 0; j < weightchecker.length(); j++){
            if (isdigit(weightchecker[j])==false){
                weightcheck = false;
            }
        }
        if (!weightcheck){
            cerr << "Error: Invalid edge weight '"<< weightchecker <<"' on line "<< i+1 << ".";
            return 1;
        }
    }
    distancematrix = new long*[num_vertices];
    for(int i = 0; i < num_vertices; i++){
        distancematrix[i] = new long[num_vertices];
        for(int j = 0; j < num_vertices; j++){
            if (i==j){
                distancematrix[i][j]=0;
            } else{
                distancematrix[i][j] = INF;
            }
        }
    }
    for(map<string,int>::const_iterator it = infomap.begin(); it != infomap.end(); ++it) {
        string inputweight = "";
        unsigned int i = 4;
        while (i < (it->first).length()){
            inputweight += (it->first).at(i);
            i++;
        }
        distancematrix[(it->first).at(0)-65][(it->first).at(2)-65] = stoi(inputweight);
    }
    floyds_alg(distancematrix, num_vertices);
    //listofpaths();
    for(int i=0; i < num_vertices; i++){
		delete[] distancematrix[i];
		delete[] matrix2[i];
		delete[] matrix3[i];
	}
	delete[] distancematrix;
	delete[] matrix2;
	delete[] matrix3;
	return 0;
}
