/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "simpio.h"
#include "tokenscanner.h"
using namespace std;

// Constants
const double c0 = -15.59;
const double c1 = 0.39;
const double c2 = 11.8;

bool isLatinCharacter(char ch);
void inputFile(ifstream & file);
int countSentences(ifstream & file, string & str);
int countWords(string str);
int countSyllables(string str);
double calculateGrade(int sentences, int words, int syllables);
bool isVowel(char ch);


int main() {
    ifstream file;
	inputFile(file);
	string str = "";
	int sentences = countSentences(file, str);
	int words = countWords(str);
	int syllables = countSyllables(str);
	cout << "Grade: " << calculateGrade(sentences, words, syllables) << endl;
    return 0;
}

// Lets the user to enter filename
void inputFile(ifstream & file) {
	string filename = getLine("Enter Filename: ");
	file.open(filename.c_str());
	if(file.fail()) {
		filename = getLine("Can't Open File. Try Again: ");
		file.clear();
		file.open(filename.c_str());
	}
}

// 
bool isLatinCharacter(char ch) {
	if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
		return true;
	}
	return false;
}

// Counts sentences in the given file
int countSentences(ifstream & file, string & str) {
	int sentences = 0;
	char ch;
	while(file.get(ch)) {
		if (ch == '?' || ch == '.' || ch == '!') {
			sentences++;
		}
		str += ch;
	}
	if (sentences == 0)
		return 1;
	return sentences;
}

// Counts words in a string
int countWords(string str) {
	int words = 0;
	TokenScanner scanner(str);
	scanner.ignoreWhitespace();
	scanner.addWordCharacters("\'");
	while (scanner.hasMoreTokens()) {
		string word = scanner.nextToken();
		if (word.length() > 0  && (isLatinCharacter(word[0]))){
			words++;
		}
	}
	if (words == 0)
		return 1;
	return words;
}

// Counts syllables in a string
int countSyllables(string str) {
	int counter = 0;
	TokenScanner scanner(str);
	scanner.ignoreWhitespace();
	scanner.addWordCharacters("\'");
	while (scanner.hasMoreTokens()) {
		string word = scanner.nextToken();
		if (word.length() == 1 && isLatinCharacter(word[0])) {
			counter++;
		} else if (word.length() > 1 && isLatinCharacter(word[0])) {
			int cnt = 0; // Syllables in the given word
			char lastChar = word[word.length() - 1];
			for (int i = 0; i < word.length() - 1; i++) {
				//If the char on this index is vowel and next char isn't vowel, increase amount of syllables by one 
				if (isVowel(word[i]) && !isVowel(word[i + 1])) {
					cnt++;
				}
			}
			// if last char is 'e' or 'E' and previous char is vowel, increase amount of syllables by one
			if ((lastChar == 'e'  || lastChar == 'E') && isVowel(word[word.length() - 2])) cnt++;

			// if last char is vowel but not 'e' nor 'E', increase amount of syllables by one
			if (lastChar != 'e'  && lastChar != 'E' && isVowel(lastChar)) cnt++;

			// if amount of syllables still is 0 in a word add 1. For words such as "the"
			if (cnt == 0) cnt = 1;
			counter += cnt;
		}
		
	}
	return counter;
}

// Tells if a char is a vowel
bool isVowel(char ch) {
	if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'u' || ch == 'y' || ch == 'o' ||
		ch == 'A' || ch == 'E' || ch == 'I' || ch == 'U' || ch == 'Y' || ch == 'O') {
		return true;
	}
	return false;
}

// Calculates the final result
double calculateGrade(int sentences, int words, int syllables) {
	return c0 + c1 * (words / double(sentences)) + c2 * (syllables / double(words));
}

