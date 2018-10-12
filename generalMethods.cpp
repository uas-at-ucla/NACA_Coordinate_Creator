#include "generalMethods.h"
#include <cctype>
#include <fstream>
#include <iomanip>


/*Returns true if string input is good, otherwise false*/
bool isGoodStr(string input) {

	//Check length
	if (input.length() != 4) { 
		cout << "Input is not 4 numbers! Try again" << endl;
		cout << endl;
		return false;
	}

	//Check that it's a number
	for (int i = 0; i < 4; i++) {

		if (!isdigit(input[i])) {
			cout << "Input is not numerical. Try again!" << endl;
			cout << endl;
			return false;
		}
	}

	return true;

}

/*Gets the string and size input and checks that it's good*/
void getInput(string& input, int& size, edgeType& myType) {

	//Get the NACA type
	while (1) {
		cout << "Input the NACA airfoil type as a string of 4 numbers" << endl;
		cout << "Example: NACA 0010" << endl;
		cout << "NACA ";
		cin >> input;

		if (isGoodStr(input))
			break;
	}


	//Get the size
	while (1) {
		cout << "How many X values do you want? Min " << MINPOINTS << ", Max " << MAXPOINTS << endl;
		cin >> size;

		if (size <= MAXPOINTS) {
			if (size >= MINPOINTS) {
				break;
			} else {
				cout << "Size is less than minimum value. Try again!" << endl;
				cout << endl;
			}
		} else {
			cout << "Size is greater than Max. Try again!" << endl;
			cout << endl;
		}
	}

	char choice;
	bool good = false;
	//Get the trailing edge type
	while (!good) {
		cout << "(O)pen or (C)losed Trailing edge ?" << endl;
		cin >> choice;

		switch (toupper(choice)) {
			case 'O':
				myType = OPEN;
				good = true;
				break;
			case 'C':
				myType = CLOSED;
				good = true;
				break;
			default:
				cout << "Bad choice, try again!" << endl;
				cout << endl;
				good = false;

		}

	}

	
	return;
}


bool writeFile(double * upperX, double * lowerX, double * upperY, double * lowerY, const int& size, string input) {
	 
	std::ofstream airfoilCoords;
	airfoilCoords.open("NACA"+input+".txt");

	if (!airfoilCoords.is_open()) {
		cout << "Error! Unable to open file" << endl;
		return false;
	}

	//For ANSYS CFX
	//airfoilCoords << "Polyline = true" << endl;

	airfoilCoords << std::setprecision(6) << std::fixed;
	//Print the upper coordinates
	for (int i = size - 1; i >= 0; i--) {
		airfoilCoords << "1\t" << upperX[i] << "\t" << upperY[i] << endl;
	}

	for (int i = 1; i < size; i++) {
		airfoilCoords << "1\t" << lowerX[i] << "\t" << lowerY[i] << endl;
	}

	airfoilCoords.close();

	if (!airfoilCoords.is_open()) {
		cout << "File Created Successfully!" << endl;
		return true;
	} else {
		cout << "File creation failure" << endl;
		return false;
	}
}