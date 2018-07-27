/* created by Xiaoyong Bai at CU Boulder, 07/19/2017 */

#include "MaterialPointT.h"


using namespace std;
using namespace MPM;

MaterialPointT::MaterialPointT(){
    
    fCoord=vector<double>(3, 0.0);
    fVel=vector<double>(3, 0.0);
}


MaterialPointT::~MaterialPointT(){
    delete fMaterial;
}

void MaterialPointT::setMaterial(MaterialBaseT *mat){
    
    string name = mat->getName();
    vector<double> para = mat->getParameters();
    
    fMaterial = MaterialBaseT::create(name);
    fMaterial->setParameters(para);
    
}

void MaterialPointT::updateCoord(double dt){
    
    for (int i=0; i<3; i++) {
        fCoord[i] += fVel[i]*dt;
    }
    
}

vector<double> MaterialPointT::getDisplacement(){
    
    vector<double> dis(3,0);
    for (int i=0; i<3; i++) {
        dis[i]=fCoord[i]-fInitCoord[i];
    }
    
    return dis;
    
}

