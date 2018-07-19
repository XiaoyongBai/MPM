/* created by Xiaoyong Bai at CU Boulder, 07/18/2018 */

#ifndef HEXSHAPE8NODE_H_
#define HEXSHAPE8NODE_H_

#include <string>
#include <vector>

#include "ShapeBaseT.h"

using namespace std;

namespace MPM {

class HexShape8node: public ShapeBaseT{

public:
    
    HexShape8node();
    ~HexShape8node();
    
    void evaluate(vector<double>& xi);   
    
};

}

#endif
