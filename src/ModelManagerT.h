/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */

#ifndef MODELMANAGERT_H_
#define MODELMANAGERT_H_

#include "InputT.h"
#include "MaterialBaseT.h"

namespace MPM{


class ModelManagerT
{
public:

	ModelManagerT();
	~ModelManagerT();

    int getNumStep(void){return fNumStep;};
    double getDT(void){return fDT;};

	void readInput(const char* name);

    void constructMaterialTable(void);
    
    void generateMPM(void);
    
    
private:
    
	/* algorithm parameters */
	double fDT;
	int fNumStep;

    /* Element to create Material Points */
    int fNumGroups_mp;
    vector<vector<int>> fElementConstants_mp; //algorithmical constants for element groups
    vector<int*> fIENs_mp; //Element connectivities
    vector<vector<double>> fNodes_mp; //Nodal coordiantes
    
	InputT fInput;
    
    unordered_map<int, MaterialBaseT*> fMatTables;
    
};


} /* name space */



#endif /* MODELMANAGERT_H_ */
