/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */

#ifndef MODELMANAGERT_H_
#define MODELMANAGERT_H_

#include "InputT.h"

namespace MPM{


class ModelManagerT
{
public:

	ModelManagerT();
	~ModelManagerT();

	int GetFormulation(void);
	void SetFormulation(int formulation);

	int GetNumStep(void);
	void SetNumStep(int numstep);

	double GetDT(void);
	void SetDT(double dt);

	const int GetNQ(void);
	void SetNQ(int nq);

    int GetIfExt(void);
    void SetIfExt(int if_ext);
    
	/**
	 * @Functions to get model parameters
	 * 		GetNND=return number of nodes
	 * 		GetElementType=return type of the element
	 * 		GetNEL=return number of elements
	 * 		GetIEN=return element connectivities
	 * 		GetCoords=return nodes' coordinates*/
	int GetNND(void);
	void SetNND(int nnd);

	int GetElementType(void);
	void SetElementType(int et);

	int GetENND(void);
	void SetENND(int ENND);

	int GetNEL(void);
	void SetNEL(int nel);

	const int* GetIEN(void);
	void SetIEN(int* IEN);

	const double* GetCoords(void);
    void SetCoords(double* coords);


	void GetMaterialConstants(double& E, double& nu, double& rho);
	void SetMaterialConstants(double E, double nu, double rho);

	void ReadInput(const char* name);


private:
	/**
	 * algorithm parameters
	 */
	double fDT;
	int fNumStep;
	int fNQ;

	/*
	 * fNND= number of nodes in the model
	 * fENND= number of node per element
	 * fNEL= number of elements in the model
	 * fET= element type
	 * fIEN= element connectivities
	 * fCoords= nodes coordinates
	 * fNQ= number of Gaussian quadrature point per element */
	int fSD;
	int fIfExt;
	int fNND;
	int fENND;
	int fNEL;
	int fET;
	int* fIEN;
	double* fCoords;

	/*
	 * fE=Young's modulus
	 * fNu=Possion's ratio
	 * fDensity=density
	 */
	double fE;
	double fNu;
	double fDensity;

    
	InputT fInput;
};


} /* name space */



#endif /* MODELMANAGERT_H_ */
