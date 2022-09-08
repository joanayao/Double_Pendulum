#include "pendulum.h"

int main(){

    DoublePendulum DP;

    DP.Solver(60,0.0001);

    DP.DrawGraph("vel1","theta1");
    //DP.DrawGraph("theta1");

    return 0;
}