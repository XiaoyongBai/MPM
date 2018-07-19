/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */

#ifndef MAT_1_H_
#define MAT_1_H_


#include <iostream>
#include "MaterialBaseT.h"


using namespace std;

namespace MPM{
    
class mat_1:public MaterialBaseT{

public:
    
    mat_1();
    ~mat_1();
    
    double getDensity(void){return fDensity;};
    
    void setParameters(vector<double>& para);
    
    void updateStress(vector<double>& strain);
    
private:
    
    double fE; //Young's modulus
    double fNu; //Poisson's ratio
    double fDensity;
    
    double fLambda, fMu; //Lame constant
    double fCp, fCs; //wave speeds
};


}


#endif