/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */


#include "ModelManagerT.h"

#include <iostream>

using namespace std;
using namespace MPM;


ModelManagerT::ModelManagerT(){

}

ModelManagerT::~ModelManagerT(){

}


void ModelManagerT::ReadInput(const char* name)
{
	fInput.ReadInput(name);
    
    fNumStep=fInput.getNumStep();
    fDT=fInput.getTimeStepSize();
    
    /* setup materials */
    ConstructMaterialTable();
    
    
    fInput.~InputT();
}


void ModelManagerT::ConstructMaterialTable(){
    
    unordered_map<int, string>* matNameTalbe = fInput.getMatNameTable();
    
    for (auto it=matNameTalbe->begin(); it!=matNameTalbe->end(); it++) {
        
        int id = it->first;
        string name = it->second;
        
        fMatTables[id] = MaterialBaseT::create(name);
        
        cout << name << endl;
        
    }
    
}