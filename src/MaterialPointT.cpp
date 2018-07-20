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



