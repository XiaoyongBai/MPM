/* created by Xiaoyong Bai at CU Boulder, 07/19/2018 */

#include "ExplicitTransient.h"

using namespace std;
using namespace MPM;

ExplicitTransient::ExplicitTransient(ModelManagerT* model){
    
    fModel=model;
    
    fElement=ElementBaseT::create(1);
    
}

ExplicitTransient::~ExplicitTransient(){
    
}
