
#ifndef _GENERALMETHODS_H_
#define _GENERALMETHODS_H_

#include <iostream>
#include <cstdlib>
#include "airfoil.h"

#define cout std::cout
#define cin std::cin
#define endl std::endl

bool isGoodStr(string input);

void getInput(string& input, int& size, edgeType& myType);

bool writeFile(double * upperX, double * lowerX, double * upperY, double * lowerY, const int& size, string input);


#endif // !_GENERALMETHODS_H_