/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */


#include "ModelManagerT.h"

#include <iostream>

using namespace std;
using namespace MPM;


ModelManagerT::ModelManagerT()
{
}

ModelManagerT::~ModelManagerT()
{
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


void ModelManagerT::ReadInput(const char* name)
{
	fInput.ReadInput(name);
    
    fNumStep=fInput.getNumStep();
    fDT=fInput.getTimeStepSize();
    
    
    
    fInput.~InputT();
}
