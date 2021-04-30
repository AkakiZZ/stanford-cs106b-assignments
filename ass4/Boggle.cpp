/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <cmath>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "set.h"
using namespace std;

/* Constants */
const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const int CUBE_FACES = 6;
const int MIN_SIZE_OF_WORD = 4;
const int SCORE_DIFF = 3;
const int NUM_ROWS = 4;
const int NUM_COLS = 4;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};


Lexicon words("EnglishWords.dat");

/* Function prototypes */
void welcome();
void giveInstructions();
void drawGraphicalBoard(Grid<char> &board);
void permutateCubes(Vector<string> & v);
void fillUpBoard(Vector<string> &permutations, Grid<char> &board);
Vector<string> arrToVector(const string arr[], int size);
bool wantsCustomInput(); 
Vector<string> userInput();
void getAllPossible(string soFar, Grid<char> &board, Set<string> &foundWords);
void getAllPossibleFromThisChar(string soFar, Grid<char> &board, Grid<bool> &isUsed, 
					Set<string> &res, Set<string> &foundWords, int row, int col);
bool canCreate(string word, Grid<char> &board);
bool recSearch(string word, Grid<bool> &isUsed, Grid<char> &board, int row, int col);
Set<string> getWords(Grid<char> &board);
int calculateScore(string word);
void unHighlightAll(Grid<char> &board);
bool wantsPlayAgain();
void initNewGame(GWindow &gw);
void playGame(Grid<char> &board, GWindow &gw);

/* Main program */
int main() {
	GWindow gw;
    initNewGame(gw);
    return 0;
}

/*
* Starting a new game
* Makes a new GWindow
* Initializes GBogle
* Creates a new board to play
*/
void initNewGame(GWindow &gw) {
    initGBoggle(gw);
	
	Grid<char> board(NUM_ROWS, NUM_COLS);
	
	drawGraphicalBoard(board);

    welcome();
    giveInstructions();

	Vector<string> permutations;

	if (wantsCustomInput()) {
		permutations = userInput();
	} else {
		permutations = arrToVector(STANDARD_CUBES, NUM_ROWS * NUM_COLS);
	}
	
	permutateCubes(permutations);
	fillUpBoard(permutations, board);

	playGame(board, gw);
}

/*
* Whole gameplay proccess after initializing board
* 1) Player's turn
* 2) Computer's turn
* 3) Ask for play again
*/
void playGame(Grid<char> &board, GWindow &gw) {
	drawGraphicalBoard(board);

	Set<string> foundWords = getWords(board);

	getAllPossible("", board, foundWords);

	if(wantsPlayAgain()) initNewGame(gw);
}

/*
* Returns true if the player wants to play again
*/
bool wantsPlayAgain() {
	string choice = getLine("Do you want to play again? enter Y if yes or anything if no ");
	if (choice == "Y" || choice == "y") return true;
	return false;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */
void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */
void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

/*
* Lets the user to input custom cube strings line by line
*/
Vector<string> userInput(){
	int numCubes = getInteger("How many cubes do you want? ");
	Vector<string> v;
	for (int i = 0; i < numCubes; i++) {
		v += getLine();
	}
	return v;
}

/*
* Returns true if the user wants custom input
*/
bool wantsCustomInput() {
	string choice = getLine("Do you want custom cubes? enter Y if yes or anything if no ");
	if (choice == "Y" || choice == "y") return true;
	return false;
}

/*
* Draws the board with it's chars
*/
void drawGraphicalBoard(Grid<char> &board) {
	drawBoard(board.numRows(), board.numCols());

	for (int i = 0; i < board.numRows(); i++) {
		for (int j = 0; j < board.numCols(); j++) {
			labelCube(i, j, board[i][j]);
		}
	}
}

/*
* Recieves an array and returns a vector
*/
Vector<string> arrToVector(const string arr[], int size) {
	Vector<string> v;
	for (int i = 0; i < size; i++) {
		v += arr[i];
	}
	return v;
}

/*
* Shuffles cubes
*/
void permutateCubes(Vector<string> & v) {
	for(int i = 0; i < v.size(); i++) {
		int x = randomInteger(i, v.size() - 1);
		string tmp = v[i];
		v[i] = v[x];
		v[x] = tmp;
	}
}

/*
* Fills up the board with chars
*/
void fillUpBoard(Vector<string> &permutations, Grid<char> &board) {
	for (int i = 0; i < board.numRows(); i++) {
		for (int j = 0; j < board.numCols(); j++) {
			board[i][j] = permutations[i * board.numRows() + j][randomInteger(0, CUBE_FACES - 1)];
		}
	}
}

/*
* Gets all of the possible words that can be created on a given board
*/
void getAllPossible(string soFar, Grid<char> &board, Set<string> &foundWords) {
	Set<string> res;
	for (int i = 0; i < board.numRows(); i++) {
		for (int j = 0; j < board.numCols(); j++) {
			Grid<bool> isUsed(board.numCols(), board.numRows());
			getAllPossibleFromThisChar("", board, isUsed, res, foundWords, i, j);
		}
	} 
}

/*
* Helper function of getAllPossible()
* Searchs through every possible word that can be created from a certain position
*/
void getAllPossibleFromThisChar(string soFar, Grid<char> &board, Grid<bool> &isUsed,
					Set<string> &res, Set<string> &foundWords, int row, int col) {
	if (!words.containsPrefix(soFar))
		return;
	if (words.contains(soFar) && soFar.size() >= MIN_SIZE_OF_WORD && 
		!res.contains(soFar) && !foundWords.contains(soFar)) {
		recordWordForPlayer(soFar, COMPUTER);
		res += soFar;
	}
	for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (board.inBounds(i, j) && !isUsed[i][j]) {
                isUsed[i][j] = true;
                getAllPossibleFromThisChar(soFar + board[i][j], board, isUsed, res, foundWords, i, j);
                isUsed[i][j] = false;
            }
        }
    }
}

/*
* Returns if it is possible to create word on a given board
*/
bool canCreate(string word, Grid<char> &board) {
	if (!words.contains(word) || word.size() < MIN_SIZE_OF_WORD) return false;
	for (int i = 0; i < board.numRows(); i++) {
		for (int j = 0; j < board.numCols(); j++) {
			Grid<bool> isUsed(board.numRows(), board.numCols());
			if(recSearch(word, isUsed, board, i, j)) return true;
		}
	}
	return false;
}	

/*
* Backtracking helper function of CanCreate()
*/ 
bool recSearch(string word, Grid<bool> &isUsed, Grid<char> &board, int row, int col) {
	if (word == "") return true;
	highlightCube(row, col, true);
	if (word[0] == board[row][col] && !isUsed[row][col]) {

		isUsed[row][col] = true;
		for (int i = row - 1; i <= row + 1; i++) {
			for (int j = col - 1; j <= col + 1; j++) {
				if (board.inBounds(i, j) && !isUsed[i][j] &&
					recSearch(word.substr(1), isUsed, board, i, j)) {
					return true;
				}
			}
		}
		isUsed[row][col] = false;
	}
	highlightCube(row, col, false);
	return false;
}

/*
* Lets the user to input words
* Returns set of inputed words, which are possible to create
*/
Set<string> getWords(Grid<char> &board) {
	Set<string> res;
	string word = getLine("Enter A Word: ");
	if (canCreate(toUpperCase(word), board)) {
		if (!res.contains(toUpperCase(word))) recordWordForPlayer(word, HUMAN);
		res += toUpperCase(word);
	}
	while (word != "") {
		word = getLine("Enter A Word: ");
		unHighlightAll(board);
		if (canCreate(toUpperCase(word), board)) {
			if (!res.contains(toUpperCase(word))) recordWordForPlayer(word, HUMAN);
			res += toUpperCase(word);
		}
	}
	return res;
}

/*
* Unhighlights all the cubes on the board
*/
void unHighlightAll(Grid<char> &board) {
	for (int i = 0; i < board.numRows(); i++) {
		for (int j = 0; j < board.numCols(); j++) {
			highlightCube(i, j, false);
		}
	}
}