/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */


#include "InputT.h"

#include <fstream>
#include <cstring>
#include "stdio.h"
#include "stdlib.h"


using namespace std;
using namespace MPM;



InputT::InputT()
{
	fNumStep=1;
	fDT=0;
}

InputT::~InputT()
{
    cout << "InputT is destroyed\n";
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
    
    /* read time step parameters */
    fin >> fNumStep;
    fin >> fDT;
    
    /* read material parameters */
    fin >> fNumMat;
    for (int i=0; i<fNumMat; i++) {
        int id;
        fin >> id;
        
        if (fMatNames.find(id)!=fMatNames.end()) {
            throw "\n!! Input file error:: id of materials needs to be unique!!\n";
        }
        
        string name;
        fin >> name;
        fMatNames[id]=name;
        
        int np; //number of parameters
        fin >> np;
        for (int j=0; j<np; j++) {
            double para;
            fin>>para;
            fMatConstants[id].push_back(para);
        }
        
    }
    

    /* read Element groups */
    
    
    fin.close();
    
}





