/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */

#include <iostream>

#include "ModelManagerT.h"
#include "ShapeBaseT.h"
#include "ElementBaseT.h"

using namespace std;
using namespace MPM;


ModelManagerT::ModelManagerT(){

}

ModelManagerT::~ModelManagerT(){

}


void ModelManagerT::readInput(const char* name)
{
	fInput.ReadInput(name);
    
    fNumStep=fInput.getNumStep();
    fDT=fInput.getTimeStepSize();
    
    /* set up materials */
    constructMaterialTable();
    
    /* set up nodes */
    fNodes_mp=fInput.getNodes();
    
    /* generate material points */
    generateMPM();

    
    fInput.~InputT();
}


void ModelManagerT::constructMaterialTable(){
    
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



void ModelManagerT::generateMPM(){
    
    fElementConstants_mp = fInput.getElementConstants();
    fIENs_mp = fInput.getIENs();
    
    fNumGroups_mp = fElementConstants_mp.size();
    
    //loop over element groups
    for (int gi=0; gi<fNumGroups_mp; gi++) {
        
        int nel=fElementConstants_mp[gi][0];
        int ele_type=fElementConstants_mp[gi][1];
        int ennd=fElementConstants_mp[gi][2];
        int mat_id=fElementConstants_mp[gi][3]; //material id
        int nmp=fElementConstants_mp[gi][4]; //number of material points per element
        
        ElementBaseT* element = ElementBaseT::create(ele_type);
        
        vector<vector<double>> eleCoords(ennd, vector<double>(3,0));
        
        //loop over elements
        for (int ei=0; ei<nel; ei++) {
            
            //extract element nodes
            for(int ni=0; ni<ennd; ni++){
                int nid=fIENs_mp[gi][ei*3+ni];
 
                eleCoords[ni]=fNodes_mp[nid];
            }
            
            element->setNodeCoord(eleCoords);
            
            vector<vector<double>> mp = element->generateMatPoints(nmp);
            
        }
        
        
    }
    
    
}