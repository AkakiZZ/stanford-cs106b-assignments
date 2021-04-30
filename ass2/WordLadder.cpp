/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "vector.h"
#include "set.h"
#include "lexicon.h"
#include "queue.h"


using namespace std;
Vector<string> getShortestPath(string &startingWord, string &endingWord, Lexicon & words);
Set<string> changedByOne(string & word, Lexicon & words);

int main() {
	string first = getLine("Enter a starting word: ");
	string last = getLine("Enter an ending word: ");
	Lexicon words("EnglishWords.dat");
	Vector<string> res;
	
	// if input strings are english words get the shortest path
	if (words.contains(first) && words.contains(last))
		res = getShortestPath(first, last, words);

	if (res.isEmpty()) {
		cout << "There is no path" << endl;
	} else {
		cout << "Found a ladder: ";
		for (int i = 0; i < res.size(); i++) {
			cout << res.get(i) << " ";
		} 
		cout << endl;
	}
	return 0;
}

//returns set of all words that can be made by changing one char of the passed word
Set<string> changedByOne(string & word, Lexicon & words) {
	Set<string> res;
	for (int i = 0; i < word.length(); i++) {
		for (char j = 'a'; j <= 'z'; j++) {
			string temp = word;
			temp[i] = j;
			if (words.contains(temp)) {
				res += temp;
			}
		}
	}
	return res;
}


// returns the shortest path
Vector<string> getShortestPath(string &startingWord, string &endingWord, Lexicon & words) {
	Queue<Vector<string> > queue;
	Vector<string> v;
	v += startingWord;
	queue.enqueue(v);

	Set<string> usedWords;

	while (!queue.isEmpty()) {
		Vector<string> path = queue.dequeue();

		if (path[path.size() - 1] == endingWord)
			return path;
		
		Set<string> set = changedByOne(path[path.size() - 1], words);
		foreach (string s in set) {
			if (!usedWords.contains(s)) {
				Vector<string> newPath = path;
				newPath += s;
				usedWords += s;
				queue.enqueue(newPath);
			}
		}
	}
	Vector<string> emptyPath;
	return emptyPath;
}
