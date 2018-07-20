/* created by Xiaoyong Bai at CU Boulder, 07/19/2018 */

#include "ElementBaseT.h"
#include "SolidElementMPM.h"

using namespace std;
using namespace MPM;

ElementBaseT::ElementBaseT(){
    //do nothing
}

ElementBaseT::ElementBaseT(int type){
    //do nothing
}

ElementBaseT::~ElementBaseT(){
    delete fShape;
}

ElementBaseT* ElementBaseT::create(int type){
    
    if (type==1) {
        return new SolidElementMPM(type);
    }else{
        throw "\n!! ElementBaseT::create, unsupported element type !!\n";
    }
    
}


