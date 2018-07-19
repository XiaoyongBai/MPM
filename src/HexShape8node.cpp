/* created by Xiaoyong Bai at CU Boulder, 07/18/2018 */


#include <string>
#include <vector>

#include "HexShape8node.h"

using namespace std;
using namespace MPM;

HexShape8node::HexShape8node(){
    
    fNND=8;

    fN=vector<double>(fNND, 0.0);
    fDN=vector<vector<double>>(fNND, vector<double>(3,0.0));
    
    fX=vector<double>(3,0.0);
    
}


HexShape8node::~HexShape8node(){
    
}


void HexShape8node::evaluate(vector<double> &xi){
    
    if (fNND!=fCoords->size()) {
        throw "\n !!HexShape8node:: the coordiante does not match the element!! \n";
    }
    
    //compute shape functions
    fN[0]=0.125*(1.0-xi[0])*(1.0-xi[1])*(1.0-xi[2]);
    fN[1]=0.125*(1.0+xi[0])*(1.0-xi[1])*(1.0-xi[2]);
    fN[2]=0.125*(1.0+xi[0])*(1.0+xi[1])*(1.0-xi[2]);
    fN[3]=0.125*(1.0-xi[0])*(1.0+xi[1])*(1.0-xi[2]);
    fN[4]=0.125*(1.0-xi[0])*(1.0-xi[1])*(1.0+xi[2]);
    fN[5]=0.125*(1.0+xi[0])*(1.0-xi[1])*(1.0+xi[2]);
    fN[6]=0.125*(1.0+xi[0])*(1.0+xi[1])*(1.0+xi[2]);
    fN[7]=0.125*(1.0-xi[0])*(1.0+xi[1])*(1.0+xi[2]);
    
    //compute the derivate w.r.t xi
    fDN[0][0]=-0.125*(1.0-xi[1])*(1.0-xi[2]);
    fDN[0][1]=-0.125*(1.0-xi[0])*(1.0-xi[2]);
    fDN[0][2]=-0.125*(1.0-xi[0])*(1.0-xi[1]);
    
    fDN[1][0]= 0.125*(1.0-xi[1])*(1.0-xi[2]);
    fDN[1][1]=-0.125*(1.0+xi[0])*(1.0-xi[2]);
    fDN[1][2]=-0.125*(1.0+xi[0])*(1.0-xi[1]);

    fDN[2][0]= 0.125*(1.0+xi[1])*(1.0-xi[2]);
    fDN[2][1]= 0.125*(1.0+xi[0])*(1.0-xi[2]);
    fDN[2][2]=-0.125*(1.0+xi[0])*(1.0+xi[1]);
    
    fDN[3][0]=-0.125*(1.0+xi[1])*(1.0-xi[2]);
    fDN[3][1]= 0.125*(1.0-xi[0])*(1.0-xi[2]);
    fDN[3][2]=-0.125*(1.0-xi[0])*(1.0+xi[1]);
    
    fDN[4][0]=-0.125*(1.0-xi[1])*(1.0+xi[2]);
    fDN[4][1]=-0.125*(1.0-xi[0])*(1.0+xi[2]);
    fDN[4][2]= 0.125*(1.0-xi[0])*(1.0-xi[1]);
    
    fDN[5][0]= 0.125*(1.0-xi[1])*(1.0+xi[2]);
    fDN[5][1]=-0.125*(1.0+xi[0])*(1.0+xi[2]);
    fDN[5][2]= 0.125*(1.0+xi[0])*(1.0-xi[1]);
    
    fDN[6][0]= 0.125*(1.0+xi[1])*(1.0+xi[2]);
    fDN[6][1]= 0.125*(1.0+xi[0])*(1.0+xi[2]);
    fDN[6][2]= 0.125*(1.0+xi[0])*(1.0+xi[1]);
    
    fDN[7][0]=-0.125*(1.0+xi[1])*(1.0+xi[2]);
    fDN[7][1]= 0.125*(1.0-xi[0])*(1.0+xi[2]);
    fDN[7][2]= 0.125*(1.0-xi[0])*(1.0+xi[1]);
    
    //interpolate the coordinate
    for (int i=0; i<3; i++) fX[i]=0.0;
    
    for (int n=0; n<fNND; n++) {
        fX[0] += fN[n]*fCoords->at(n)[0];
        fX[1] += fN[n]*fCoords->at(n)[1];
        fX[2] += fN[n]*fCoords->at(n)[2];
    }
    
    
    //compute Jacobian
    vector<vector<double>> dx_dxi(3, vector<double>(3,0.0)); //Jacobian matrix
    for (int n=0; n<fNND; n++) {
        dx_dxi[0][0] += fDN[n][0]*fCoords->at(n)[0]; //dx_dxi1
        dx_dxi[0][1] += fDN[n][1]*fCoords->at(n)[0]; //dx_dxi2
        dx_dxi[0][2] += fDN[n][2]*fCoords->at(n)[0]; //dx_dxi3
        dx_dxi[1][0] += fDN[n][0]*fCoords->at(n)[1]; //dy_dxi1
        dx_dxi[1][1] += fDN[n][1]*fCoords->at(n)[1]; //dy_dxi2
        dx_dxi[1][2] += fDN[n][2]*fCoords->at(n)[1]; //dy_dxi3
        dx_dxi[2][0] += fDN[n][0]*fCoords->at(n)[2]; //dz_dxi1
        dx_dxi[2][1] += fDN[n][1]*fCoords->at(n)[2]; //dz_dxi2
        dx_dxi[2][2] += fDN[n][2]*fCoords->at(n)[2]; //dz_dxi3
    }
    
    fJ=dx_dxi[0][0]*dx_dxi[1][1]*dx_dxi[2][2]+dx_dxi[0][1]*dx_dxi[1][2]*dx_dxi[2][0]
      +dx_dxi[0][2]*dx_dxi[1][0]*dx_dxi[2][1]-dx_dxi[0][2]*dx_dxi[1][1]*dx_dxi[2][0]
      -dx_dxi[0][1]*dx_dxi[1][0]*dx_dxi[2][2]-dx_dxi[0][0]*dx_dxi[1][2]*dx_dxi[2][1];
    
    
    
}

