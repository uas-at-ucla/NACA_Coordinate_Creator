#include "generalMethods.h"


int main() {

	bool done = false;
	while (!done) {

		//Get the input from the user
		string input;
		int size;
		edgeType type;
		getInput(input, size, type);

		//Get the Values of m, p, t
		double m = getM(input[0]);
		double p = getP(input[1]);
		double t = getT(input);

		//Allocate the arrays
		double * xArr = new double[size];
		double * Yc = new double[size];
		double * dYcdx = new double[size];
		double * yt = new double[size];
		double * upperX = new double[size];
		double * lowerX = new double[size];
		double * upperY = new double[size];
		double * lowerY = new double[size];

		//Calculate X array
		calcXArr(size, xArr);

		//Calculate Yc
		if (calcYc(p, m, xArr, Yc, size)) {

			//Calculate dYc/dx
			if (calcdYc(p, m, xArr, dYcdx, size)) {

				//Calculate yt array
				calcYt(t, xArr, yt, type, size);

				double theta;
				//Calculate Xu, Xl, Yu, Yl
				for (int k = 0; k < size; k++) {
					theta = atan(dYcdx[k]);

					upperX[k] = xArr[k] - yt[k] * sin(theta);
					lowerX[k] = xArr[k] + yt[k] * sin(theta);
					upperY[k] = Yc[k] + yt[k] * cos(theta);
					lowerY[k] = Yc[k] - yt[k] * cos(theta);
				}

				if (!writeFile(upperX, lowerX, upperY, lowerY, size, input)) {
					cout << endl;
					cout << "Could not write to file. Please try again" << endl;
				} else {
					done = true;
				}

			} else {
				cout << "Error Creating dYc/dx. Try again with new input." << endl;
				cout << endl;
			}

		} else {
			cout << "Error Creating Yc. Try again with new input." << endl;
			cout << endl;
		}

		//Free up dynamically allocated memory
		delete[] xArr;
		delete[] Yc;
		delete[] dYcdx;
		delete[] yt;
		delete[] upperX;
		delete[] lowerX;
		delete[] upperY;
		delete[] lowerY;
	}

	return 0;
}