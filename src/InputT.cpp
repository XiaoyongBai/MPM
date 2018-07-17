/*
 * InputT.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: xiaoyong
 */

#include "InputT.h"

#include <fstream>
#include <cstring>
#include "stdio.h"
#include "stdlib.h"
#include "MathOperationT.h"


using namespace std;
using namespace TD_BEM;
using namespace GreenFunction;

const int MAX_CHARS_LINE=300;
const int MAX_TOKEN_LINE=100;
const char* const DELIMITER = "\t=;, ";

InputT::InputT()
{
	fNumStep=1;
	fDT=0;
	fNQ=6;


	fE=1;
	fNu=0;
	fDensity=1;

    fSD=3;
	fNND=0;
	fNEL=0;
	fEType=1;
	fENND=4;
	fIEN=NULL;
	fCoords=NULL;
}

InputT::~InputT()
{
	delete[] fIEN;
	delete[] fCoords;

}

void InputT::ReadInput(const char* fileName)
{
	cout << "reading " << fileName << endl;

	ifstream fin;
	fin.open(fileName);

	if(!fin.good())
	{
		cout << fileName << " was not found \n";
		throw "file was not found";
	}

	int line=0;

	while(!fin.eof())
	{
		line++;
        
		char buff[MAX_CHARS_LINE];
		char buff_temp[MAX_CHARS_LINE];
        
		fin.getline(buff, MAX_CHARS_LINE);
        
        //check if the line is empty
        char buff_empty[MAX_CHARS_LINE];
        strcpy(buff_empty, buff);
        char* token[MAX_TOKEN_LINE]={};
        token[0]=strtok(buff_empty, DELIMITER);
        
        if(!token[0])	continue;
        

		strcpy(buff_temp, buff);
		if(ReadAlgorithm(buff_temp, line)) continue;

		strcpy(buff_temp, buff);
		if(ReadMaterial(buff_temp, line)) continue;

		strcpy(buff_temp, buff);
		if(ReadGeometry(fin, buff_temp, line)) continue;

		cout << "key word " << token[0] << endl;
		throw  "InputT::ReadInput, unaccepted key word";

	}

	fin.close();

	cout << "model reading over\n";

}


bool InputT::ReadAlgorithm(char* buff, int line)
{
	char* token[MAX_TOKEN_LINE]={};

	token[0]=strtok(buff, DELIMITER);
    
	int flag;

	/************************************************
	 ** Read number of steps
	 ************************************************/
	flag=strcmp(token[0], "numstep");

	if(flag==0)
	{
		token[1]=strtok(NULL, DELIMITER);

		if(!token[1])
		{
			cout<< "Error occurs as reading line " << line << endl;
			throw "number of step to run is not set properly";
		}
		else
		{
			fNumStep=atoi(token[1]);
			//cout<< "fNumStep=" << fNumStep << endl;
		}

		return 1;
	}

	/************************************************
	 ** Read dt
	 ************************************************/
	flag=strcmp(token[0], "dt");

	if(flag==0)
	{
		token[1]=strtok(NULL, DELIMITER);

		if(!token[1])
		{
			cout<< "Error occurs as reading line " << line << endl;
			throw "time step size is not set properly";
		}
		else
		{
			fDT=atof(token[1]);
			//cout<< "fDT=" << fDT << endl;
		}

		return 1;
	}



	/************************************************
	 ** Read number of Gaussian points
	 ************************************************/
	flag=strcmp(token[0], "nq");

	if(flag==0)
	{
		token[1]=strtok(NULL, DELIMITER);

		if(!token[1])
		{
			cout<< "Error occurs as reading line " << line << endl;
			throw "number of Gaussian points (nq) is not set properly";
		}
		else
		{
			fNQ=atof(token[1]);
			//cout<< "fNQ=" << fNQ << endl;
		}

		return 1;
	}

	return 0;
}

bool InputT::ReadMaterial(char* buff, int line)
{
	char* token[MAX_TOKEN_LINE]={};

	token[0]=strtok(buff, DELIMITER);

	int flag;

	/************************************************
	 ** Read modulus
	 ************************************************/
	flag=strcmp(token[0], "E");

	if(flag==0)
	{
		token[1]=strtok(NULL, DELIMITER);

		if(!token[1])
		{
			cout<< "Error occurs as reading line " << line << endl;
			throw "Young's modulus is not set properly";
		}
		else
		{
			fE=atof(token[1]);
			//cout<< "fE=" << fE << endl;
		}

		return 1;
	}

	/************************************************
	 ** Read Poisson Ratio
	 ************************************************/
	flag=strcmp(token[0], "nu");

	if(flag==0)
	{
		token[1]=strtok(NULL, DELIMITER);

		if(!token[1])
		{
			cout<< "Error occurs as reading line " << line << endl;
			throw "possion's ratio is not set properly";
		}
		else
		{
			fNu=atof(token[1]);
			//cout<< "fNu=" << fNu << endl;
		}

		return 1;
	}

	/************************************************
	 ** Read material density
	 ************************************************/
	flag=strcmp(token[0], "density");

	if(flag==0)
	{
		token[1]=strtok(NULL, DELIMITER);

		if(!token[1])
		{
			cout<< "Error occurs as reading line " << line << endl;
			throw "density is not set properly";
		}
		else
		{
			fDensity=atof(token[1]);
			//cout<< "fDensity=" << fDensity << endl;
		}

		return 1;
	}

	return 0;
}


bool InputT::ReadGeometry(ifstream& fin, char* buff, int& line)
{
	char* token[MAX_TOKEN_LINE]={};

	token[0]=strtok(buff, DELIMITER);

	int flag;


    /************************************************
     ** Read if external problem
     ************************************************/
    flag=strcmp(token[0], "if_ext");
    if(flag==0)
    {
        token[1]=strtok(NULL, DELIMITER);
        
        if(!token[1])
        {
            cout<< "Error occurs as reading line " << line << endl;
            throw "if_ext is not set properly";
        }
        else
        {
            fIfExt=atoi(token[1]);
            //cout<< "fIfExt=" << fIfExt << endl;
        }
        
        return 1;
    }
    
	/************************************************
	 ** Read number of nodes
	 ************************************************/
	flag=strcmp(token[0], "nnd");
	if(flag==0)
	{
		token[1]=strtok(NULL, DELIMITER);

		if(!token[1])
		{
			cout<< "Error occurs as reading line " << line << endl;
			throw "number of nodes is not set properly";
		}
		else
		{
			fNND=atoi(token[1]);
			//cout<< "fNND=" << fNND << endl;
		}

		return 1;
	}

	/************************************************
	 ** Read type of element
	 ************************************************/
	flag=strcmp(token[0], "EType");
	if(flag==0)
	{
		token[1]=strtok(NULL, DELIMITER);

		if(!token[1])
		{
			cout<< "Error occurs as reading line " << line << endl;
			throw "number of nodes is not set properly";
		}
		else
		{
			fEType=atoi(token[1]);
			if(fEType==1)
				fENND=4;
			else if(fEType==2)
				fENND=8;
			else
			{
				throw "InputT::ReadInput, unsupported element type";
			}
			//cout<< "fEType=" << fEType << endl;
		}

		return 1;
	}

	/************************************************
	 ** Read number of elements
	 ************************************************/
	flag=strcmp(token[0], "nel");
	if(flag==0)
	{
		token[1]=strtok(NULL, DELIMITER);

		if(!token[1])
		{
			cout<< "Error occurs as reading line " << line << endl;
			throw "number of nodes is not set properly";
		}
		else
		{
			fNEL=atoi(token[1]);
			//cout<< "fNel=" << fNEL << endl;
		}

		return 1;
	}


	/************************************************
	 ** Read node coordinates
	 ************************************************/
	flag=strcmp(token[0], "nodes");
	if(flag==0)
	{
		fCoords=new double[fSD*fNND];

		char bf[MAX_CHARS_LINE];

		for(int nid=0; nid<fNND; nid++)
		{
			fin.getline(bf, MAX_CHARS_LINE);

			token[0]=strtok(bf, DELIMITER);
			fCoords[nid*fSD+0]=atof(token[0]);

			token[1]=strtok(NULL, DELIMITER);
			fCoords[nid*fSD+1]=atof(token[1]);

			token[2]=strtok(NULL, DELIMITER);
			fCoords[nid*fSD+2]=atof(token[2]);
		}


		//MathOperationT::PrintMatrix(fNND, fSD, fCoords, "Nodes");

		return 1;
	}

	/************************************************
	 ** Read element connections
	 ************************************************/
	flag=strcmp(token[0], "IEN");
	if(flag==0)
	{
		fIEN=new int[fNEL*fENND];

		char buff[MAX_CHARS_LINE];

		for(int eid=0; eid<fNEL; eid++)
		{
			fin.getline(buff, MAX_CHARS_LINE);
			line++;

			token[0]=strtok(buff, DELIMITER);
			fIEN[eid*fENND+0]=atoi(token[0])-1;

			for(int ni=1; ni<fENND; ni++)
			{
				token[ni]=strtok(NULL, DELIMITER);
				fIEN[eid*fENND+ni]=atoi(token[ni])-1;
			}
		}

		//MathOperationT::PrintMatrix(fNEL, fENND, fIEN, "fIEN");

		return 1;
	}

	return 0;
}




int InputT::GetNumStep(void)
{
	return fNumStep;
}

double InputT::GetDT(void)
{
	return fDT;
}


int InputT::GetNQ(void)
{
	return fNQ;
}

int InputT::GetIfExt()
{
    return fIfExt;
}

int InputT::GetNND(void)
{
	return fNND;
}

int InputT::GetElementType(void)
{
	return fEType;
}

int InputT::GetENND(void)
{
	return fENND;
}

int InputT::GetNEL(void)
{
	return fNEL;
}

int* InputT::GetIEN(void)
{
	return fIEN;
}

double* InputT::GetCoords(void)
{
	return fCoords;
}


void InputT::GetMaterialConstants(double& E, double& nu, double& rho)
{
	E=fE;
	nu=fNu;
	rho=fDensity;
}


