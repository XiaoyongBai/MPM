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
    void setNodeVelo(vector<double>& velo){fNodeVelo=velo;};
    
    virtual void setMaterialPoints(vector<MaterialPointT*>* mp, vector<int>& index){;};
    
    /* generate material points */
    /* returns coordiante and volume of each material point */
    virtual vector<vector<double>> generateMatPoints(int num_mp){return {};};
    
    //compute the mass matrix and convective velocity
    virtual void computeMassVelo(void)=0;
    virtual void computeForce(double dt)=0;
    
    
    vector<double>* getMassMatrix(void){return &fMassMatrix;};
    vector<double>* getConvecVelo(void){return &fConvecVelo;};
    vector<double>* getForce(void){return &fForce;};
    
public:
    
    static ElementBaseT* create(int type);
    
protected:
    
    /* nodal information */
    vector<vector<double>> fNodeCoord;
    vector<double> fNodeVelo; //for simplicity of the computation, it's arranged in 1D-vector
    
    
    ShapeBaseT* fShape;
    
    /* Material Point infos */
    vector<MaterialPointT*>* fMP; //all material points in the model
    vector<int> fMP_index; //material points in this element
    vector<vector<double>> fMP_ShapeCoord; //shape coordinates of material points
    
    /* results */
    vector<double> fMassMatrix;
    vector<double> fConvecVelo; //Convective velocity of the grid nodes
    vector<double> fForce;
    
};
    
    
}



#endif

