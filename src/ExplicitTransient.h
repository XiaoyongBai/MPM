/* created by Xiaoyong Bai at CU Boulder, 07/19/2018 */

#ifndef EXPLICITTRANSIENT_H_
#define EXPLICITTRANSIENT_H_

#include <iostream>
#include <vector>

#include "ModelManagerT.h"
#include "ElementBaseT.h"

namespace MPM {
    
class ExplicitTransient{
    
public:
    ExplicitTransient(ModelManagerT* model);
    ~ExplicitTransient();
    
    
    void drive(void);
    
    void AssembleVector(vector<double>& gv, vector<double>* ev, int eid);
    
    void VTKfile_output(int step);
    
private:
    
    ModelManagerT* fModel;
    
    ElementBaseT* fElement;
    
    /* infos of background mesh */
    vector<vector<int>>* fIEN;
    vector<vector<vector<double>>>* fElementCoord;
    
    /* global vectors */
    vector<double> fMass;
    vector<double> fVelo; //grid velocity
    vector<double> fAcce; //grid acceleration
    
    vector<double> fForce; //force vector
    
};
    
    
    
    
}

#endif