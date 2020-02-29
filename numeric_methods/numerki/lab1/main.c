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



//funkcja V(t)
double Vfunction(double wv, double t);

double w0(double L, double C);

double Inn(double Iprev, double dt, double k1, double k2, double k3, double k4);
double Qnn(double Qprev, double dt, double k1, double k2, double k3, double k4);

double f(double I);
double g(double wv, double t, double R, double L, double C, double I, double Q);


void RK4_v2(double t0, double tlast, double dt, double I0, 
            double Q0, double L, double C, double R, double aw);



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


    dt = 1e-4;
    double R = 100;
    double L = 0.1;
    double C = 0.001;
    t0 = 2 * M_PI/w0(L,C);
    double tlast = 4*t0;



    RK4_v2(t0,tlast,dt,0,0,L,C,R,0.5);
    RK4_v2(t0,tlast,dt,0,0,L,C,R,0.8);
    RK4_v2(t0,tlast,dt,0,0,L,C,R,1.0);
    RK4_v2(t0,tlast,dt,0,0,L,C,R,1.2);
    



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


//CZESC 2

double Vfunction(double wv, double t)
{
    return 10*sin(wv * t);
}

double w0(double L, double C)
{
    return 1.0/sqrt(L*C);
}

double Inn(double Iprev, double dt, double k1, double k2, double k3, double k4)
{
    return Iprev + dt*(k1+k2+k3+k4)/6.0;
}

double Qnn(double Qprev, double dt, double k1, double k2, double k3, double k4)
{
    return Qprev + dt*(k1+k2+k3+k4)/6.0;
}

double f(double I)
{
    return I;
}

double g(double wv, double t, double R, double L, double C, double I, double Q)
{
    double A = Vfunction(wv,t)/L;
    double B = R*I/L;
    double F = Q/(L*C);

    return A - B - F; 
}



void RK4_v2(double t0, double tlast, double dt, double I0, 
            double Q0, double L, double C, double R, double aw)
{




    double curr_t = t0;
    int n;
    double In;
    double Qn;

    while(curr_t <= tlast)
    {

        n = curr_t/dt;
        In = I0;
        Qn = Q0;

        double tn = dt * n;
        double tn2 = dt * (n + 0.5);
        double wv = aw*w0(L,C);

        double k1i = g(wv, tn, R, L, C, In, Qn);
        double k1q = f(In);

        double k2i = g(wv, tn2, R, L, C, In + dt*k1i/2.0, Qn + dt*k1q/2.0);
        double k2q = f(In) + dt*k1i/2.0;

        double k3i = g(wv, tn2, R, L, C, In + dt*k2i/2.0, Qn + dt*k2q/2.0);
        double k3q = f(In) + dt*k2i/2.0;


        double k4i = g(wv, tn2, R, L, C, In + dt*k3i/2.0, Qn + dt*k3q/2.0);
        double k4q = f(In) + dt*k3i/2.0;




        printf("%.2g\t%.5g\t%.5g\n", curr_t, I0, Q0);

        I0 = Inn(I0, dt, k1i, k2i, k3i, k4i);
        Q0 = Qnn(Q0, dt, k1q, k2q, k3q, k4q);

        curr_t += dt;
    }



}





