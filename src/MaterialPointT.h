/* created by Xiaoyong Bai at CU Boulder, 07/18/2018 */

#ifndef MATERIALPOINTT_H_
#define MATERIALPOINTT_H_

#include <string>
#include <vector>

#include "MaterialBaseT.h"

using namespace std;

namespace MPM {
    
    class MaterialPointT
    {
    public:
        
        MaterialPointT();
        ~MaterialPointT();
        
        
        double getMass(void){return fMass;}; //get the mass the point
        
        vector<double> getCoord(void){return fCoord;};
        vector<double> getDisplacement(void);
        vector<double> getVelo(void){return fVel;};
        MaterialBaseT* getMaterial(void){return fMaterial;};
        
        void setMaterial(MaterialBaseT* mat);
        
        void setMass(double mass){fMass=mass;};
        void setInitCoord(vector<double>& coord){fInitCoord=fCoord;}; //initital coordinates
        void setCoord(vector<double>& coord){fCoord=coord;};
        void setVelocity(vector<double>& velo){fVel=velo;};
        void updateCoord(double dt);
        
    private:
        
        double fMass;
        
        /* coordiante, velocity and acceleration of the point */
        vector<double> fInitCoord;
        vector<double> fCoord;
        vector<double> fVel;
        vector<double> fAcc;
        
        MaterialBaseT* fMaterial;
        
    };
    
}

#endif