/* created by Xiaoyong Bai at CU Boulder, 07/18/2017 */

#include "ShapeBaseT.h"
#include "HexShape8node.h"


using namespace std;
using namespace MPM;


ShapeBaseT::ShapeBaseT(){
    
}

ShapeBaseT::~ShapeBaseT(){
    
}

ShapeBaseT* ShapeBaseT::create(int type){
 
    if (type==1) {
        return new HexShape8node;
    }else{
        throw "\n !! ShapeBaseT::create(), unsupported element tyep !! \n";
    }
}