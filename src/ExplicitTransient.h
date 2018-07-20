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
    
private:
    
    ModelManagerT* fModel;
    
    ElementBaseT* fElement;
    
    
    
};
    
    
    
    
}

#endif