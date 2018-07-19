/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */

#include <iostream>

#include "ModelManagerT.h"
#include "ShapeBaseT.h"

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
    
    /* set up materials */
    ConstructMaterialTable();
    
    /* set up nodes */
    fNodes_mp=fInput.getNodes();
    
    /* set up elements and generate material points */
    vector<vector<int>> elementConstants = fInput.getElementConstants();
    int ele_type=elementConstants[0][1];
    ShapeBaseT* shape = ShapeBaseT::create(ele_type);
    shape->setCoord(&fNodes_mp);
    vector<double> xi={0,-1,1};
    shape->evaluate(xi);
    
    vector<double> X=shape->getX();
    double J=shape->getJ();
    
    fInput.~InputT();
}


void ModelManagerT::ConstructMaterialTable(){
    
    unordered_map<int, string>* matNameTalbe = fInput.getMatNameTable();
    unordered_map<int, vector<double>>* matParaTable = fInput.getMatParaTable();
    
    
    for (auto it=matNameTalbe->begin(); it!=matNameTalbe->end(); it++) {
        
        int id = it->first;
        string name = it->second;
        vector<double> parameters = (*matParaTable)[id];
        
        fMatTables[id] = MaterialBaseT::create(name);
        
        if (parameters.size()!=fMatTables[id]->getNumPara()) {
            throw "\n !! ModelManagerT::ConstructMaterialTable, number of parameters does not match !! \n";
        }
        
        fMatTables[id]->setParameters(parameters);
        
        vector<double> strain={0.0,0.01,0,0.2,0.3,0.4};
        fMatTables[id]->updateStress(strain);
        vector<double>* stress=fMatTables[id]->getCauchyStress();
        
        /*
        cout << "stress="<< endl;
        for (int i=0; i<stress->size(); i++) {
            cout << stress->at(i) << endl;
        }
        
        cout << name << endl;*/
        
    }
    
}