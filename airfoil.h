#ifndef _AIRFOIL_H_
#define _AIRFOIL_H_

#include <cmath>
#include <string>


#define pi (atan(1)*4)
#define MAXPOINTS 200
#define MINPOINTS 10

typedef std::string string;
enum edgeType {OPEN, CLOSED};

double calcX(double beta);

void calcXArr(int size, double* Xarr);

double getM(char m);

double getP(char p);

double getT(string input);

bool calcYc(const double& p, const double& m, double* xArr, double * result, const int& size);

bool calcdYc(const double& p, const double& m, double* xArr, double * result, const int& size);

void calcYt(const double& t, double* xArr, double* result, edgeType myType, const int& size);


#endif // !_AIRFOIL_H_