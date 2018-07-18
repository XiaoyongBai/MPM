/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */


#include "ModelManagerT.h"

#include <iostream>

using namespace std;
using namespace MPM;


ModelManagerT::ModelManagerT()
{
	fDT=0;
	fNumStep=1;
	fNQ=6;

	fSD=3;
	fIfExt=1;
	fNND=0;
	fENND=0;
	fNEL=0;
	fET=1;
	fIEN=NULL;
	fCoords=NULL;

	fE=0;
	fNu=0;
	fDensity=0;
}

ModelManagerT::~ModelManagerT()
{
	if (fIEN) delete[] fIEN;
	if (fCoords) delete[] fCoords;
}



int ModelManagerT::GetNumStep(void)
{
	return fNumStep;
}

void ModelManagerT::SetNumStep(int numstep)
{
	fNumStep=numstep;
}

double ModelManagerT::GetDT(void)
{
	return fDT;
}
void ModelManagerT::SetDT(double dt)
{
	fDT=dt;
}

const int ModelManagerT::GetNQ(void)
{
	return fNQ;
}

void ModelManagerT::SetNQ(int nq)
{
	fNQ=nq;
}

int ModelManagerT::GetIfExt(void)
{
    return fIfExt;
}

void ModelManagerT::SetIfExt(int if_ext)
{
    fIfExt=if_ext;
}


int ModelManagerT::GetNND(void)
{
	return fNND;
}

void ModelManagerT::SetNND(int nnd)
{
	fNND=nnd;
}

int ModelManagerT::GetElementType()
{
	return fET;
}

void ModelManagerT::SetElementType(int et)
{
	fET=et;

	switch (et){
	case 1:
		fENND=4;
		break;
	case 2:
		fENND=8;
		break;
	default:
		throw "ModelManagerT::SetElementType, unsupported element type";
		break;
	}
}

int ModelManagerT::GetENND()
{
	return fENND;
}

int ModelManagerT::GetNEL(void)
{
	return fNEL;
}

void ModelManagerT::SetNEL(int nel)
{
	fNEL=nel;
}

const int* ModelManagerT::GetIEN(void)
{
	return fIEN;
}

void ModelManagerT::SetIEN(int* IEN)
{
    if (fIEN) delete [] fIEN;
    
	fIEN=new int[fNEL*fENND];

}

const double* ModelManagerT::GetCoords(void)
{
	return fCoords;
}

void ModelManagerT::SetCoords(double* coords)
{
    if(fCoords) delete [] fCoords;
    
	fCoords=new double[fNND*fSD];

}

void ModelManagerT::GetMaterialConstants(double& E, double& nu, double& rho)
{
	E=fE;
	nu=fNu;
	rho=fDensity;
}

void ModelManagerT::SetMaterialConstants(double E, double nu, double rho)
{
	fE=E;
	fNu=nu;
	fDensity=rho;
}


void ModelManagerT::ReadInput(const char* name)
{
	fInput.ReadInput(name);
    
    fNumStep=fInput.getNumStep();
    fDT=fInput.getTimeStepSize();
    
    fInput.~InputT();
}
