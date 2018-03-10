#include "BTree.hpp" //BTree
#include <iostream> // std::cout
#include <fstream> // std::fstream
#include <math.h> // pow

#define FILE_INPUT_LENGTH 10 //max length to be used by file_input
#define B_TREE_DEGREES 3 //degrees to be used by the BTree
#define ASCII_0 48 //48 is the ascii value of 0
#define BASE_10 10 //Our number system uses Base 10
#define ASCII_SPACE 32 //32 is the ascii value of space


int main(int argc, char *argv[]){
	//if no files were passed in display an error message
	if (argc != 2) {
		std::cout << "Pleases pass a file in";
		// Holds the terminal open
		std::cout << "\nPress any key to close";
		std::cin.ignore();
		return 0;
		
	}
	char *file_input = new char(FILE_INPUT_LENGTH); //allocate an array of 10 characters
	BTree<int> values(B_TREE_DEGREES); // A B-Tree with minium degrees in B_TREE_DEGREES
	int value_to_insert = 0; //value to add to B_TREE
	std::fstream data_file(argv[1]); //open file and store in data_file
	//if file is open
	if (data_file.is_open()) {
		//loop through the file, checking one step ahead for the EOF
		while (data_file.peek() != EOF) {
			//get the nextline of data in the file, until reaching a ' '
			data_file.getline(file_input, FILE_INPUT_LENGTH, ' ');
			//find end of file_input
			int i; //iterator to iterate over file_input
			//move i up to either the end of the array or till i reaches 0
			for (i = 0; i <= FILE_INPUT_LENGTH && *(file_input + i) != '\0'; ++i);
			//extract the value in file_input by iterating through it and adding the values to value_to_insert
			for (;i >= 0; --i) {
				//take the character at file_input - ASCII_0 from it and raise it to its value in the decimal system
				if (*(file_input + i) != ASCII_SPACE && *(file_input + i) != '\0') {
					value_to_insert += (*(file_input + i) - ASCII_0)*pow(BASE_10, i);
				}
			}
			//insert the value into the B-Tree
			values.insert(value_to_insert);
			value_to_insert = 0; //reset value_to_insert back to 0 for next input
		}
		//Print out the sorted values
		std::cout << "The sorted values are: ";
		values.traverse();
	}
	//if file failed to open close program
	else {
		std::cout << "File failed to open";
		return 1;
	}
	
	// Holds the terminal open
	std::cout << "\nPress any key to close";
	std::cin.ignore();
    return 0;
}
