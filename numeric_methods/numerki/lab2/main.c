#include "stdio.h"
#include "math.h"

//tu w srodku iteracje po mi
double P_un(double uprev, int mi_max, double TOL, double dt, double B, int N, double y);

double N_un(double uprev, int mi_max, double TOL, double dt, double B, int N, double y);


double f1(int option, double B, int N, double y, double dt, double *u0, double TOL, int mi_max);

void wypiszF(int option, double dt, double u0, double B, int N, double y, int mi_max, double tmax, double TOL);


void wypiszF2(double uprev, double dt, double t, double b1, double b2, double c1, double c2, double u0, double B, int N, double y, int mi_max, double tmax, double TOL);






int main()
{
    double B = 0.001;
    double y = 0.1;
    double dt = 0.1;
    int N = 500;

    double tmax = 100;
    double TOL = 1e-6;
    int mi_max = 20;
    double u0 = 1;



    //metoda trapezow
    wypiszF(0, dt, u0, B,N,y,mi_max,tmax,TOL);
    printf("\n\n");
    wypiszF(1, dt,u0,B,N,y,mi_max,tmax,TOL);


    //metoda RK2

    u0 = 1;
    double c1 = 1/2. - sqrt(3)/6.;
    double c2 = 1/2. + sqrt(3)/6.;
    double a11 = 1/4.;
    double a12 = a11 - sqrt(3)/6.;
    double a21 = a11 + sqrt(3)/6.;
    double a22 = a11;

    double b1 = 1/2.;
    double b2 = b1;

    //void wypiszF2(double uprev, double dt, double t, double b1, double b2, double c1, double c2, double u0, double B, int N, double y, int mi_max, double tmax, double TOL);

    wypiszF2(u0, dt, 0, b1,b2,c1,c2,u0,B,N,y,mi_max,tmax,TOL);






    return 0;
}


//wyliczamy iteracjami un wlasciwe
double P_un(double uprev, int mi_max, double TOL, double dt, double B, int N, double y)
{
    double alfa = B*N - y;
    double un = uprev;
    int iteracje = 0;

    double un_mi_prev = uprev;


    for(int mi = 0; mi < mi_max; mi++)
    {
        iteracje ++;

        double part1 = alfa*uprev - B*pow(uprev,2);
        double part2 = alfa*un_mi_prev - B*pow(un_mi_prev,2);

        un = uprev + (dt/2.) * (part1 + part2);

        

        if(fabs(un - un_mi_prev) < TOL)
        {
            break;
        }

        un_mi_prev = un;

    }


    printf("Iteracje Picard: %d\n", iteracje);

    return un;
}

double N_un(double uprev, int mi_max, double TOL, double dt, double B, int N, double y)
{
    double alfa = B*N - y;
    double un = uprev;
    int iteracje = 0;

    double un_mi_prev = uprev;


    for(int mi = 0; mi < mi_max; mi++)
    {
        iteracje ++;

        double part1 = alfa*uprev - B*pow(uprev,2);
        double part2 = alfa*un_mi_prev - B*pow(un_mi_prev,2);

        double part3 = un_mi_prev - uprev - (dt/2.) *(part1 + part2);
        double part4 = 1 - (dt/2.) * (alfa - 2*B*un_mi_prev);

        un = un_mi_prev - (part3 / part4);

        

        if(fabs(un - un_mi_prev) < TOL)
        {
            break;
        }

        un_mi_prev = un;

    }

    printf("Iteracje Newton: %d\n", iteracje);

    return un;
}

//f1(option,B,N,y,dt, &u0, TOL, mi_max)
double f1(int option, double B, int N, double y, double dt, double *u0, double TOL, int mi_max)
{
    double un;
    double uprev = *u0;

    double (*un_f)(double, int, double, double, double, int, double) = (option == 0) ? P_un : N_un;

    un = un_f(uprev, mi_max, TOL, dt, B,N,y);

    *u0 = un;                   

    return un;

}





void wypiszF(int option, double dt, double u0, double B, int N, double y, int mi_max, double tmax, double TOL)
{
    double t = 0;


    while(t < tmax)
    {
        printf("%g\t%g\n", t, f1(option,B,N,y,dt, &u0, TOL, mi_max));

        t += dt;
    }
}

//RK2

void wypiszF2(double uprev, double dt, double t, double b1, double b2, double c1, double c2, double u0, double B, int N, double y, int mi_max, double tmax, double TOL)
{
    double un;

    //f1(option,B,N,y,dt, &u0, TOL, mi_max)

    //prosze sie nie dziwic - nie zdazylam tutaj obliczyc juz, dalam 0, zeby nie bylo errora
    double u1 = 0;
    double u2 = 0;

    double part1 = b1 * f1(0, B, N, y, dt * c1, &u1, TOL, mi_max);
    double part2 = b2 * f1(0,B,N,y,dt * c2 ,&u2, TOL, mi_max);

    un = uprev + dt * (part1 + part2);


    double t1 = 0;

    while(t1 < tmax)
    {
        printf("%g\t%g\n", t1, un);

        t1 += dt;
    }



}