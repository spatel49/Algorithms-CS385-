/*******************************************************************************
 * Name        : anagramfinder.cpp
 * Author      : Siddhanth Y. Patel
 * Version     : 1.0
 * Date        : November 12, 2019
 * Description : Finds and lists anagrams in a dictionary.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <map>
#include <typeinfo>
#include <bits/stdc++.h>

using namespace std;

void findanagrams(const vector<string> &dictionary, map<int, int> &Casemap){
    int counterr = 1;
    map<string, int> mapc;
    for (long unsigned int i = 0; i < dictionary.size(); i++){
        int product = 1;
        string currentword = dictionary[i];
        if (!(mapc.find(currentword)==mapc.end())){ //add to an already present group
            product = mapc.find(currentword)->second;
            for (long unsigned int k = 0; k < currentword.length(); k++){
                if (Casemap.find(currentword[k])==Casemap.end()){
                    break;
                }
                product = product * Casemap.at(currentword[k]);
            }
            mapc.find(currentword)->second = product;
        } else {
            for (long unsigned int k = 0; k < currentword.length(); k++){
                if (Casemap.find(currentword[k])==Casemap.end()){
                    break;
                }
                product = product * Casemap.at(currentword[k]);
                if (k+1 == currentword.length()){
                    mapc.insert(pair<string,int>(currentword, product));
                }
            }
        }
    }
    map <int, vector<string> > segList;
    for (std::map<string,int>::iterator it=mapc.begin(); it!=mapc.end(); ++it){
        if (!(segList.find(it->second)==segList.end())){ //add to an already present group
           vector<string> words;
           words = segList.find(it->second)->second;
           words.push_back(it->first + "\n");
           segList.find(it->second)->second = words;
        }else{
            vector<string> words; // create new group
            int xp = (it->first).size();
            if (xp == 1){ //if value is a character
                int newtotalval = it->second;
                string holder = it->first;
                int numofprints = log(newtotalval) / log(Casemap.at(holder[0]));
                if (numofprints > 1){
                    for (int z = 0; z < numofprints; z++){
                        words.push_back(it->first + "\n");
                    }
                    segList.insert(pair<int, vector<string> >(it->second, words));
                }
            } else {
                words.push_back(it->first + "\n");
                segList.insert(pair<int, vector<string> >(it->second, words));
            }
        }
    }
    int counter = 0; // can make this faster
    for (std::map<int, vector<string> >::iterator it=segList.begin(); it!=segList.end(); ++it){
            vector<string> finalwords = it->second;
            int xl = (it->second).size();
            if (finalwords.size()>1){
                counter = max(counter, xl);
            }
    }
    long unsigned int counterfinal = counter;
    vector <string> upperfinalwords;
    vector <string> lowerfinalwords;
    if (counterfinal ==0) {
        cout << "No anagrams found." <<endl;
    }else {
        cout << "Max anagrams: " << counter << endl;
        std::map<int, vector<string> >::reverse_iterator rit = segList.rbegin();
        for (std::map<int, vector<string> >::iterator it=segList.begin(); it!=segList.end(); ++it){
            vector<string> finalwords = it->second;
            if (finalwords.size() ==counterfinal && it->first != rit->first){
                for (long unsigned int i = 0; i < finalwords.size(); i++){
                    string exam = finalwords[0];
                    if (exam[0] >= 65 && exam[0] <=90){
                        upperfinalwords.push_back(finalwords[i]);
                    }else{
                        lowerfinalwords.push_back(finalwords[i]);
                    }
                }
                //upperfinalwords.push_back("\n");
                lowerfinalwords.push_back("\n");
            } else if (finalwords.size() ==counterfinal){ // last anagram group
                for (long unsigned int i = 0; i < finalwords.size(); i++){
                    string exam = finalwords[0];
                    if (exam[0] >= 65 && exam[0] <=90){
                        upperfinalwords.push_back(finalwords[i]);
                        counterr++;
                        //cout << counterr << endl;
                        if (counterr == 4) {
                           upperfinalwords.push_back("\n");
                        }
                    }else{
                        lowerfinalwords.push_back(finalwords[i]);

                    }
                }
            }
        }
    }
    for (long unsigned int i = 0; i < upperfinalwords.size(); i++){
        //string blank = upperfinalwords[0];
       // if (Casemap.find(blank[0])==Casemap.end()){
       //     cout << "";
       // }else{
            cout << upperfinalwords[i];
       // }
    }
    for (long unsigned int j = 0; j< lowerfinalwords.size(); j++){
        cout << lowerfinalwords[j];
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1 || argc > 2){
        cout << "Usage: ./anagramfinder <dictionary file>" << endl;
        return 1;
    }
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107};
    map<int, int> Casemap;
    int y = 0;
    for (int x = 65; x <= 90; x++){
        Casemap.insert(pair<int,int>(x, primes[y]));
        y++;
    }
    int yy = 0;
    for (int x = 97; x <= 122; x++){
        Casemap.insert(pair<int,int>(x, primes[yy]));
        yy++;
    }
    string line;
    vector<string> inputfile;
    ifstream myfile ("words.txt");
    if (myfile.is_open()){
        int i = 0;
        while (getline(myfile,line)){
           inputfile.push_back(line);
           i++;
        }
        myfile.close();
        findanagrams(inputfile, Casemap);
        return 0;
    } else {
        cout << "Error: File 'nofile.txt' not found." << endl;
        return 1;
    }
}
