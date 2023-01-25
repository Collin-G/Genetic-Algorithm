#include <iostream>
#include <math.h>
#include <random>
#include <vector>
#include <cmath>

//class which contains randomly generated x,y,z values for a mathematical function
class Solution{
    public:
        Solution(double x, double y, double z){
            _x = x;
            _y = y;
            _z = z;
            

            double ans  = (6*x+ +std::pow(y,2) -std::pow(z,2)) - 35;
            _ans = ans;
            //solutions that give largest value have highest rank
            _rank = 1/ans;
        }

        
        double get_rank(){
            return _rank;
        }

        double get_x(){
            return _x;
        
        }
        double get_y(){
            return _y;
        }

        double get_z(){
            return _z; 
        }

        double get_ans(){
            return _ans;
        }
        

    private:
        double _x{};
        double _y{};
        double _z{};
        double _rank{};
        double _ans{};

};

//store generated solutions in vector
std::vector<Solution> trials;


void sort(std::vector<Solution> &t){
    //sort entries from first to last rank
    bool sorted  = false;
    while(!sorted){
        for(int i{0}; i<trials.size(); ++i){
            if(trials[i+1].get_rank() > trials[i].get_rank()){
                Solution temp(0,0,0); 
                temp = trials[i];
                trials[i] = trials[i+1];
                trials[i+1] = trials[i];
                break;
            }
        }
        sorted = true;
    }

}

int main(){
    bool done = false;
    std::default_random_engine solution_generator;
    std::uniform_real_distribution<double> distribution(-1000,1000); 
    for(int i{0}; i<100; ++i){
        double x = distribution(solution_generator);
        double y = distribution(solution_generator);
        double z = distribution(solution_generator);

        Solution test(x,y,z);
        trials.push_back(test);
    }

    sort(trials);
    

    while(!done){

        //only generate values which lie within the range of the top 10 solutions
        double xmin = trials[10].get_x();
        double xmax = trials[0].get_x();
        
        double ymin = trials[10].get_y();
        double ymax = trials[0].get_y();

        double zmin = trials[10].get_z();
        double zmax = trials[10].get_z();

        trials.clear();

        std::default_random_engine solution_generator;
        std::uniform_real_distribution<double> xdistribution(xmin,xmax);
        std::uniform_real_distribution<double> ydistribution(ymin,ymax);
        std::uniform_real_distribution<double> zdistribution(zmin, zmax);

        for(int i{0}; i <100; ++i){
            double x = xdistribution(solution_generator);
            double y = ydistribution(solution_generator);
            double z = zdistribution(solution_generator);

            Solution test(x,y,z);
            
            trials.push_back(test);
        }

        sort(trials);
        std::cout<<trials[0].get_ans()<<std::endl;

        if(abs(trials[0].get_ans() - trials[99].get_ans()) <= 0.1){
            std::cout<<"x: " <<trials[0].get_x()<<" y: "<<trials[0].get_y()<<" z: "<<trials[0].get_z()<<std::endl;
            std::cout<<"max: "<<trials[0].get_ans();
            done = true;
        }

        
        
    } 
}

