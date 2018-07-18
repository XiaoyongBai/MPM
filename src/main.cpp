/* Created by Xiaoyong Bai at CU Boulder, 07/17/2018 */


#include <iostream>
#include "ModelManagerT.h"

using namespace std;
using namespace MPM;

void recordTime();

int main(int argc, char **args){

cout << "ll"<< endl;
    recordTime();
    
    if(argc == 1){
        try{
            throw "Input file was not specified, try with an input file!!";
        }catch(const char* msg){
            cerr<<msg<<endl;
            return 0;
        }
    }
    
    //////////////////////////////////////////////
    /* read input file */
    //////////////////////////////////////////////
    ModelManagerT* model = new ModelManagerT();
    
    try{
        model->ReadInput(args[1]);
    }catch(const char* msg){
        cerr<<msg<<endl;
        return 0;
    }
    
    int numStep=model->GetNumStep();
    double time_step = model->GetDT();
    
    recordTime();
    

	return 0;

}


void recordTime(){
    time_t now;
    
    now= time(0);
    char* curr_time = ctime(&now);
    cout << "The MPM starts at: " << curr_time << endl;
}
