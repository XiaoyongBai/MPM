/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */

#ifndef INPUTT_H_
#define INPUTT_H_

#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

namespace MPM{

class InputT
{
public:
	InputT();
	~InputT();

    void ReadInput(const char* name);

    int getNumStep(void){return fNumStep;}; //get number of steps

    double getTimeStepSize(void){return fDT;}; //get time step size
    
    unordered_map<int, string>* getMatNameTable(void){return &fMatNames;};
    unordered_map<int, vector<double>>* getMatParaTable(void){return &fMatConstants;};
    
    
    vector<double> getBKG_range(void){return fBKG_range;};
    double getESize(void){return fESIZE;};
    
    vector<vector<int>> getElementConstants(void){return fElementConstants;};
    vector<int*> getIENs(void){return fIENs;};
    vector<vector<double>> getNodes(void){return fNodes;};
    
private:
    
    /*time step parameters*/
	
    int fNumStep; //number of time step
	double fDT; //time step size

    /*Material parameters*/
    
    int fNumMat; //number of materials involved
    unordered_map<int, string> fMatNames;
    unordered_map<int, vector<double>> fMatConstants;

    /* Background mesh range */
    vector<double> fBKG_range;
    double fESIZE;
    
    /*Elements for material points*/
    
    int fNumGroup; //number of element groups
    vector<vector<int>> fElementConstants; //algorithmical constants for elelement groups
    vector<int*> fIENs; //Element connectivities
    
    int fNumNodes;
    vector<vector<double>> fNodes; //Nodes' coordiantes
};


}/*namespace*/

#endif /* INPUTT_H_ */










