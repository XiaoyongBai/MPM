/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */

#include "InputT.h"

#include <fstream>
#include <cstring>
#include "stdio.h"
#include "stdlib.h"

using namespace std;
using namespace MPM;

InputT::InputT()
{
	fNumStep=1;
	fDT=0;
    
    fBKG_range=vector<double>(6, 0.0);
}

InputT::~InputT()
{
    cout << "InputT is destroyed\n";
    
    for (int i=0; i<fIENs.size(); i++) {
        delete [] fIENs[i];
    }
}

void InputT::ReadInput(const char* fileName)
{
    cout << "reading " << fileName << endl;
    
    ifstream fin;
    fin.open(fileName);
    
    if(!fin.good())
    {
        cout << fileName << " was not found \n";
        throw "file was not found";
    }
    
    /* read time step parameters */
    fin >> fNumStep;
    fin >> fDT;
    
    /* read material parameters */
    fin >> fNumMat;
    for (int i=0; i<fNumMat; i++) {
        int id;
        fin >> id;
        
        if (fMatNames.find(id)!=fMatNames.end()) {
            throw "\n!! Input file error:: id of materials needs to be unique!!\n";
        }
        
        string name;
        fin >> name;
        fMatNames[id]=name;
        
        int np; //number of parameters
        fin >> np;
        for (int j=0; j<np; j++) {
            double para;
            fin>>para;
            fMatConstants[id].push_back(para);
        }
    }
    
    /* read background mesh range */
    double x_left, x_right, y_left, y_right, z_left, z_right;
    double esize; //length of element
    fin >>x_left>>x_right>>y_left>>y_right>>z_left>>z_right>>esize;
    
    fBKG_range={x_left,x_right,y_left,y_right,z_left,z_right};
    fESIZE=esize;
    
    /* read Element groups */
    fin >> fNumGroup;
    
    fElementConstants=vector<vector<int>> (fNumGroup, vector<int>(5,0));
    fIENs=vector<int*>(fNumGroup, NULL);
    
    for (int i=0; i<fNumGroup; i++) {
        int numElements; fin>>numElements;
        int eleType; fin>>eleType; //element type
        int eleNND; fin>>eleNND; //number of nodes per element
        int mat_id; fin>>mat_id; //id of the material
        int num_mp; fin>>num_mp; //number of material points per element
        
        fElementConstants[i][0]=numElements;
        fElementConstants[i][1]=eleType;
        fElementConstants[i][2]=eleNND;
        fElementConstants[i][3]=mat_id;
        fElementConstants[i][4]=num_mp;
        
        //allocate memory for IEN
        fIENs[i] = new int[numElements*eleNND];
        
        for (int j=0; j<numElements; j++) {
            for (int k=0; k<eleNND; k++) {
                fin>>fIENs[i][j*eleNND+k];
                fIENs[i][j*eleNND+k]-=1;
            }
        }
        
    }
    
    /* read Nodes' coordinates */
    fin>>fNumNodes;
    fNodes=vector<vector<double>>(fNumNodes, vector<double>(3,0));
    
    for (int i=0; i<fNumNodes; i++) {
        for (int j=0; j<3; j++) {
            fin>>fNodes[i][j];
        }
    }
    
    fin.close();
    
}





