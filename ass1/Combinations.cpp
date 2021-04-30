/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

int c(int n, int k);

int main() {
	int n = getInteger("Enter n: ");
	int k = getInteger("Enter k: ");
    cout << "C = " << c(n, k) << endl;
    return 0;
}

//Counts combination with c and k recursively
int c(int n, int k) {
	if (k == 0 || n == k) {
		return 1;
	}
	return c(n - 1, k - 1) + c(n - 1, k);
}