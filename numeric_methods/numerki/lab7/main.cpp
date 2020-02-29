#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "utils.h"
#define IT_MAX 20000

using namespace std;

double Qout(double Qin, int j1, int ny, double delta);
void del(double** matrix, int rows, int cols);
void WBu(double** U, int j1, int i1, int nx, int ny, double Qin, double delta, double mi);
void WBc(double** C, double** U, int j1, int i1, int nx, int ny, double Qin, double delta, double mi);

void NS(double** U, double** C, int j1, int i1, int nx, int ny, double delta, double mi, double ro, double Qin);
double oblicz_U(double** U, double** C, int i, int j, double delta);        //wzor 8
double oblicz_C(double** U, double** C, int i, int j, double delta, int om, double ro, double mi);         //wzor 9
bool brzeg(int i,int j, int nx, int ny, int i1, int j1);   //spr czy sa brzegami
double count_err(double** C, double** U, int j1, int nx, double delta);
void brzegi_A_F_C(double** U, double** C, int j1, int i1, int nx, int ny, double Qin, double delta, double mi);
double uxy(double** U, int i, int j, double delta,int nx, int ny, int i1, int j1);
double vxy(double** U, int i, int j, double delta,int nx, int ny, int i1, int j1);
void print_M(double** U, double** C,int i1, int j1, int nx, int ny, double delta, FILE* f);
template<typename T>
T** prepare_matrix(int rows, int cols);





int main()
{
    double delta = 0.01;
    double ro = 1;
    double mi = 1;
    int nx = 200;
    int ny = 90;
    int i1 = 50;
    int j1 = 55;

    double Qin;

    FILE* f1 = fopen("wyniki1.txt", "w");
    FILE* f2 = fopen("wyniki2.txt", "w");
    FILE* f3 = fopen("wyniki3.txt", "w");
    
    

    double** U = prepare_matrix<double>(nx+1,ny+1);
    double** C = prepare_matrix<double>(nx+1,ny+1);

    for(int i=0; i<=nx; i++)
    {
        for(int j=0; j<=ny; j++)
        {
            U[i][j] = 0;
            C[i][j] = 0;
        }
    }

    //Qin = -1000
    Qin = -1000;
    NS(U, C, j1, i1, nx, ny, delta,mi, ro, Qin);

    print_M(U, C,i1,j1, nx,  ny, delta, f1);

    //Qin = -4000
    Qin = -4000;
    for(int i=0; i<=nx; i++)
    {
        for(int j=0; j<=ny; j++)
        {
            U[i][j] = 0;
            C[i][j] = 0;
        }
    }
    NS(U, C, j1, i1, nx, ny, delta,mi, ro, Qin);

    print_M(U, C,i1,j1, nx,  ny, delta, f1);

    //Qin = 4000
    Qin = 4000;
    for(int i=0; i<=nx; i++)
    {
        for(int j=0; j<=ny; j++)
        {
            U[i][j] = 0;
            C[i][j] = 0;
        }
    }
    NS(U, C, j1, i1, nx, ny, delta,mi, ro, Qin);

    print_M(U, C,i1,j1, nx,  ny, delta, f1);


    del(U,nx+1, ny+1);
    del(C,nx+1, ny+1);

    fclose(f1);
    fclose(f2);
    fclose(f3);

    return 0;
}


double Qout(double Qin, int j1, int ny, double delta)
{
    double yn = delta * ny;
    double y1 = delta *j1;

    return Qin * (pow(yn,3) - pow(y1,3) - 3 * y1*pow(yn,2) + 3*pow(y1,2)*yn)/pow(yn,3);
}

template<typename T>
T** prepare_matrix(int rows, int cols)
{
    T** matrix = new T*[rows];
    for(int i=0; i<rows; i++)
    {
        matrix[i] = new T[cols];
        // for(int j=0; j<cols; j++)
        // {
        //     matrix[i][j] = T(0);
        // }
    }

    return matrix;

}

void del(double** matrix, int rows, int cols)
{
    for(int i=0; i<rows; i++)
    {
        delete [] matrix[i];
    }
}


void WBu(double** U, int j1, int i1, int nx, int ny, double Qin, double delta, double mi)
{
    for(int i=1; i<nx; i++)
    {
        U[i][ny] = U[0][ny];
        if(i>=i1) U[i][0] = U[0][j1];
        if(i<=i1) U[i][j1] = U[0][j1];
    }

    for(int j=1; j<=j1; j++)
    {
        U[i1][j] = U[0][j1];
    }

}

void WBc(double** C, double** U, int j1, int i1, int nx, int ny, double Qin, double delta, double mi)
{
    for(int i=0; i<nx; i++)
    {
        C[i][ny] = 2. * (U[i][ny-1] - U[i][ny])/pow(delta,2);
        C[i][0] = 2. * (U[i][ny-1] - U[i][ny])/pow(delta,2);
        
        if(i<=i1) C[i][j1] = 2. * (U[i][j1+1] - U[i][j1])/pow(delta,2);
    }

    for(int j=0; j<j1; j++)
    {
        C[i1][j] = 2. * (U[i1+1][j] - U[i1][j])/pow(delta,2);
    }

    C[i1][j1] = (C[i1-1][j1] + C[i1][j1-1])/2.;

}

double count_err(double** C, double** U, int j1, int nx, double delta)
{
    double sum = 0;

    for(int i=1; i<nx; i++)
    {
        sum += U[i+1][j1+2] + U[i-1][j1+2] + U[i][j1+3] + U[i][j1] - 4*U[i][j1+2] - pow(delta,2)*C[i][j1+2];
    }

    return sum;
}

void NS(double** U, double** C, int j1, int i1, int nx, int ny, double delta, double mi, double ro, double Qin)
{
    int om = 1;
    brzegi_A_F_C(U,C,j1,i1,nx,ny,Qin,delta,mi);

    WBu(U,j1,i1,nx,ny,Qin,delta,mi);
    double err;

    for(int it=1; it<=IT_MAX; it++)
    {
        if(it<2000)
        {
            om = 0;
        }

        for(int i=1; i<nx; i++)
        {
            for(int j=1; j<ny; j++)
            {
                if(!brzeg(i,j,nx,ny,i1,j1))     //napisac fun spr czy to nie brzegowe
                {
                    U[i][j] = oblicz_U(U,C,i,j,delta);
                    C[i][j] = oblicz_C(U,C,i,j,delta,om,ro,mi);
                }
            }
        }
        
        WBc(U,C,j1,i1,nx,ny,Qin,delta,mi);
        if(it%1000 == 1)
        {
            err = fabs(count_err(C,U,j1,nx,delta));
            cout<<err<<endl;
        }
    }


}

bool brzeg(int i,int j, int nx, int ny, int i1, int j1)
{
    if(i==nx || j==ny)
    {
        return true;
    }
    else if(i<=i1 && j<=j1)
    {
        return true;
    }  
    
    return false;
}

void brzegi_A_F_C(double** U, double** C, int j1, int i1, int nx, int ny, double Qin, double delta, double mi)
{
    for(int j=0; j<=ny; j++)
    {
        double Qwy = Qout(Qin, j, ny, delta);
        double y = delta*j;
        if(j>=j1) U[0][j] = (1./(2*mi)) * Qin * ((pow(y,3)/3.) - (pow(y,2)/2.) * (delta*j1 + delta*ny) + y*delta*j1*delta*ny);


        U[nx][j] = Qwy * (1./(2*mi)) * ((pow(y,3)/3.) - (pow(y,2)/2.) * delta*ny);
        U[nx][j] += Qin * pow(delta*j1,2) * (-delta*j1 + 3 * delta*ny)/(12*mi);
    
        if(j>=j1) C[0][j] = Qin * (2*y - delta*j1 - delta*ny)/(2*mi);
        
        C[nx][j] = Qwy * (2*y - delta*ny)/(2*mi);
    }

}

double oblicz_U(double** U, double** C, int i, int j, double delta)
{
    return (U[i+1][j] + U[i-1][j] + U[i][j+1] + U[i][j-1] - pow(delta,2)*C[i][j])/4.;
}

double oblicz_C(double** U, double** C, int i, int j, double delta, int om, double ro, double mi)
{
    return (C[i+1][j] + U[i-1][j] + U[i][j+1] + U[i][j-1])/4. - double(om) * ro * ((U[i][j+1] - U[i][j-1])*(C[i+1][j] - C[i-1][j]) - (U[i+1][j] - U[i-1][j])* (C[i][j+1] - C[i][j-1]))/(16.*mi);
}

double uxy(double** U, int i, int j, double delta, int nx, int ny, int i1, int j1)
{
    if(brzeg(i,j,nx,ny, i1, j1))
    {
        return 0;
    }
    return (U[i][j+1] - U[i][j-1])/(delta*2.);
}

double vxy(double** U, int i, int j, double delta, int nx, int ny, int i1, int j1)
{
    if(brzeg(i,j,nx,ny, i1, j1))
    {
        return 0;
    }
    
    return (U[i+1][j] - U[i-1][j])/(delta*2.);
}


void print_M(double** U, double** C,int i1, int j1, int nx, int ny, double delta, FILE* f)
{
    for(int i=0; i<=nx; i++)
    {
        for(int j=0; j<=ny; j++)
        {
            if(i<i1 && j<j1)
            {
                fprintf(f,"%g\t%g\t%g\t%g\n",U[i1][j1],C[i1][j1],uxy(U,i1,j1,delta,nx,ny, i1, j1),vxy(U,i1,j1,delta,nx,ny,i1, j1));
            }
            else
            {
                fprintf(f,"%g\t%g\t%g\t%g\n",U[i][j],C[i][j],uxy(U,i,j,delta,nx,ny,i1, j1),vxy(U,i,j,delta,nx,ny,i1, j1));
            }
        }
    }
}