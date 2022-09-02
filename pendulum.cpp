#include "pendulum.h"

DoublePendulum::DoublePendulum(double lenght1_, double lenght2_, double theta1_, double theta2_, double gravity_ = 9.81, double mass = 1){
    lenght_1 = lenght1_;
    lenght_2 = lenght2_;
    theta_1 = theta1_;
    theta_2 = theta2_;

    //store initial position
    Point Initial;
    Initial.time = 0;
    Initial.theta1 = theta_1;
    Initial.theta2 = theta_2;

    Points.push_back(Initial);

    //set Lagrangian functions

};

void DoublePendulum::Solver(double Time, double h){

};

