#include <iostream>
#include "PID.h"
using namespace std;
/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    p_error = 0.0;
    i_error = 0.0;
    d_error = 0.0;
    best_error =1000;
}

void PID::UpdateError(double cte) {
    d_error = cte - p_error;
    p_error = cte;
    i_error += cte;
}

double PID::TotalError() {
    return -(Kp*p_error + Kd*d_error + Ki*i_error);
}
double PID::Sum(std::vector<double> dp)
{
    int sum = 0; 

    for (int i = 0; i < dp.size(); i++){
    sum += dp[i];
    }
    cout<<"Sum"<<sum<<endl;
    return sum;
}
void PID::Twiddle(double tolerance, double cte)
{
    std::vector<double> p = {this->Kp, this->Ki, this->Kd};
    //std::vector<double> dp = [this->p_error, this->i_error, this->d_error];
    std::vector<double> dp = {1, 1, 1};

    while (Sum(dp) > tolerance){
        for (int i=0; i<p.size(); i++){
            p[i]+= dp[i];
            if (fabs(cte)< fabs(best_error)){
                best_error = cte;
                dp[i]*=1.1;
            }
            else {
                p[i] -= 2*dp[i];
                if (fabs(cte) < fabs(best_error)){
                    best_error = cte;
                    dp[i]*=1.1;
                }
                else {
                    p[i] +=dp[i];
                    dp[i]*=0.9;
                }
            }
        }
    }
    cout << "K values " << p[0] << " "<< p[1]  << " "<<p[2]<< endl;
    Kp = p[0];
    Ki = p[1];
    Kd = p[2];
    cout << "Error values " << dp[0] << " "<< dp[1]  << " "<<dp[2]<< endl;
    p_error = dp[0];
    i_error = dp[1];
    d_error = dp[2];
}