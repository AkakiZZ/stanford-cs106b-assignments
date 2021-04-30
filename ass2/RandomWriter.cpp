/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "map.h"
#include "vector.h"
#include "random.h"
#include <fstream>
#include <cstring>

using namespace std;

const int K_MIN = 1;
const int K_MAX = 10;
const int N_SYMBOLS = 2000;

void getSettings(ifstream &file, int &k);
void analyseData(Vector<char> &chars, Map<string, Vector<char> > & map, int k);
void writeRandomText(Map<string, Vector<char> > & map, int k);
string getMostFrequentSequence(Map<string, Vector<char> > & map);

int main() {
	ifstream file;
	int k;

	getSettings(file, k); // get file and k-th order
	cout << "Processing data..." << endl;

	Map<string, Vector<char> > map; 
	Vector<char> chars;
	char ch;

	while (file.get(ch)) { // read characters
		chars.add(ch);
	}

	if (chars.size() <= k) {
		cout << "Not enough data" << endl;
	} else {
		analyseData(chars, map, k); // save data in collections
		writeRandomText(map, k); // write random text
	}

    return 0;
}

// Lets the user to input filename and the order
void getSettings(ifstream &file, int &k) {
	string filename = getLine("Enter file name: ");
	file.open(filename.c_str());

	while (file.fail()) {
		filename = getLine("Can't Open File. Try Again: ");
		file.clear();
		file.open(filename.c_str());
	}

	k = getInteger("Enter model [1 - 10]: ");

	while (k < K_MIN || k > K_MAX) {
		k = getInteger("Enter integers from 1 to 10");
	}
}

//Saves data in map
void analyseData(Vector<char> &chars, Map<string, Vector<char> > & map, int k) {
	for (int i = 0; i < chars.size() - k + 1; i++) {

		string lastSequence = "";
		char nextChar = '0';

		// if char is not last
		if (i != chars.size() - k)
			nextChar = chars[i + k];
		
		//generate sequence
		for (int j = 0; j < k; j++) {
			lastSequence += chars[i + j];
		}

		if (!map.containsKey(lastSequence)) {
			Vector<char> vec;
			if (i != chars.size() - k)
				vec += nextChar;
			map.put(lastSequence, vec);
		} else if (i != chars.size() - k) {
			map[lastSequence].add(nextChar);
		}
	}
}

// writes the text
void writeRandomText(Map<string, Vector<char> > & map, int k) {

	string sequence = getMostFrequentSequence(map);

	for (int i = 0; i < N_SYMBOLS - k; i++) {
		//get next char by generating random index of sequence's mapped vector
		char nextChar = map[sequence].get(randomInteger(0, map[sequence].size() - 1));

		cout << nextChar;
		sequence = sequence.substr(1) + nextChar; //new sequence
		
		// if program has no more than one choice stop printing
		if (map[sequence].isEmpty())
			break;
	}

	cout << endl;
}

//Returns the most frequent sequence in the text
string getMostFrequentSequence(Map<string, Vector<char> > & map) {
	int maxSize = 0;
	string res;
	foreach(string key in map) {
		if (map[key].size() > maxSize) {
			maxSize = map[key].size();
			res = key;
		}
	}
	return res;
}