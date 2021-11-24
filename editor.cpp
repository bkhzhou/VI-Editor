//Editor.cpp file
//CSC 326
//VI EDITOR PHASE 1
//GROUP MEMBERS: DEANNA MANDARINO, VICTORIA JACZYNSKI, SIMON CHRISTIAN, BILL ZHOU
// Task: Write an Editor class that has an instance of our LinkedList
// Use command line arguments - the user will specify the file (if it exists)
// Code a constructor for the Editor class with one parameter for the file name - read it in and add to the linked list 
// Allow for the following commands:  :q   :w


#include "Editor.h"
#include "ListInterface.h"
#include "Position.h"
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
int binarySearch(string*& keyWords, int first, int last, string word);
void placeCursorAt(Position coordinate); //function prototype
void colorText(int value);
using namespace std;

Editor::Editor() {
}//end default constructor

Editor::Editor(string _fileName) {
	ifstream inFile(_fileName);
	string readLine;
	fileName = _fileName;
	int lineCounter = 1;

	/*Exits when file is not found*/
	if (inFile.fail()) {
		cout << "File cannot be found.";
		exit(1);
	}
	/*Reads each line of the file*/
	while (!inFile.eof()) {
		getline(inFile, readLine);
		lines.insert(lineCounter, readLine);
		lineCounter++;
	}
	
	ifstream keywordsList;
	keywordsList.open("keywords.txt");
	int arraySize = 0;
	keyWords = new string[numKeywords];
	while (!keywordsList.eof()) {
		getline(keywordsList, keyWords[arraySize]);
		arraySize++;
	}

}
//void Editor::displayLines() {
//	/*Clear screen to display text file*/
//	system("CLS");
//	for (int i = 1; i < lines.getLength(); i++) {
//		cout << lines.getEntry(i) << endl;
//	}
//}
int binarySearch(string*&keyWords, int first, int last, string word) //function definition
{
	int index;
	if (first > last)
		index = -1;
	else
	{
		int mid = first + (last - first) / 2;
		if (word == keyWords[mid])
			index = mid;
		else if (word < keyWords[mid])
			index = binarySearch(keyWords, first, mid - 1, word);
		else
			index = binarySearch(keyWords, mid + 1, last, word);
	}
	return index;
}
void Editor::displayLines()
{
	int position;
	string nextLine, nextWord, line;

	system("CLS");

	// goes through each line in the linked list 
	for (position = 1; position <= lines.getLength(); position++)
	{
		nextLine = lines.getEntry(position);

		int i = 0;
		while (i < nextLine.length()) {
			string word;
			// isolate a word at a time (can contain underscores)
			if (isalpha(nextLine[i])) {
				while (isalpha(nextLine[i]) || nextLine[i] == '_') {
					word += nextLine[i];
					i++;
				}
				if (binarySearch(keyWords, 0, numKeywords - 1, word) != -1)  //found
					colorText(3);
				else
					colorText(15);
				cout << word;
			}

			else {
				colorText(15);
				cout << nextLine[i];
				i++;
			}

		}
		cout << endl;
	}
	placeCursorAt(cursor);
} // end displayLines

void Editor::run() {
	/*Initialize cursor position (0,0)*/
	Position cursor;
	displayLines();
	placeCursorAt(cursor);
	char entry;
	bool operation = true;
	/*System function which gets the character*/
	entry = _getch();

	while (operation == true) {
			/*Utilizing cursor line to determine current line*/
			int currentLineNumber = cursor.getX() + 1;
			/*Gets current line where cursor is*/
			string currentLine = lines.getEntry(currentLineNumber);
			

			switch (entry) {
			case ':':
				cursor.setX(0);
				cursor.setY(lines.getLength() + 5);
				placeCursorAt(cursor);
				cout << entry;
				entry = _getche();
				/*Quits the file*/
				if (entry == 'q') {
					inFile.close();
					cout << " " << fileName << " closing the file was successful." << endl;
					operation = false;
					exit(1);
				}
				/*Overwrite on the file*/
				else if (entry == 'w') {
					ofstream newFile;
					newFile.open(fileName);
					for (int copy = 1; copy <= lines.getLength(); copy++)
						newFile << lines.getEntry(copy) << endl;
					newFile.close();
					cout << " " << fileName << " file successfully overwritten." << endl;
				}
				break;
			case 'x':
				placeCursorAt(cursor);
				currentLine.erase(cursor.getX(), 1);
				lines.replace(currentLineNumber, currentLine);
				displayLines();
				break;
			case 'd':
				entry = _getch();
				/*Command dd will erase the whole line*/
				if (entry == 'd') {
					lines.remove(currentLineNumber);
				}
				displayLines();
				break;
			}
			cursor.setX(0);
			cursor.setY(0);
			placeCursorAt(cursor);
			entry = _getch();
	}
}
/*This is not a member function but a package for Editor*/
/*Initializes the cursor*/
void placeCursorAt(Position coordinate) {
	COORD coord;
	coord.X = coordinate.getX();
	coord.Y = coordinate.getY();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*colorText function*/
void colorText(int value) {
	COORD coord;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);
	SetConsoleTextAttribute(hConsole, value);
}
