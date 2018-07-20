/* created by Xiaoyong Bai at CU Boulder, 07/19/2018 */

#ifndef ELEMENTBASET_H_
#define ELEMENTBASET_H_

#include <iostream>
#include <vector>

#include "ShapeBaseT.h"
#include "MaterialPointT.h"

using namespace std;

namespace MPM{
    
class ElementBaseT{
    
public:
    
    ElementBaseT();
    ElementBaseT(int type);
    ~ElementBaseT();
    
    void setNodeCoord(vector<vector<double>>& coord){fNodeCoord=coord;};

    virtual void setMaterialPoints(vector<MaterialPointT*>* mp, vector<int>& index){;};
    
    /* generate material points */
    /* returns coordiante and volume of each material point */
    virtual vector<vector<double>> generateMatPoints(int num_mp){return {};};
    

    virtual void compute(void)=0;
    
public:
    
    static ElementBaseT* create(int type);
    
protected:
    
    /* nodal information */
    vector<vector<double>> fNodeCoord;
    vector<vector<double>> fNodeVelo;
    
    
    ShapeBaseT* fShape;
    
    /* Material Point infos */
    vector<MaterialPointT*>* fMP; //all material points in the model
    vector<int> fMP_index; //material points in this element
    vector<vector<double>> fMP_ShapeCoord; //shape coordinates of material points
    
    /* results */
    vector<double> fMassMatrix;
    vector<double> fForce;
    
};
    
    
}



#endif

