/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
	string s1 = getLine("Enter string: ");
	string s2 = getLine("Enter subseqeuence: ");
	if (isSubsequence(s1, s2)) {
		cout << "true" << endl;
	} else {
		cout << "false" << endl;
	}
    
    return 0;
}

bool isSubsequence(string text, string subsequence) {
	if (subsequence == "") {
		return true;
	} else if (text == "") {
		return false;
	}
	if (text[0] == subsequence[0]) {
		return isSubsequence(text.substr(1), subsequence.substr(1));
	} else {
		return isSubsequence(text.substr(1), subsequence);
	}
}
