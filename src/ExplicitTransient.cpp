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
    
    int num_step = fModel->getNumStep();
    double time_step = fModel->getDT();
    int nel=fIEN->size();
    int ennd=fIEN->at(0).size();
    
    vector<vector<int>>* table = fModel->getElementMP_table();
    vector<MaterialPointT*>* MP = fModel->getMatPts();
    
    //initialize force vectors
    for (int i=0; i<ndof; i++) fForce[i]=0;

    for (int i=100; i<125; i++) {
        fForce[i*3+2]=1;
    }
    
    fModel->constructElementMPTable();
    
    //loop over element to initialize mass and convective velocity
    
    for (int i=0; i<ndof; i++) {
        fMass[i]=0;
        fVelo[i]=0;
    }
    
    for (int ei=0; ei<nel; ei++) {
        
        fElement->setNodeCoord(fElementCoord->at(ei));
        fElement->setMaterialPoints(MP, table->at(ei));
        
        fElement->computeMassVelo();
        
        vector<double>* mass = fElement->getMassMatrix();
        vector<double>* velo = fElement->getConvecVelo();
        
        AssembleVector(fMass, mass, ei);
        AssembleVector(fVelo, velo, ei);
    }

    //adjust convective velocity
    for (int di=0; di<ndof; di++) {
        if (fMass[di]>0) fVelo[di] /= fMass[di];
    }
    
    
    //time stepping
    for (int si=0; si<num_step; si++) {
        
        //compute acceleration
        for (int di=0; di<fAcce.size(); di++) {
            if (fMass[di]>0) fAcce[di]=fForce[di]/fMass[di];
        }
        
        //update convective velocity
        for (int di=0; di<ndof; di++) {
            if (fMass[di]>0) {
                fVelo[di] += fAcce[di]*time_step;
            }
        }
        
        //velocity boundary condition on background mesh
        for (int i=0; i<25*3; i++) {
            fVelo[i]=0;
        }
        
        //clear force vector
        for (int i=0; i<ndof; i++) {
            fForce[i]=0;
        }
        
        //body force and tractions
        for (int i=100; i<125; i++) {
            fForce[i*3+2]=1;
        }
        
        //loop over elements to form internal force vector
        vector<double> node_v(ennd*3, 0.0);//node velocity
        
        for (int ei=0; ei<fIEN->size(); ei++) {
            
            //collect nodal velocity
            for (int ni=0; ni<ennd; ni++) {
                int nid=fIEN->at(ei)[ni];
                for (int di=0; di<3; di++) {
                    node_v[ni*3+di]=fVelo[nid*3+di];
                }
            }
            
            //node_v={1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            
            fElement->setNodeCoord(fElementCoord->at(ei));
            fElement->setNodeVelo(node_v);
            fElement->setMaterialPoints(MP, table->at(ei));
            
            fElement->computeForce(time_step);
            
            vector<double>* force = fElement->getForce();
            
            AssembleVector(fForce, force, ei);
            
        }
        
        
        //compute nodal mass and convective velocity
        
        for (int i=0; i<ndof; i++) {
            fMass[i]=0;
            fVelo[i]=0;
        }
        
        fModel->constructElementMPTable();
        
        for (int ei=0; ei<nel; ei++) {
            
            fElement->setNodeCoord(fElementCoord->at(ei));
            fElement->setMaterialPoints(MP, table->at(ei));
            
            fElement->computeMassVelo();
            
            vector<double>* mass = fElement->getMassMatrix();
            vector<double>* velo = fElement->getConvecVelo();
            
            AssembleVector(fMass, mass, ei);
            AssembleVector(fVelo, velo, ei);
        }
        
        //adjust convective velocity
        for (int di=0; di<ndof; di++) {
            if (fMass[di]>0) fVelo[di] /= fMass[di];
        }
        
        vector<double> dis = MP->at(3999)->getDisplacement();
        cout << "step=" << si << ", dis_z="<<dis[2]<< ", fForce is=" << fForce[2] << endl;
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