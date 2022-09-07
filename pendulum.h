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
    double vel1;
    double vel2;
};

class DoublePendulum{

    public:
        //constructor and destructor
        DoublePendulum(double l1 = 1, double l2 = 1, double t1 = 1, double t2 = 0.5, double gravity_ = 9.81, double m1 = 1, double m2 = 1);
        ~DoublePendulum() = default;

        //Runge-kutta 4th Order Solver
        void Solver(double Time, double step);

        //draw graphs

    private:

        double lenght_1; 
        double lenght_2;
        double theta_1;
        double theta_2;

        double mass_1; //kg
        double mass_2;

        double G = 9.81;
        
        //functions to be solved
        vector<function<double(Point)>> functions;

        //store results
        vector<Point> Points;
};

#endif