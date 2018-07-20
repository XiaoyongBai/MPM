/* created by Xiaoyong Bai at CU Boulder, 07/18/2018 */

#ifndef SHAPEBASET_H_
#define SHAPEBASET_H_

#include <string>
#include <vector>


using namespace std;

namespace MPM {

class ShapeBaseT
{
public:
    
    ShapeBaseT();
    ~ShapeBaseT();
    
    int getENND(){return fNND;};
    
    //set up the nodal coordiantes
    void setCoord(vector<vector<double>>* coord){fCoords=coord;};
    
    //evaluate shape values and its derivatives
    virtual void evaluate(vector<double>& xi)=0;

    vector<double> getX(void){return fX;};
    double getJ(void){return fJ;};
    
    
public:
    
    //create instance of materials by factory method
    static ShapeBaseT* create(int type);
    
protected:
    
    int fNND; //number of nodes per element
    vector<vector<double>>* fCoords; //coordinates of the nodes
    
    vector<double> fN; //value of the shape functions
    vector<vector<double>> fDN; //Derivative of N w.r.t xi (shape coord)
    
    vector<double> fX; //coordinate of the point under evaluation
    double fJ; //Jacobian at the point
    
    
};

}

#endif
