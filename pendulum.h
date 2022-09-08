#ifndef __DoublePendulum__
#define __DoublePendulum__

#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

//ROOT includes
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"

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
        DoublePendulum(double l1 = 1, double l2 = 1, double t1 = 0.5, double t2 = 0.5, double gravity_ = 9.81, double m1 = 1, double m2 = 1);
        ~DoublePendulum() = default;

        //Runge-kutta 4th Order Solver
        void Solver(double Time, double step);

        //draw graphs
        // arguments for Y and X axis: "time", "theta1", "theta2", "vel1", "vel2"
        void DrawGraph(string Yaxis, string Xaxis = "time");

        vector<Point> GetPoints();

    private:

        //characteristics of the pendulum (constants)
        double lenght_1; 
        double lenght_2;
        double mass_1; //kg
        double mass_2;
        double G = 9.81;
        
        //functions to be solved
        vector<function<double(Point)>> functions;

        //store results
        vector<Point> Points;
};

#endif