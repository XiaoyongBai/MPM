/*
 * InputT.h
 *
 *  Created on: Jun 5, 2015
 *      Author: xiaoyong
 */

#ifndef INPUTT_H_
#define INPUTT_H_

#include <cstring>
#include <iostream>
#include <fstream>

namespace TD_BEM{

class InputT
{
public:
	InputT();
	~InputT();

	void ReadInput(const char* name);

	bool ReadAlgorithm(char* buff, int line);
	bool ReadGeometry(std::ifstream& fin, char* buff, int& line);
	bool ReadMaterial(char* buff, int line);

	/*
	 * Get algorithm parameters
	 */
	int GetNumStep(void);

	double GetDT(void);

	int GetNQ(void);

    int GetIfExt(void);
    
	/*
	 * Geometric information
	 */
	int GetNND(void);

	int GetElementType(void);

	int GetENND(void);

	int GetNEL(void);

	int* GetIEN(void);

    double* GetCoords(void);

	void GetMaterialConstants(double& E, double& nu, double& rho);

    
private:
	/*
	 * algorithm coefficients
	 */
	int fNumStep; //number of time step
	double fDT; //time step size
	int fNQ; //number of Gaussian points per element

    int fIfExt;
    
	/*
	 * material parameters
	 */
	double fE;
	double fNu;
	double fDensity;

	/*
	 * geoemtry information
	 */
    int fSD;
	int fNND;
	int fNEL;
	int fEType;
	int fENND;
	double* fCoords;
	int* fIEN;
    
};


}/*namespace*/

#endif /* INPUTT_H_ */










