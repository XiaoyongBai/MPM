/* created by Xiaoyong Bai at CU Boulder, 07/19/2018 */

#include "ExplicitTransient.h"

using namespace std;
using namespace MPM;

ExplicitTransient::ExplicitTransient(ModelManagerT* model){
    
    fModel=model;
    
    fElement=ElementBaseT::create(1);
    
    fIEN=model->getIEN_bkg();
    fElementCoord=model->getElementCoord_bkg();
    
}

ExplicitTransient::~ExplicitTransient(){
    
}

void ExplicitTransient::drive(){
    
    int num_step = fModel->getNumStep();
    int time_step = fModel->getDT();
    
    vector<vector<int>>* table = fModel->getElementMP_table();
    vector<MaterialPointT*>* MP = fModel->getMatPts();
    
    for (int si=0; si<num_step; si++) {
        
        fModel->constructElementMPTable();
        
        //loop over element
        for (int ei=0; ei<fIEN->size(); ei++) {
            
            fElement->setNodeCoord(fElementCoord->at(ei));
            
            fElement->setMaterialPoints(MP, table->at(ei));
            
            fElement->compute();
        }
        
        
        
        
    }
    
}