/* created by Xiaoyong Bai at CU Boulder, 07/17/2018 */

#include <iostream>

#include "ModelManagerT.h"
#include "ShapeBaseT.h"
#include "ElementBaseT.h"

using namespace std;
using namespace MPM;


ModelManagerT::ModelManagerT(){

}

ModelManagerT::~ModelManagerT(){

}


void ModelManagerT::readInput(const char* name)
{
	fInput.ReadInput(name);
    
    fNumStep=fInput.getNumStep();
    fDT=fInput.getTimeStepSize();
    
    /* set up materials */
    constructMaterialTable();
    
    /* set up background mesh */
    generateBackgroundMesh();
    
    /* set up nodes */
    fNodes_mp=fInput.getNodes();
    
    /* generate material points */
    generateMPs();

    
    fInput.~InputT();
}


void ModelManagerT::constructMaterialTable(){
    
    unordered_map<int, string>* matNameTalbe = fInput.getMatNameTable();
    unordered_map<int, vector<double>>* matParaTable = fInput.getMatParaTable();
    
    
    for (auto it=matNameTalbe->begin(); it!=matNameTalbe->end(); it++) {
        
        int id = it->first;
        string name = it->second;
        vector<double> parameters = (*matParaTable)[id];
        
        fMatTables[id] = MaterialBaseT::create(name);
        
        if (parameters.size()!=fMatTables[id]->getNumPara()) {
            throw "\n !! ModelManagerT::ConstructMaterialTable, number of parameters does not match !! \n";
        }
        
        fMatTables[id]->setParameters(parameters);
        
        vector<double> strain={0.0,0.01,0,0.2,0.3,0.4};
        fMatTables[id]->updateStress(strain);
        vector<double>* stress=fMatTables[id]->getCauchyStress();
        
        /*
        cout << "stress="<< endl;
        for (int i=0; i<stress->size(); i++) {
            cout << stress->at(i) << endl;
        }
        
        cout << name << endl;*/
        
    }
    
}


void ModelManagerT::generateBackgroundMesh(){
    
    vector<double> range = fInput.getBKG_range();
    double esize = fInput.getESize();
    
    
    generateBackgroundMesh(range, esize);
}


void ModelManagerT::generateBackgroundMesh(vector<double> range, double esize){
    
    fIEN_bkg.clear();
    fNodes_bkg.clear();
    
    double x_left=range[0];
    double x_right=range[1];
    double y_left=range[0];
    double y_right=range[1];
    double z_left=range[0];
    double z_right=range[1];
    
    double x_length=x_right-x_left;
    double y_length=y_right-y_left;
    double z_length=z_right-z_left;
    
    int nel_x = ceil(x_length/esize);
    int nel_y = ceil(y_length/esize);
    int nel_z = ceil(z_length/esize);
    
    int nnd_x = nel_x+1;
    int nnd_y = nel_y+1;
    int nnd_z = nel_z+1;
    
    double inc_x = x_length/(nel_x+0.0);
    double inc_y = y_length/(nel_y+0.0);
    double inc_z = z_length/(nel_z+0.0);
    
    //generate nodes
    for (int zi=0; zi<nnd_z; zi++) {
        double z = zi*inc_z;
        
        for (int yi=0; yi<nnd_y; yi++) {
            double y = yi*inc_y;
            
            for (int xi=0; xi<nnd_x; xi++) {
                double x = xi*inc_x;
                
                fNodes_bkg.push_back({x,y,z});
            }
        }
    }
    
    //generate elements
    int nnd_layer = nnd_x*nnd_y;
    
    for (int zi=0; zi<nel_z; zi++) {
        int z_offset = zi*nnd_layer;
        
        for (int yi=0; yi<nel_y; yi++) {
            int y_offset = yi*nnd_x;
            
            for (int xi=0; xi<nel_x; xi++) {
                
                int id=z_offset+y_offset+xi;
                
                fIEN_bkg.push_back({id, id+1, id+1+nnd_x, id+nnd_x,
                    id+nnd_layer, id+1+nnd_layer, id+1+nnd_x+nnd_layer, id+nnd_x+nnd_layer});
            }
        }
        
    }
    
    cout << "num element=" << fIEN_bkg.size() << endl;
    

}



void ModelManagerT::generateMPs(){
    
    fElementConstants_mp = fInput.getElementConstants();
    fIENs_mp = fInput.getIENs();
    
    fNumGroups_mp = fElementConstants_mp.size();
    
    //loop over element groups
    for (int gi=0; gi<fNumGroups_mp; gi++) {
        
        int nel=fElementConstants_mp[gi][0];
        int ele_type=fElementConstants_mp[gi][1];
        int ennd=fElementConstants_mp[gi][2];
        int mat_id=fElementConstants_mp[gi][3]; //material id
        int nmp=fElementConstants_mp[gi][4]; //number of material points per element
        
        ElementBaseT* element = ElementBaseT::create(ele_type);
        
        vector<vector<double>> eleCoords(ennd, vector<double>(3,0));
        
        //loop over elements
        for (int ei=0; ei<nel; ei++) {
            
            //extract element nodes
            for(int ni=0; ni<ennd; ni++){
                int nid=fIENs_mp[gi][ei*3+ni];
 
                eleCoords[ni]=fNodes_mp[nid];
            }
            
            element->setNodeCoord(eleCoords);
            
            vector<vector<double>> mp = element->generateMatPoints(nmp);
            
            
            //loop over material points
            for (int mi=0; mi<mp.size(); mi++) {
                vector<double> mp_coord (3,0.0);
                for (int di=0; di<3; di++) mp_coord[di]=mp[mi][di];
                double v=mp[mi][3];
                MaterialBaseT* material = fMatTables[mat_id];
                double density = material->getDensity();
                double mass=v*density;
                
                MaterialPointT* point = new MaterialPointT;
                point->setMaterial(material);
                point->setMass(mass);
                point->setCoord(mp_coord);
                
                fMatPts.push_back(point);
            }
            
            
        }
        
        
    }
    
    
}