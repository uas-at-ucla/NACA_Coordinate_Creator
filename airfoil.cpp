#include "airfoil.h"
#include "generalMethods.h"

/*Returns the X value given Beta*/
double calcX(double beta) {
	return((1 - cos(beta)) / 2);
}

/*Fills an Array with the values of X in an equal distribution*/
void calcXArr(int size, double * Xarr) {

	double betaInc = pi / (double) (size - 1);
	double beta = 0;


	for (int i = 0; i < size; i++, beta += betaInc) {
		
		Xarr[i] = calcX(beta);
	}

}

/*Change the inputs to variable values*/
double getM(char m) {
	return std::stod(&m) / 100;
}

double getP(char p) {
	return std::stod(&p) / 10;
}

double getT(string input) {
	return std::stod(&input[2]) / 100;
}

/*Calculates the Yc array*/
bool calcYc(const double& p, const double& m, double* xArr, double * result, const int& size) {

	for (int i = 0; i < size; i++) {
		
		if (xArr[i] < p) {

			if (p != 0) {
				result[i] = (m / (p*p))*(2*p*xArr[i] - (xArr[i]*xArr[i]));
			} else if (p == 0 && m == 0) {
				result[i] = 0;
			} else {
				cout << "The postion of max camber must be equal to 0 if " <<
					"max camber is equal to 0!" << endl;
				return false;
			}
			
		} else {
			result[i] = (m / pow(1-p, 2))*(1 - 2 * p + 2 * p*xArr[i] - (xArr[i] * xArr[i]));
		}
	}

	return true;
}

/*Calculates the dYc/dx array*/
bool calcdYc(const double& p, const double& m, double* xArr, double * result, const int& size) {

	for (int i = 0; i < size; i++) {

		if (xArr[i] < p) {

			if (p != 0) {
				result[i] = (2*m / (p*p))*(p-xArr[i]);
			}
			else if (p == 0 && m == 0) {
				result[i] = 0;
			}
			else {
				cout << "The postion of max camber must be equal to 0 if " <<
					"max camber is equal to 0!" << endl;
				return false;
			}

		}
		else {
			result[i] = (2*m / pow(1-p, 2))*(p-xArr[i]);
		}
	}

	return true;
}

/*Calculates the yt array*/
void calcYt(const double& t, double* xArr, double* result, edgeType myType, const int& size) {
	double a0 = 0.2969, a1 = -0.126, a2 = -0.3516, a3 = 0.2843, a4;

	if (myType == OPEN) {
		a4 = -.1015;
	} else {
		a4 = -0.1036;
	}

	for (int i = 0; i < size; i++) {
		result[i] = (t / 0.2)*(a0*pow(xArr[i], 0.5) + a1*xArr[i] +
			a2*pow(xArr[i], 2) + a3*pow(xArr[i], 3) + a4*pow(xArr[i], 4));
	}

	return;
}