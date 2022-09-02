#ifndef __DoublePendulum__
#define __DoublePendulum__

#include <cmath>
#include <functional>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Point{
    double time;
    double theta1;
    double theta2;
    double vel_1;
    double vel_2;
};

class DoublePendulum{

    public:
        //constructor and destructor
        DoublePendulum(double l1, double l2, double t1, double t2, double gravity_ = 9.81);
        ~DoublePendulum() = default;

        //Runge-kutta 4th Order Solver
        void Solver(double Time, double step);

    private:

        double lenght_1; 
        double lenght_2;
        double theta_1;
        double theta_2;

        //double mass = 1; //kg

        double G = 9.81;
        
        //functions to be solved
        map<string,function<double(Point)>> functions;

        //store results
        vector<Point> Points;
};

#endif