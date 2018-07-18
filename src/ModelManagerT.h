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

    int GetNumStep(void){return fNumStep;};
    double GetDT(void){return fDT;};


	void ReadInput(const char* name);

    void ConstructMaterialTable(void);

private:
	/**
	 * algorithm parameters
	 */
	double fDT;
	int fNumStep;
	int fNQ;

    
	InputT fInput;
    
    unordered_map<int, MaterialBaseT*> fMatTables;
    
};


} /* name space */



#endif /* MODELMANAGERT_H_ */
