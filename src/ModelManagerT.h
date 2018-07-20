/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */

#ifndef MODELMANAGERT_H_
#define MODELMANAGERT_H_

#include "InputT.h"
#include "MaterialBaseT.h"
#include "MaterialPointT.h"


namespace MPM{


class ModelManagerT
{
public:

	ModelManagerT();
	~ModelManagerT();

    int getNumStep(void){return fNumStep;};
    double getDT(void){return fDT;};

    vector<MaterialPointT*>* getMatPts(void){return &fMatPts;};
    
	void readInput(const char* name);

    void constructMaterialTable(void);
    
    void generateBackgroundMesh(void);
    void generateBackgroundMesh(vector<double> range, double esize);
    
    void generateMPs(void);
    
    
private:
    
	/* algorithm parameters */
	double fDT;
	int fNumStep;

    /* Element to create Material Points */
    int fNumGroups_mp;
    vector<vector<int>> fElementConstants_mp; //algorithmical constants for element groups
    vector<int*> fIENs_mp; //Element connectivities
    vector<vector<double>> fNodes_mp; //Nodal coordiantes
    
    
    /* Material Points */
    vector<MaterialPointT*> fMatPts;
    
    /* read input */
	InputT fInput;
    
    /* Material table */
    unordered_map<int, MaterialBaseT*> fMatTables;
    
    /* Background mesh */
    vector<vector<int>> fIEN_bkg;
    vector<vector<double>> fNodes_bkg;
    
    
};


} /* name space */



#endif /* MODELMANAGERT_H_ */
