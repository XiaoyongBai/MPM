/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */

#ifndef MATERIALBASET_H_
#define MATERIALBASET_H_

#include <string>
#include <vector>


using namespace std;

namespace MPM {

class MaterialBaseT
{
public:
    
    MaterialBaseT();
    ~MaterialBaseT();
    
    string getName(void){return fName;};
    int getNumPara(void){return fNumPara;}; //get the number of parameters
    
    virtual void setParameters(vector<double>& para) = 0;
    
    virtual double getDensity(void)=0;
    
    virtual void updateStress(vector<double>& strain) = 0;
    
    vector<double>* getCauchyStress(void){return &fCauchyStress;};

public:
    
    //create instance of materials by factory method
    static MaterialBaseT* create(string name);
    
protected:
    
    std::string fName;
    int fNumPara; //number of parameters
    
    vector<double> fCauchyStress;
    
};

}

#endif