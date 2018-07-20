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
    
    /* generate material points using the input finite elements and materials */
    void generateMPs(void);
    
    /* For each background element, determine the material points that it contiains */
    void constructElementMPTable(void);
    
private:
    
    /* read input */
    InputT fInput;
    
	/* algorithm parameters */
	double fDT;
	int fNumStep;
    
    /* Material table */
    unordered_map<int, MaterialBaseT*> fMatTables;
    
    /* Background mesh */
    double fx_left, fx_right, fy_left, fy_right, fz_left, fz_right; //range of the background mesh
    double fx_inc, fy_inc, fz_inc; //element size in each direction
    int fx_nel, fy_nel, fz_nel; //number of elements in each direction
    
    vector<vector<int>> fIEN_bkg;
    vector<vector<double>> fNodes_bkg;
    
    
    /* Element to create Material Points */
    int fNumGroups_mp;
    vector<vector<int>> fElementConstants_mp; //algorithmical constants for element groups
    vector<int*> fIENs_mp; //Element connectivities
    vector<vector<double>> fNodes_mp; //Nodal coordiantes
    
    
    /* Material Points */
    vector<MaterialPointT*> fMatPts;
    
    
    /* Material points in each background mesh */
    vector<vector<int>> fBKG_Element_MP_table;
    
};


} /* name space */



#endif /* MODELMANAGERT_H_ */
