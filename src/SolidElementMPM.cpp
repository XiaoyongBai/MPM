/* created by Xiaoyong Bai at CU Boulder, 07/18/2017 */

#include "SolidElementMPM.h"

using namespace std;
using namespace MPM;

SolidElementMPM::SolidElementMPM(){
    
}

SolidElementMPM::SolidElementMPM(int type){
    
    if (type==1) {
        fShape=ShapeBaseT::create(1);
    }else{
        throw "\n!! SolidElementMPM:create, unsupported element type  !!\n";
    }
    
    int ennd = fShape->getENND();
    fMassMatrix = vector<double>(3*ennd, 0.0);
    fForce = vector<double>(3*ennd, 0.0);
    
}

/* num_mp=number of material points in 1D */
/* material points are equally-spaced in parent domain */
vector<vector<double>> SolidElementMPM::generateMatPoints(int num_mp){
    
    int total_num = num_mp*num_mp*num_mp;
    
    vector<vector<double>> result;
    
    /* specify the points in parent domain, i.e. their shape coordinates */
    vector<double> xi_1d(num_mp, 0.0);
    double inc = 2.0/(num_mp+0.0);
    for (int i=0; i<num_mp; i++) {
        xi_1d[i]=(0.5+i)*inc-1.0;
    }
    
    vector<double> xi(3,0.0);
    
    fShape->setCoord(&fNodeCoord);
    
    for (int i=0; i<num_mp; i++) {
        
        xi[0] = xi_1d[i];
        
        for (int j=0; j<num_mp; j++) {
            
            xi[1] = xi_1d[j];
            
            for (int k=0; k<num_mp; k++) {
                
                xi[2] = xi_1d[k];
                
                fShape->evaluate(xi);
                
                vector<double> x=fShape->getX();
                double J=fShape->getJ();
                double volume=J*8.0/(total_num+0.0);
                
                result.push_back({x[0], x[1], x[2], volume});
                
                
            }
        }
    }
    
    
    
    return result;
    
}



void SolidElementMPM::setMaterialPoints(vector<MPM::MaterialPointT *> *mp, vector<int> &index){
    
    fMP=mp;
    fMP_index=index;
    
};



void SolidElementMPM::compute(){
    
    for (int i=0; i<fMassMatrix.size(); i++) {
        fMassMatrix[i]=0;
        fForce[i]=0;
    }
    
    int nmp = fMP_index.size();
    
    if (nmp==0) return;
    
    computeMPShapeCoord();
    
    fShape->setCoord(&fNodeCoord);
    
    //loop over the material points
    for (int mi=0; mi<nmp; mi++) {
        
        MaterialPointT* mp = fMP->at(fMP_index[mi]); //pointer to the material point
        double ms = mp->getMass(); //mass of the material point
        
        fShape->evaluate(fMP_ShapeCoord[mi]);
        
        
    }
    
}



void SolidElementMPM::computeMPShapeCoord(){
    
    int nmp = fMP_index.size(); //number of material point in this element
    
    fMP_ShapeCoord.clear();
    
    double x_left=fNodeCoord[0][0];
    double y_left=fNodeCoord[0][1];
    double z_left=fNodeCoord[0][2];
    double x_right=fNodeCoord[6][0];
    double y_right=fNodeCoord[6][1];
    double z_right=fNodeCoord[6][2];
    
    for (int mi=0; mi<nmp; mi++) {
        
        int id = fMP_index[mi];
        MaterialPointT* mp = fMP->at(id);
        
        vector<double> coord = mp->getCoord();
        
        double xi_1=-1.0+2.0*(coord[0]-x_left)/(x_right-x_left);
        double xi_2=-1.0+2.0*(coord[1]-y_left)/(y_right-y_left);
        double xi_3=-1.0+2.0*(coord[2]-z_left)/(z_right-z_left);
        
        fMP_ShapeCoord.push_back({xi_1,xi_2,xi_3});
    }
    
    
}