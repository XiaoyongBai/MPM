/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */

#include <iostream>
#include <cmath>

#include "mat_1.h"

using namespace std;
using namespace MPM;

mat_1::mat_1(){
    
    fName="mat_1";
    fNumPara=3;

    fCauchyStress=vector<double>(6,0);
    
}


mat_1::~mat_1(){
    
}


void mat_1::setParameters(vector<double>& para){
    
    fE=para[0]; //Young's modulus
    fNu=para[1]; //Poisson's ratio
    fDensity=para[2];
    
    fLambda=fE*fNu/((1.0+fNu)*(1.0-2.0*fNu));
    fMu=fE/(2.0*(1+fNu));
    
    fCp=pow((fLambda+2*fMu)/fDensity, 0.5);
    fCs=pow(fMu/fDensity, 0.5);
}

// strain={e_11, e_22, e_33, 2*e_23, 2*e_13, 2*e_12};
// stress={s_11, s_22, s_33, s_23, s_13, s_12};
//s_ij=Lambda*e_kk*delta_ij+2*Mu*e_ij

//!!Note: the strain should be the increment, instead of the totoal strain.!!
void mat_1::updateStress(vector<double>& strain){
    
    double v=fLambda*(strain[0]+strain[1]+strain[2]);
    
    fCauchyStress[0] += v + 2*fMu*strain[0];
    fCauchyStress[1] += v + 2*fMu*strain[1];
    fCauchyStress[2] += v + 2*fMu*strain[2];
    fCauchyStress[3] += fMu*strain[3];
    fCauchyStress[4] += fMu*strain[4];
    fCauchyStress[5] += fMu*strain[5];
    
}