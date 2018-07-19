/* created by Xiaoyong Bai at CU Boulder, 07/19/2018 */

#ifndef ELEMENTBASET_H_
#define ELEMENTBASET_H_

#include <iostream>
#include <vector>

#include "ShapeBaseT.h"


using namespace std;

namespace MPM{
    
class ElementBaseT{
    
public:
    
    ElementBaseT();
    ElementBaseT(int type);
    ~ElementBaseT();
    
    void setNodeCoord(vector<vector<double>>& coord){fNodeCoord=coord;};

    /* generate material points */
    /* returns coordiante and volume of each material point */
    virtual vector<vector<double>> generateMatPoints(int num_mp){return {};};
    
public:
    
    static ElementBaseT* create(int type);
    
protected:
    
    /* nodal information */
    vector<vector<double>> fNodeCoord;
    vector<vector<double>> fNodeVelo;
    
    ShapeBaseT* fShape;
};
    
    
}



#endif

