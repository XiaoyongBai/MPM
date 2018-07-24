/* created by Xiaoyong Bai at CU Boulder, 07/19/2018 */

#ifndef SOLIDELEMENTMPM_H_
#define SOLIDELEMENTMPM_H_

#include <iostream>
#include <vector>

#include "ElementBaseT.h"


using namespace std;

namespace MPM{
    
class SolidElementMPM : public ElementBaseT {
        
public:
        
    SolidElementMPM();
    SolidElementMPM(int type);
    
    ~SolidElementMPM();
                
    /* generate material points */
    /* returns coordiante and volume of each material point */
    vector<vector<double>> generateMatPoints(int num_mp);
    
    void setMaterialPoints(vector<MaterialPointT*>* mp, vector<int>& index);
    
    //compute the shape coordinates of the material point
    void computeMPShapeCoord(void);
 
    void computeMassVelo(void);
    void computeForce(double dt);
    
};
    
    
}



#endif

