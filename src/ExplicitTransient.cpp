/* created by Xiaoyong Bai at CU Boulder, 07/19/2018 */

#include "ExplicitTransient.h"

using namespace std;
using namespace MPM;

ExplicitTransient::ExplicitTransient(ModelManagerT* model){
    
    fModel=model;
    
    fElement=ElementBaseT::create(1);
    
    fIEN=model->getIEN_bkg();
    fElementCoord=model->getElementCoord_bkg();
    
    int nnd=model->getNodes_bkg()->size(); //number of nodes in background mesh
    int ndof=nnd*3;
    
    fMass=vector<double>(ndof, 0.0);
    fVelo=vector<double>(ndof, 0.0);
    fAcce=vector<double>(ndof, 0.0);
    fForce=vector<double>(ndof, 0.0);
    
}

ExplicitTransient::~ExplicitTransient(){
    
}

void ExplicitTransient::drive(){
    
    
    int ndof=fMass.size();
    
    //clear the global vectors
    for (int i=0; i<ndof; i++) {
        fMass[i]=0;
        fVelo[i]=0;
        fForce[i]=0;
    }
    
    int num_step = fModel->getNumStep();
    int time_step = fModel->getDT();
    
    vector<vector<int>>* table = fModel->getElementMP_table();
    vector<MaterialPointT*>* MP = fModel->getMatPts();
    
    for (int si=0; si<num_step; si++) {
        
        fModel->constructElementMPTable();
        
        //loop over element to form mass and convective velocity
        for (int ei=0; ei<fIEN->size(); ei++) {
            
            fElement->setNodeCoord(fElementCoord->at(ei));
            
            fElement->setMaterialPoints(MP, table->at(ei));
            
            fElement->computeMassVelo();
            
            vector<double>* mass = fElement->getMassMatrix();
            vector<double>* velo = fElement->getConvecVelo();
            
            AssembleVector(fMass, mass, ei);
            AssembleVector(fVelo, velo, ei);
            
        }
        
        //adjust and update convective velocity
        for (int di=0; di<ndof; di++) {
            if (fMass[di]>0) {
                fVelo[di] /= fMass[di];
                fVelo[di] += fAcce[di];
            }
        }
        
        //loop over elements to form force vector
        int ennd=fIEN->at(0).size();
        vector<double> node_v(ennd*3, 0.0);//node velocity
        
        for (int ei=0; ei<fIEN->size(); ei++) {
            
            //collect nodal velocity
            for (int ni=0; ni<ennd; ni++) {
                int nid=fIEN->at(ei)[ni];
                for (int di=0; di<3; di++) {
                    node_v[ni*3+di]=fVelo[nid*3+di];
                }
            }
            
            fElement->setNodeCoord(fElementCoord->at(ei));
            fElement->setNodeVelo(node_v);
            fElement->setMaterialPoints(MP, table->at(ei));
            
            
            
            fElement->computeMassVelo();
            
            vector<double>* mass = fElement->getMassMatrix();
            vector<double>* velo = fElement->getConvecVelo();
            
            AssembleVector(fMass, mass, ei);
            AssembleVector(fVelo, velo, ei);
            
        }
        
    }
    
}




void ExplicitTransient::AssembleVector(vector<double>& gv, vector<double>* ev, int eid){
    
    int ennd = fIEN->at(0).size();
    
    for (int i=0; i<ennd; i++) {
        int gid=fIEN->at(eid)[i];
        
        for (int d=0; d<3; d++) {
            gv[gid*3+d] += ev->at(i*3+d);
        }
        
    }
    
}