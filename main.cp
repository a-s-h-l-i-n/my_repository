/*
      FILE NAME: Harris5
       DUE DATE: 24 November 2015
         AUTHOR: Ashlin Harris
         COURSE: CSCI 3180
    DESCRIPTION: Approximates he value of an ODE
          INPUT: The equation, method, initial point, final value, and step size  are prompted.
         OUTPUT: Values of t and x are diplayed on a table.
*/

#include <iostream>

// selectable ODEs
double g0(double,double); // x' = x/(1+t)
double g1(double,double); // x' = t+x
double g2(double,double); // x' = t-x
double g3(double,double); // x' = (t-x)/(t+x)

// methods of approximation
double       Euler(double h, double t, double x, double (*function)(double,double));
double        Heun(double h, double t, double x, double (*function)(double,double));
double Runge_Kutta(double h, double t, double x, double (*function)(double,double));

int main()
{
    // pointers for equation and method
    double (*equation)(double,double) = &g0;
    double (*method)(double,double,double,double(*)(double,double)) = &Euler;
    
    int       temp; // stores an integer selection from a menu
    double       t; // current t value; initially supplied by user
    double t_final; // final t value
    double       h; // step size
    double       x; // x value at t (analytical for initial t, approximate otherwise)
    
    // input equation
    std::cout << "\nPlease select a function"
              << "\n    0: x' = x/(1+t)"
              << "\n    1: x' = t+x"
              << "\n    2: x' = t-x"
              << "\n    3: x' = (t-x)/(t+x)"
              << "\nSelection: ";
    
    std::cin  >> temp;
    
    // assign equation pointer
    switch(temp)
    {
        case 0: equation = &g0; break;
        case 1: equation = &g1; break;
        case 2: equation = &g2; break;
        case 3: equation = &g3; break;
    }
    
    // input method

    std::cout << "\nPlease select a method"
              << "\n    0: Euler"
              << "\n    1: Heun"
              << "\n    2: Runge-Kutta"
              << "\nSelection: ";
    
    std::cin  >> temp;
    
    // assign method pointer
    switch(temp)
    {
        case 0: method = &Euler;       break;
        case 1: method = &Heun;        break;
        case 2: method = &Runge_Kutta; break;
    }
    
    std::cout << "\nInitial t value?: ";
    std::cin  >> t;
    
    std::cout << "\nInitial x value?: ";
    std::cin  >> x;
    
    std::cout << "\nFinal t value?: ";
    std::cin  >> t_final;
    
    std::cout << "\nStep size?: ";
    std::cin  >> h;
    
    std::cout << "\n+-----------+-----------+"
              << "\n|         t |      x(t) |"
              << "\n|-----------+-----------|";
    
    while (t<=t_final)
    {
        printf("\n|%10f |%10f |", t, x);
        x = (*method)(h,t,x,equation);
        t += h;
    }
    std::cout << "\n+-----------+-----------+\n";

    return 0;
}

double g0(double t,double x) { return x/(1+t);     } // x' = x/(1+t)
double g1(double t,double x) { return t+x;         } // x' = t+x
double g2(double t,double x) { return t-x;         } // x' = t-x
double g3(double t,double x) { return (t-x)/(t+x); } // x' = (t-x)/(t+x)


double Euler(double h, double t, double x, double(*equation)(double,double))
    // approximate the next iteration of Euler's method
{
    return x+h*(*equation)(t,x);
}

double Heun(double h, double t, double x, double(*equation)(double,double))
    // approximate the next iteration of Heun's method
{
    double z = x+h*(*equation)(t,x);
    
    return x+(h/2)*( (*equation)(t,x) + (*equation)(t+h,z));
}

double Runge_Kutta(double h, double t, double x, double(*equation)(double,double))
    // approximate the next iteration of the Runge-Kutta method
{
    double k1 = h*(*equation)(t,x);
    double k2 = h*(*equation)(t+(h/2),x+(k1/2));
    double k3 = h*(*equation)(t+(h/2),x+(k2/2));
    double k4 = h*(*equation)(t+h,x+k3);
    
    return x + (1.0/6)*(k1+2*k2+2*k3+k4);
}