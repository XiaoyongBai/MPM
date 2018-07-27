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
    
    fx_left=range[0];
    fx_right=range[1];
    fy_left=range[0];
    fy_right=range[1];
    fz_left=range[0];
    fz_right=range[1];
    
    double x_length=fx_right-fx_left;
    double y_length=fy_right-fy_left;
    double z_length=fz_right-fz_left;
    
    fx_nel = ceil(x_length/esize);
    fy_nel = ceil(y_length/esize);
    fz_nel = ceil(z_length/esize);
    
    int nnd_x = fx_nel+1;
    int nnd_y = fy_nel+1;
    int nnd_z = fz_nel+1;
    
    fx_inc = x_length/(fx_nel+0.0);
    fy_inc = y_length/(fy_nel+0.0);
    fz_inc = z_length/(fz_nel+0.0);
    
    //generate nodes
    for (int zi=0; zi<nnd_z; zi++) {
        double z = zi*fz_inc;
        
        for (int yi=0; yi<nnd_y; yi++) {
            double y = yi*fy_inc;
            
            for (int xi=0; xi<nnd_x; xi++) {
                double x = xi*fx_inc;
                
                fNodes_bkg.push_back({x,y,z});
            }
        }
    }
    
    //generate elements
    int nnd_layer = nnd_x*nnd_y;
    
    for (int zi=0; zi<fz_nel; zi++) {
        int z_offset = zi*nnd_layer;
        
        for (int yi=0; yi<fy_nel; yi++) {
            int y_offset = yi*nnd_x;
            
            for (int xi=0; xi<fx_nel; xi++) {
                
                int id=z_offset+y_offset+xi;
                
                fIEN_bkg.push_back({id, id+1, id+1+nnd_x, id+nnd_x,
                    id+nnd_layer, id+1+nnd_layer, id+1+nnd_x+nnd_layer, id+nnd_x+nnd_layer});
                
                fElementCoord_bkg.push_back({fNodes_bkg[id], fNodes_bkg[id+1], fNodes_bkg[id+1+nnd_x],
                    fNodes_bkg[id+nnd_x],fNodes_bkg[id+nnd_layer], fNodes_bkg[id+1+nnd_layer],
                    fNodes_bkg[id+1+nnd_x+nnd_layer], fNodes_bkg[id+nnd_x+nnd_layer]});
                
            }
        }
        
        
        
    }
    
    int nel = fIEN_bkg.size();
    fBKG_Element_MP_table=vector<vector<int>>(nel, {});

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
                point->setInitCoord(mp_coord);
                
                fMatPts.push_back(point);
            }
            
            
        }
        
        
    }
    
}




void ModelManagerT::constructElementMPTable(void){
    
    //clear the table
    int nel=fBKG_Element_MP_table.size();
    for (int i=0; i<nel; i++) {
        fBKG_Element_MP_table[i].clear();
    }
    
    
    int nmp = fMatPts.size(); //number of material points
    
    for (int ni=0; ni<nmp; ni++) {
        
        vector<double> coord = fMatPts[ni]->getCoord();
        
        if (coord[0]>fx_right || coord[0]<fx_left || coord[1]>fy_right || coord[1]<fy_left
            || coord[2]>fz_right || coord[2]<fz_left) continue;  //material point is out of range
        
        
        int x_index = floor( (coord[0]-fx_left)/fx_inc );
        int y_index = floor( (coord[1]-fy_left)/fy_inc );
        int z_index = floor( (coord[2]-fz_left)/fz_inc );
        
        int eid = z_index*(fx_nel*fy_nel) + y_index*fx_nel + x_index;
        
        fBKG_Element_MP_table[eid].push_back(ni);
    }
        
    
}
