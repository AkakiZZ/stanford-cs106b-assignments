/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"

using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);
int pow(int n, int k);

/* Main program */

int main() {
    return 0;
}

string intToString(int n) {
	if (n < 0) {
		return string("-") + intToString(-1 * n);
	}
	if (n < 10) {
		return string() + char(n + '0');
	}
	return intToString(n / 10) + char(n % 10 + '0');
}

int stringToInt(string str) {
	if (str[0] == '-') {
		return -1 * stringToInt(str.substr(1));
	} 
	if (str.length() < 2) {
		return str[0] - '0';
	}
	return (str[0] - '0') * pow(10, str.length() - 1) + stringToInt(str.substr(1));
}

// Calculates n^k
int pow (int n, int k) {
	int ans = 1;
	for (int i = 1; i <= k; i++) {
		ans *= n;
	}
	return ans;
}
