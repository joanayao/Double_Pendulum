#include "pendulum.h"

DoublePendulum::DoublePendulum(double lenght1_, double lenght2_, double theta1_, double theta2_, double gravity_){
    lenght_1 = lenght1_;
    lenght_2 = lenght2_;
    theta_1 = theta1_;
    theta_2 = theta2_;
    mass = mass_;
    G = gravity_;

    //store initial position
    Point Initial;
    Initial.time = 0;
    Initial.theta1 = theta_1;
    Initial.theta2 = theta_2;
    Initial.vel_1 = 0;
    Initial.vel_2 = 0;

    Points.push_back(Initial);

    //set Lagrangian functions
    function<double(Point)> acel_2 = [this](Point P){
        return (G*sin(P.theta2)-lenght_2*P.vel_2*P.vel_2*sin(P.theta1)*cos(P.theta1)*(cos(P.theta2)*cos(P.theta2)-sin(P.theta2)*sin(P.theta2))
            -G*sin(P.theta1)*(cos(P.theta1)*cos(P.theta2)+sin(P.theta1)*sin(P.theta2))
            -lenght_1*P.vel_1*P.vel_1*(cos(P.theta1)*sin(P.theta2)-sin(P.theta1)*cos(P.theta2)))
            /(lenght_2*(1-(cos(P.theta1)*cos(P.theta2)+sin(P.theta1)*sin(P.theta2))*(cos(P.theta1)*cos(P.theta2)+sin(P.theta1)*sin(P.theta2))));
    } ;

    function<double(Point)> acel_1 = [this](Point P){
        return -(G*sin(P.theta2)-lenght_2*P.vel_2*P.vel_2*sin(P.theta1)*cos(P.theta1)*(cos(P.theta2)*cos(P.theta2)-sin(P.theta2)*sin(P.theta2))
            -G*sin(P.theta1)*(cos(P.theta1)*cos(P.theta2)+sin(P.theta1)*sin(P.theta2))
            -lenght_1*P.vel_1*P.vel_1*(cos(P.theta1)*sin(P.theta2)-sin(P.theta1)*cos(P.theta2)))
            /(1-(cos(P.theta1)*cos(P.theta2)+sin(P.theta1)*sin(P.theta2))*(cos(P.theta1)*cos(P.theta2)+sin(P.theta1)*sin(P.theta2)))
            -lenght_2*P.vel_2*P.vel_2*(sin(P.theta1)*cos(P.theta2)-cos(P.theta1)*sin(P.theta2))-G*sin(P.theta1);
    };

    function<double(Point)> vel_1 = [this](Point P){return P.vel_1;};
    
    function<double(Point)> vel_2 = [this](Point P){return P.vel_2;};    

    functions["A1"] = acel_1;
    functions["A2"] = acel_2;
    functions["V1"] = vel_1;
    functions["V2"] = vel_2;

};

void DoublePendulum::Solver(double Time, double step){

    double current_time = 0;

    while(current_time < Time){
        
    }

};

