#include <stdio.h>
#include <math.h>


//rozwiazanie dokladne
double yt(double t, double lambda);

// funkcja f(t,y)
double function(double y, double lambda);

//metoda jawna Eulera 
double Euler(double dt, int n, double yn, double lambda);

//metoda jawna RK2 trapezow 
double RK2(double dt, int n, double yn, double lambda);

//metoda jawna RK4
double RK4(double dt, int n, double yn, double lambda);

//funkcja wypisujaca wartosci dla danej metody
void wypiszF(double (*f)(double, int, double, double), double dt, 
            double lambda, double t0, double tn, double y0);

int main()
{

    double y0 = 1;
    double lambda = -1;
    double t0 = 0;
    double tn = 5;

    double dt;


    //wariant dt = 0.01
    dt = 0.01;
    printf("Wariant dt = %.2g\n",dt);

    wypiszF(Euler, dt, lambda, t0, tn, y0);
    wypiszF(RK2, dt, lambda, t0, tn, y0);
    wypiszF(RK4, dt, lambda, t0, tn, y0);


    //wariant dt = 0.1
    dt = 0.1;

    wypiszF(Euler, dt, lambda, t0, tn, y0);
    wypiszF(RK2, dt, lambda, t0, tn, y0);
    wypiszF(RK4, dt, lambda, t0, tn, y0);


    //wariant dt = 1.0
    dt = 1.0;

    wypiszF(Euler, dt, lambda, t0, tn, y0);
    wypiszF(RK2, dt, lambda, t0, tn, y0);
    wypiszF(RK4, dt, lambda, t0, tn, y0);


    //czesc druga




    return 0;
}



double yt(double t, double lambda)
{
    return exp(lambda * t);
}


double function(double y, double lambda)
{
    return lambda*y;
}


double Euler(double dt, int n, double yn, double lambda)
{
    return yn + dt * function(yn,lambda);
}


double RK2(double dt, int n, double yn, double lambda)
{
    double tn = dt*n;
    double k1 = function(yn,lambda);
    double k2 = function(yn + dt * k1, lambda);

    return yn + dt*(k1 + k2)/2.0;
}


double RK4(double dt, int n, double yn, double lambda)
{
    double tn = dt*n;
    double k1 = function(yn,lambda);
    double k2 = function(yn + dt*k1/2.0, lambda);
    double k3 = function(yn + dt*k2/2.0, lambda);
    double k4 = function(yn + dt*k3, lambda);

    return yn + dt*(k1 + k2 + k3 + k4)/6.0;
}


void wypiszF(double (*f)(double, int, double, double), double dt, 
            double lambda, double t0, double tn, double y0)
{
    double curr_t = t0;
    int n;
    double ex_val;
    double fn;

    while(curr_t <= tn)
    {
        n = curr_t/dt;
        ex_val = yt(curr_t, lambda);
        fn = f(dt,n,y0,lambda);

        //chwila czasowa, wartosc funkcji, blad
        //printf("%.2g\t%.5g\t%.5g\n", curr_t, fn, yt - fn );
        printf("%.2g\t%.5g\n", curr_t, fn);
        y0 = f(dt,n,y0,lambda);
        curr_t += dt;
    }

}







