/* created by Xiaoyong Bai at CU Boulder, 07/18/2017 */

#include "SolidElementMPM.h"

using namespace std;
using namespace MPM;

SolidElementMPM::SolidElementMPM(){
    
}

SolidElementMPM::SolidElementMPM(int type){
    
    if (type==1) {
        fShape=ShapeBaseT::create(1);
    }
    
}

/* num_mp=number of material points in 1D */
/* material points are equally-spaced in parent domain */
vector<vector<double>> SolidElementMPM::generateMatPoints(int num_mp){
    
    int total_num = num_mp*num_mp*num_mp;
    
    vector<vector<double>> result;
    
    /* specify the points in parent domain, i.e. their shape coordinates */
    vector<double> xi_1d(num_mp, 0.0);
    double inc = 2.0/(num_mp+0.0);
    for (int i=0; i<num_mp; i++) {
        xi_1d[i]=(0.5+i)*inc-1.0;
    }
    
    vector<double> xi(3,0.0);
    
    fShape->setCoord(&fNodeCoord);
    
    for (int i=0; i<num_mp; i++) {
        
        xi[0] = xi_1d[i];
        
        for (int j=0; j<num_mp; j++) {
            
            xi[1] = xi_1d[j];
            
            for (int k=0; k<num_mp; k++) {
                
                xi[2] = xi_1d[k];
                
                fShape->evaluate(xi);
                
                vector<double> x=fShape->getX();
                double J=fShape->getJ();
                double volume=J*8.0/(total_num+0.0);
                
                result.push_back({x[0], x[1], x[2], volume});
                
                
            }
        }
    }
    
    
    
    return result;
    
}