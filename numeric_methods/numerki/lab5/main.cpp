#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double Vb(int znak, int nr_pi, int b, double max,double delta);
void brzegowe(double **V, int nx, int ny, double xmax, double ymax,double delta);
void wypelnij(double** matrix,int x, int y, double val);
double count_S(int nx,int ny,double** V, double delta, int k);
void dense(double** V, int k, int nx, int ny);
void net(double** V, int nx, int ny, int k1, double delta, double TOL);
void print_matrix(double** matrix, int nx, int ny, int k, int it);

int main()
{
    double delta = 0.2;
    int nx = 128;
    int ny = 128;
    double xmax = delta*nx;
    double ymax = delta*ny;
    double TOL = 1e-8;

    double **V = new double *[nx+1];
    for (int i = 0; i < nx+1; i++) 
    {
        V[i] = new double[ny+1];
    }

    wypelnij(V,nx+1,ny+1,0);
    brzegowe(V,nx+1,ny+1,xmax,ymax, delta);

    int k = 16;
    //relaksacja
    net(V,nx,ny,k,delta,TOL);

    for(int i=0; i<nx+1; i++)
    {
        delete [] V[i];
    }

    return 0;
}

//warunki poczatkowe
double Vb(int znak, int nr_pi, int b, double max, double delta)
{
    return znak*sin(nr_pi*M_PI * b *delta / max);
}

void brzegowe(double **V, int nx, int ny, double xmax, double ymax, double delta)
{
    for(int i=0; i<nx; i++)
    {
        V[i][ny-1] = Vb(-1,2,i,xmax,delta);
        V[i][0] = Vb(1,2,i,xmax,delta);
    }

    for(int j=0; j<ny; j++)
    {
        V[0][j] = Vb(1,1,j,ymax,delta);
        V[nx-1][j] = Vb(1,1,j,ymax,delta);
    }
}

//wypelnia na poczatek macierz
void wypelnij(double** matrix,int x, int y, double val)
{
    for(int i=0; i<x; i++)
    {
        for(int j = 0; j<y; j++)
        {
            *(*(matrix + i) + j) = val;
        }
    }
}

//wylicxza sume kontrolna do stopu
double count_S(int nx,int ny,double** V, double delta, int k)
{
    double suma = 0;
    double part1;
    double part2;

    for(int i=0; i<nx; i+=k)
    {
        for(int j=0; j<ny; j+=k)
        {
            part1 = V[i+k][j] - V[i][j] + V[i+k][j+k] - V[i][j+k];
            part1 /= 2*k*delta;
            part2 = V[i][j+k] - V[i][j] + V[i+k][j+k] - V[i+k][j];
            part2 /= 2*k*delta;
            
            suma += pow(k*delta,2) * (pow(part1,2) + pow(part2,2))/2.; 
        }
    }

    return suma;
}

void dense(double** V, int k, int nx, int ny)
{
    int k2 = k/2;

    for(int i=0; i<nx; i+=k)
    {
        for(int j=0; j<ny; j+=k)
        {
            V[i+k2][j+k2] = (V[i][j] + V[i+k][j] + V[i][j+k] + V[i+k][j+k])/4.;
            //V[i+k][j+k2] = (V[i+k][j] + V[i+k][j+k])/2.;
            //V[i+k2][j+k] = (V[i][j+k] + V[i+k][j+k])/2.;
            if(j>0) V[i+k2][j] = (V[i][j] + V[i+k][j])/2.;
            if(i>0) V[i][j+k2] = (V[i][j] + V[i][j+k])/2.; 
        }
    }
}


void net(double** V, int nx, int ny, int k1, double delta, double TOL)
{
    double Sk;
    double Skprev = 1;
    int it =0;;
    double diff;

    for(int k=k1; k>=1; k/=2)
    {

        do{
            it++;

            for(int i=k; i<nx; i+=k)
            {
                for(int j=k; j<ny; j+=k)
                {
                    V[i][j] = (V[i+k][j] + V[i-k][j] + V[i][j+k] + V[i][j-k])/4.;
                }
            }

            Sk = count_S(nx,ny,V,delta,k);
            cout<<"k = "<<k<<" S = "<<Sk<<endl;
            diff = fabs((Sk - Skprev)/Skprev);
            Skprev = Sk;

        }while(diff >= TOL);
        

        if(k != 1)
        {
            dense(V,k,nx,ny);
        }

        print_matrix(V,nx,ny,k, it);
    }
}

void print_matrix(double** matrix, int nx, int ny, int k, int it)
{
    cout<<endl;
    cout<<endl;
    cout<<"******* k = "<<k<<"*******"<<endl;
    cout<<"******* it = "<<it<<"*******"<<endl;

    for(int i=0; i<nx; i++)
    {
        for(int j=0; j<ny; j++)
        {
            cout<<i<<"  "<<j<<"  "<<matrix[i][j]<<endl;
        }
    }
    cout<<endl;
    cout<<endl;
}