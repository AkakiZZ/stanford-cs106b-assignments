/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

string flipCoin();

int main() {
    int flips = 0;
	int ConsecutiveHeads = 0;
	while (heads < 3) {
		string res = flipCoin();
		cout << res << endl;
		if (res == "heads") {
			ConsecutiveHeads++;
		} else {
			ConsecutiveHeads = 0;
		}
		flips++;
	}
	cout << "It took " << flips << " flips to get 3 consecutive heads." << endl;

    return 0;
}

//Simulates coin flipping
string flipCoin() {
	if (randomChance(0.50)) {
		return "heads";
	}
	return "tails";
}


