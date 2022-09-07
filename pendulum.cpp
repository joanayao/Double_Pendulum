#include "pendulum.h"

DoublePendulum::DoublePendulum(double lenght1_, double lenght2_, double theta1_, double theta2_, double gravity_, double mass1_, double mass2_){
    lenght_1 = lenght1_;
    lenght_2 = lenght2_;
    theta_1 = theta1_;
    theta_2 = theta2_;
    G = gravity_;
    mass_1 = mass1_;
    mass_2 = mass2_;

    //store initial position
    Point Initial;
    Initial.time = 0;
    Initial.theta1 = theta_1;
    Initial.theta2 = theta_2;
    Initial.vel1 = 0;
    Initial.vel2 = 0;

    Points.push_back(Initial);

    //set Lagrangian functions
    function<double(Point)> acel_2 = [this](Point P){
        return ((mass_1+mass_2)*G*sin(P.theta1)*cos(P.theta1-P.theta2)*(lenght_1*P.vel1*P.vel1*sin(P.theta1-P.theta2)-G*sin(P.theta2))
        -mass_2*lenght_2*P.vel2*sin(P.theta1-P.theta2))/((mass_1+mass_2)*lenght_1-mass_2*lenght_1*lenght_2*cos(P.theta1-P.theta2)*cos(P.theta1-P.theta2));
    } ;

    function<double(Point)> acel_1 = [this](Point P){
        return lenght_1*P.vel2*P.vel2*sin(P.theta1-P.theta2)-G*sin(P.theta2)-lenght_1*cos(P.theta1-P.theta2)*
        (((mass_1+mass_2)*G*sin(P.theta1)*cos(P.theta1-P.theta2)*(lenght_1*P.vel1*P.vel1*sin(P.theta1-P.theta2)-G*sin(P.theta2))
        -mass_2*lenght_2*P.vel2*sin(P.theta1-P.theta2))/((mass_1+mass_2)*lenght_1-mass_2*lenght_1*lenght_2*cos(P.theta1-P.theta2)*cos(P.theta1-P.theta2)));
    };

    function<double(Point)> vel_1 = [this](Point P){return P.vel1;};
    
    function<double(Point)> vel_2 = [this](Point P){return P.vel2;};    

    functions.push_back(acel_1);
    functions.push_back(acel_2);
    functions.push_back(vel_1);
    functions.push_back(vel_2);

};

void DoublePendulum::Solver(double Time, double step){

    double current_time = 0;

    double k1, k2, k3, k4, // for function acel_1
        l1, l2, l3, l4, // for function acel_2
        m1, m2, m3, m4, // for function vel_1
        n1, n2, n3, n4; // for function vel_2

    int i = 0;
    Point aux; // auxiliar point used for intermediate contas

    while(current_time < Time){

        k1 = functions[1](Points[i]); 
        l1 = functions[2](Points[i]);
        m1 = functions[3](Points[i]);
        n1 = functions[4](Points[i]);

        aux.time = current_time + step/2;
        aux.vel1 = Points[i].vel1 + step/2*k1;
        aux.vel2 = Points[i].vel2 + step/2*l1;
        aux.theta1 = Points[i].theta1 + step/2*m1;
        aux.theta2 = Points[i].theta2 + step/2*n1;

        k2 = functions[1](aux); 
        l2 = functions[2](aux);
        m2 = functions[3](aux);
        n2 = functions[4](aux);

        aux.vel1 = Points[i].vel1 + step/2*k2;
        aux.vel2 = Points[i].vel2 + step/2*l2;
        aux.theta1 = Points[i].theta1 + step/2*m2;
        aux.theta2 = Points[i].theta2 + step/2*n2;

        k3 = functions[1](aux); 
        l3 = functions[2](aux);
        m3 = functions[3](aux);
        n3 = functions[4](aux);

        aux.time = current_time + step;
        aux.vel1 = Points[i].vel1 + step*k3;
        aux.vel2 = Points[i].vel2 + step*l3;
        aux.theta1 = Points[i].theta1 + step*m3;
        aux.theta2 = Points[i].theta2 + step*n3;

        k4 = functions[1](aux); 
        l4 = functions[2](aux);
        m4 = functions[3](aux);
        n4 = functions[4](aux);

        // final result (next point)
        aux.vel1 = Points[i].vel1 + 1./6.*step*(k1+2*k2+2*k3+k4);
        aux.vel2 = Points[i].vel2 + 1./6.*step*(l1+2*l2+2*l3+l4);
        aux.theta1 = Points[i].theta1 + 1./6.*step*(m1+2*m2+2*m3+m4);
        aux.theta2 = Points[i].theta2 + 1./6.*step*(n1+2*n2+2*n3+n4);

        Points.push_back(aux);
        i++;
        current_time += step;

    }

};

