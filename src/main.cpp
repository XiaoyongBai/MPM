/* Created by Xiaoyong Bai at CU Boulder, 07/17/2018 */



#include "iostream"

using namespace std;

int main(int argc, char **args){

    // current date/time based on current system
    time_t now;
    
    now= time(0);
    char* curr_time = ctime(&now);
    cout << "The MPM starts at: " << curr_time << endl;
    
    /*
    if(argc <=1)
    {
        try
        {
            throw "Input file was not specified, try with an input file!!";
        }
        catch(const char* msg){
            cerr<<msg<<endl;
            return 0;
        }
    }*/
    
    cout << "hello mpm" << endl;

    
    now= time(0);
    curr_time = ctime(&now);
    cout << "\nThe MPM finishes at: " << curr_time << endl;
    
    
    
	

	return 0;

}
