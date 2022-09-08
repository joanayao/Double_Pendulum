#include "pendulum.h"

DoublePendulum::DoublePendulum(double lenght1_, double lenght2_, double theta1_, double theta2_,
double gravity_, double mass1_, double mass2_){

    // store pendulum characteristics (constants)
    lenght_1 = lenght1_;
    lenght_2 = lenght2_;
    G = gravity_;
    mass_1 = mass1_;
    mass_2 = mass2_;

    // store initial position
    Point Initial;
    Initial.time = 0;
    Initial.theta1 = theta1_;
    Initial.theta2 = theta2_;
    Initial.vel1 = 0;
    Initial.vel2 = 0;
    Points.push_back(Initial);

    // Set Lagrangian functions

    // function for angular acceleration (theta1)
    function<double(Point)> acel_1 = [this](Point P){
        return (-(mass_1+mass_2)*G*sin(P.theta1)+mass_2*cos(P.theta1-P.theta2)*(lenght_1*P.vel1*P.vel1*sin(P.theta1-P.theta2)+G*sin(P.theta2))
        -mass_2*lenght_2*P.vel2*P.vel2*sin(P.theta1-P.theta2))/((mass_1+mass_2)*lenght_1-mass_2*lenght_1*lenght_2*cos(P.theta1-P.theta2)*cos(P.theta1-P.theta2));
    } ;

    // function for angular acceleration (theta2)
    function<double(Point)> acel_2 = [this](Point P){
        return lenght_1*P.vel2*P.vel2*sin(P.theta1-P.theta2)-G*sin(P.theta2)-lenght_1*cos(P.theta1-P.theta2)*
        (-(mass_1+mass_2)*G*sin(P.theta1)+mass_2*cos(P.theta1-P.theta2)*(lenght_1*P.vel1*P.vel1*sin(P.theta1-P.theta2)+G*sin(P.theta2))
        -mass_2*lenght_2*P.vel2*P.vel2*sin(P.theta1-P.theta2))/((mass_1+mass_2)*lenght_1-mass_2*lenght_1*lenght_2*cos(P.theta1-P.theta2)*cos(P.theta1-P.theta2));
        
    };

    // function for angular velocity (theta1)
    function<double(Point)> vel_1 = [this](Point P){return P.vel1;};
    
    // function for angular velocity (theta2)
    function<double(Point)> vel_2 = [this](Point P){return P.vel2;};    

    // store functions
    functions.push_back(acel_1);
    functions.push_back(acel_2);
    functions.push_back(vel_1);
    functions.push_back(vel_2);

};

void DoublePendulum::Solver(double Time, double step){

    double current_time = 0;

    // variables to store slopes 
    double k1, k2, k3, k4, // for function acel_1 (slope for vel1)
        l1, l2, l3, l4, // for function acel_2 (slope for vel2)
        m1, m2, m3, m4, // for function vel_1 (slope for theta1)
        n1, n2, n3, n4; // for function vel_2 (slope for theta2)

    int i = 0; // counter variable
    Point aux; // auxiliar point for intermediate calculations

    while(current_time < Time){

        // first slope
        k1 = functions[0](Points[i]); 
        l1 = functions[1](Points[i]);
        m1 = functions[2](Points[i]);
        n1 = functions[3](Points[i]);
        
        // set auxiliar point to use in second slope
        aux.time = current_time + step/2;
        aux.vel1 = Points[i].vel1 + step/2*k1;
        aux.vel2 = Points[i].vel2 + step/2*l1;
        aux.theta1 = Points[i].theta1 + step/2*m1;
        aux.theta2 = Points[i].theta2 + step/2*n1;

        // second slope
        k2 = functions[0](aux); 
        l2 = functions[1](aux);
        m2 = functions[2](aux);
        n2 = functions[3](aux);

        // set auxiliar point to use in third slope
        aux.vel1 = Points[i].vel1 + step/2*k2;
        aux.vel2 = Points[i].vel2 + step/2*l2;
        aux.theta1 = Points[i].theta1 + step/2*m2;
        aux.theta2 = Points[i].theta2 + step/2*n2;

        // third slope
        k3 = functions[0](aux); 
        l3 = functions[1](aux);
        m3 = functions[2](aux);
        n3 = functions[3](aux);

        // set auxiliar point to use in fourth slope
        aux.time = current_time + step;
        aux.vel1 = Points[i].vel1 + step*k3;
        aux.vel2 = Points[i].vel2 + step*l3;
        aux.theta1 = Points[i].theta1 + step*m3;
        aux.theta2 = Points[i].theta2 + step*n3;

        // fourth slope
        k4 = functions[0](aux); 
        l4 = functions[1](aux);
        m4 = functions[2](aux);
        n4 = functions[3](aux);

        // set aux with final result (next point)
        aux.vel1 = Points[i].vel1 + 1./6.*step*(k1+2*k2+2*k3+k4);
        aux.vel2 = Points[i].vel2 + 1./6.*step*(l1+2*l2+2*l3+l4);
        aux.theta1 = Points[i].theta1 + 1./6.*step*(m1+2*m2+2*m3+m4);
        aux.theta2 = Points[i].theta2 + 1./6.*step*(n1+2*n2+2*n3+n4);

        //store point
        Points.push_back(aux);

        // update counter and add the time
        i++;
        current_time += step;
    }
};

void DoublePendulum::DrawGraph(string Yaxis, string Xaxis){

    // declare vectores to store data
    vector<double> yy;
    vector<double> xx;

    // declare title string
    string Ytitle, Xtitle;

    // check argument for y axis, input data in vector yy accordingly and define y axis title
    if(Yaxis == "time"){
        for(int i = 0; i < Points.size(); ++i)
            yy.push_back(Points[i].time);
        Ytitle = "Time";
    }
    else if(Yaxis == "theta1"){
        for(int i = 0; i < Points.size(); ++i)
            yy.push_back(Points[i].theta1);
        Ytitle = "Theta 1";
    }
    else if(Yaxis == "theta2"){
        for(int i = 0; i < Points.size(); ++i)
            yy.push_back(Points[i].theta2);
        Ytitle = "Theta 2";
    }
    else if(Yaxis == "vel1"){
        for(int i = 0; i < Points.size(); ++i)
            yy.push_back(Points[i].vel1);
        Ytitle = "Angular velocity 1";
    }
    else if(Yaxis == "vel2"){
        for(int i = 0; i < Points.size(); ++i)
            yy.push_back(Points[i].vel2);
        Ytitle = "Angular velocity 2";
    }
    else{
        cout << "invalid argument :(" << endl;
        Ytitle = "";
    }

    // check argument for x axis, input data in vector xx accordingly and define x axis title
    if(Xaxis == "time"){
        for(int i = 0; i < Points.size(); ++i)
            xx.push_back(Points[i].time);
        Xtitle = "Time";
    }
    else if(Xaxis == "theta1"){
        for(int i = 0; i < Points.size(); ++i)
            xx.push_back(Points[i].theta1);
        Xtitle = "Theta 1";
    }
    else if(Xaxis == "theta2"){
        for(int i = 0; i < Points.size(); ++i)
            xx.push_back(Points[i].theta2);
        Xtitle = "Theta 2";
    }
    else if(Xaxis == "vel1"){
        for(int i = 0; i < Points.size(); ++i)
            xx.push_back(Points[i].vel1);
        Xtitle = "Angular velocity 1";
    }
    else if(Xaxis == "vel2"){
        for(int i = 0; i < Points.size(); ++i)
            xx.push_back(Points[i].vel2);
        Xtitle = "Angular velocity 2";
    }
    else{
        cout << "invalid argument :(" << endl;
        Xtitle = "";
    }

    if(!Ytitle.empty() && !Xtitle.empty()){   
        // declare canvas
        TCanvas C;

        // declare and construct graph
        TGraph *g = new TGraph(yy.size(), xx.data(), yy.data());
        g -> GetXaxis() -> SetTitle(Xtitle.data());
        g -> GetYaxis() -> SetTitle(Ytitle.data());
        g -> Draw("al");
        g -> SetLineColor(kPink-4);

        C.SaveAs("graph.png");
    }
}

vector<Point> DoublePendulum::GetPoints(){
    return Points;
}