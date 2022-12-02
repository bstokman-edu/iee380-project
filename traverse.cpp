/*
Title: IEE380 Semester Project traverser
Author: Ben Stokman <bstokman@asu.edu>
Description: Counts the amount of children each item in the Wikidata lexumes dump given the jq --stream format.
Usage: ./traverse <file path>
*/

// Importing libraries
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// Function headers
int readLine(FILE* filePointer);
bool detectNumber(char currentChar);
char * concatonateCharString(char* input, int size);

// Main
int main(int argc, char** argv) {
	// Handling too few or too many arguments
	if(argc != 2) {
		// Print usage
		cout << "Usage: " << argv[0] << " <file path>\n";
		
		// Exit
		return 0;
	}
	
	// Open reading file in read mode
	FILE* filePointer = fopen(argv[1], "r");
	
	// If error opening file
	if(filePointer == NULL) {
		// Print message
		cout << "Error opening file!\n";
		
		// Exit
		return 0;
	}
	
	// Variables needed for logic
	int readLineOutput = -1;
	int currentWDID = 0; // Current Wikidata ID (used for output) (starts at 0)
	int currentCount = 0; // Current count of matching lines
	char currentChar;
	
	// Traverse file while !EOF
	// Traverse whole file
	while((readLineOutput = readLine(filePointer)) != -1) {
		// If the WDID is the same
		if(readLineOutput == currentWDID) {
			// Increment counter
			currentCount ++;
		}
		
		// New WDID
		else {
			// Output stats for previous WDID
			cout << currentWDID << "," << currentCount << "\n";
			
			// Reset
			currentCount = 1; // Resetting to 1 fixes an undercounting issue. I have no idea why. Whatever it works.
			currentWDID = readLineOutput;
		}
		
		// Seek to end of line to properly set the FP for next readLine call
		while((currentChar = fgetc(filePointer)) != '\n') {
			// Do nothing
		}
	}
	
	// Close file
	fclose(filePointer);
	
	// Exit
	return 0;
}

// Reads one line and detects the WDID on that line
// Expects that the FP is at the start of the line
int readLine(FILE* filePointer) {
	// Variables needed for traversal
	char currentChar; // Current char being read
	char storage[32]; // Used to cache number
	int currentTraverseLength = 0; // How long the number string literal is in the cache
	
	// Traverse line
	// Exit if unexpected LE or EOF
	while(((currentChar = fgetc(filePointer)) != '\n') || currentChar != EOF) {
		// Not yet to number
		if(currentChar == '[') {
			// Do nothing
		}
		
		// Number is read
		else if(detectNumber(currentChar)) {
			// Store in cache
			storage[currentTraverseLength] = currentChar;
			
			// Increment cache size
			currentTraverseLength ++;
		}
		
		// Done reading number
		else {
			
			// Return integer value
			return atoi(concatonateCharString(storage, currentTraverseLength));
		}
	}
	
	// Return -1 if unexpected LE or EOF
	return -1;
}

// Detects if the passed-through char is a number 
bool detectNumber(char currentChar) {
	// Is a number
	if(
		(currentChar == '0') ||
		(currentChar == '1') ||
		(currentChar == '2') ||
		(currentChar == '3') ||
		(currentChar == '4') ||
		(currentChar == '5') ||
		(currentChar == '6') ||
		(currentChar == '7') ||
		(currentChar == '8') ||
		(currentChar == '9')
	) {
		return true;
	}
	
	// Is not a number
	else {
		return false;
	}
}

// Returns the first n chars in a char string
char * concatonateCharString(char* input, int size) {
	// Output variable
	char * output = new char[size];
	
	// Copying over
	for(int i = 0; i < size; i++) {
		output[i] = input[i];
	}
	
	// Returning
	return output;
}
