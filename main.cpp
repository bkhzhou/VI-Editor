//Main.cpp file
//CSC 326
//VI EDITOR PHASE 1
//GROUP MEMBERS: DEANNA MANDARINO, VICTORIA JACZYNSKI, SIMON CHRISTIAN, BILL ZHOU

// Task: Write an Editor class that has an instance of our LinkedList
// Use command line arguments - the user will specify the file (if it exists)
// Code a constructor for the Editor class with one parameter for the file name - read it in and add to the linked list 
// Allow for the following commands:  :q   :w

#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Editor.h"

void main(int argc, const char* argv[]) {

	if (argc > 1) {
		Editor si(argv[1]);
	}
}
