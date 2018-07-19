/* created by Xiaoyong Bai at CU Boulder, 07/17/2017 */

#include "MaterialBaseT.h"
#include "mat_1.h"

using namespace std;
using namespace MPM;

MaterialBaseT::MaterialBaseT(){
    
}

MaterialBaseT::~MaterialBaseT(){
    
}



MaterialBaseT* MaterialBaseT::create(string name){
    
    if (name=="mat_1"){
        return new mat_1;
    }else{
        throw "\n !! MaterialBaseT::create(), unsupported material type !! \n";
    }
    
}


