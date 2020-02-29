#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

//plot "energia1.dat"
//splot "nachylenie1.dat"

void algo(int nx, int nt, double delta, double dt, double beta, double alfa, double xa, double sigma, double xf, FILE* f1, FILE* f2);
double aF(double t, double nt, double x, double xf, double dt);
void schemat(double* u0, double* u, double* v, double* a, int nx, double dt,double delta, double beta, double alfa, double t, int nt, double xf);
double ener(double delta, double* u, int nx, double* v);
void WP(double* u, double xa, double sigma, int nx, double delta);


int main()
{

    int nx = 150;
    int nt = 1000;
    double delta = 0.1;
    double dt = 0.05;
    double xa = 7.5;
    double sigma = 0.5;

    FILE* f1a = fopen("energia1.dat", "w+");
    FILE* f2a = fopen("nachylenie1.dat", "w+");

    FILE* f1b = fopen("energia2.dat", "w+");
    FILE* f2b = fopen("nachylenie2.dat", "w+");

    FILE* f1c = fopen("energia3.dat", "w+");
    FILE* f2c = fopen("nachylenie3.dat", "w+");

    FILE* f1d = fopen("energia4.dat", "w+");
    FILE* f2d = fopen("nachylenie4.dat", "w+");

    double xf = 2.5;


    double alfa = 0;
    double beta = 0;
    algo(nx,nt,delta,dt,beta,alfa,xa,sigma,xf,f1a,f2a);


    beta = 0.1;
    algo(nx,nt,delta,dt,beta,alfa,xa,sigma,xf,f1b,f2b);


    beta = 1;
    algo(nx,nt,delta,dt,beta,alfa,xa,sigma,xf,f1c,f2c);

    alfa = 1;
    algo(nx,nt,delta,dt,beta,alfa,xa,sigma,xf,f1d,f2d);


    fclose(f1a);
    fclose(f2a);
    fclose(f1b);
    fclose(f2b);
    fclose(f1c);
    fclose(f2c);
    fclose(f1d);
    fclose(f2d);


    return 0;
}


void algo(int nx, int nt, double delta, double dt, double beta, double alfa, double xa, double sigma, double xf, FILE* f1, FILE* f2)
{
    double* u0 = calloc(nx+1, sizeof(double));
    double* u = calloc(nx+1, sizeof(double));
    double* v = calloc(nx+1, sizeof(double));
    double* vp = calloc(nx+1, sizeof(double));
    double* a = calloc(nx+1, sizeof(double));

    double E;


    if(alfa == 0)
    {
        WP(u,xa,sigma,nx, delta);
    }

    memcpy(u0, u, sizeof(double)*(nx+1));

    schemat(u0,u,v,a,nx,dt,delta,beta,alfa,0,nt,xf);


    for(int n=1; n<=nt; n++)
    {
        for(int i=1; i<nx; i++)
        {
            vp[i] = v[i] + dt*a[i]/2.;
        }

        memcpy(u0, u, sizeof(double)*(nx+1));

        for(int i=1; i<nx; i++)
        {
            u[i] += dt*vp[i];
        }

        schemat(u0,u,v,a,nx,dt,delta,beta,alfa,n*dt,nt,xf);

        for(int i=1; i<nx; i++)
        {
            v[i] = vp[i] + dt*a[i]/2.;
        }

        E = ener(delta,u,nx,v);

        fprintf(f1,"%g\t%g\n",n*dt,E);
        
        for(int i=0; i<=nx; i++)
        {
            fprintf(f2,"%g\t%g\t%g\n",dt*n, delta*i,u[i]);
        }

        fprintf(f2,"\n");

    }

    free(u0);
    free(u);
    free(a);
    free(v);
    free(vp);

}

double aF(double t, double nt, double x, double xf, double dt)
{
    double temp = (x==xf) ? 1 : 0;

    return cos(50*t/(nt*dt)) * temp;

}


void schemat(double* u0, double* u, double* v, double* a, int nx, double dt,double delta, double beta, double alfa, double t, int nt, double xf)
{
    double part1;
    double part2;

    //bez brzegowych
    for(int i=1; i<nx; i++)
    {
        part1 = u[i+1] - 2*u[i] + u[i-1];
        part2 = beta * (u[i] - u0[i]);

        a[i] = part1/pow(delta,2) - part2/dt + alfa * aF(t,nt,i*delta,xf,dt);
    }
}

double ener(double delta, double* u, int nx, double* v)
{
    double suma = 0;
    double part1 = pow((u[1] - u[0])/delta,2) + pow((u[nx] - u[nx-1])/delta,2);

    for(int i=1; i<nx; i++)
    {
        suma += pow(v[i],2) + pow((u[i+1] - u[i-1])/(2*delta),2);
    }

    return delta*0.25*part1 + delta*0.5*suma;
}

void WP(double* u, double xa, double sigma, int nx, double delta)
{
    for(int i=1; i<nx; i++)
    {
        u[i] = exp(-pow(delta*i - xa,2)/(2*pow(sigma,2)));
    }
}