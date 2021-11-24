//Editor.h file
//CSC 326
//VI EDITOR PHASE 1
//GROUP MEMBERS: DEANNA MANDARINO, VICTORIA JACZYNSKI, SIMON CHRISTIAN, BILL ZHOU

// Task: Write an Editor class that has an instance of our LinkedList
// Use command line arguments - the user will specify the file (if it exists)
// Code a constructor for the Editor class with one parameter for the file name - read it in and add to the linked list 
// Allow for the following commands:  :q   :w

#include "Position.h"
#include "LinkedList.h"
#include <Windows.h>
#include <string>
#include <fstream>
#ifndef EDITOR_H
#define EDITOR_H
using namespace std;

class Editor {
public:
	/*Default Constructor*/
	Editor();
	/*General Constructor*/
	Editor(string _fileName);
	/*Displays Lines*/
	void displayLines();
	/*Runs the program*/
	void run();
private:
	fstream inFile;
	LinkedList<string> lines;
	string fileName;
	string* keyWords;
	const int numKeywords = 60;
	Position cursor;
};
#include "Editor.cpp"
#endif
