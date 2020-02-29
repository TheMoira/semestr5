#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include <string.h>

void fill_matrix_vec(gsl_matrix* A,gsl_matrix* B,gsl_vector* c,int N,
                int nx,int ny,double dt,double delta,
                int Ta,int Tb,int Tc,int Td,double kb,double kd);

void fill_vec_T(gsl_vector* t0,int N,int nx,int ny,int Ta,int Tc);

void algo_CN(gsl_matrix* A,gsl_matrix* B,gsl_vector* c,gsl_vector *t0,int N,
            int nx,int ny,int IT_MAX, double delta, gsl_permutation* p);

void result_to_file(int f, gsl_vector* t, int n, int nx, int ny, double delta);

int main()
{
    int nx = 40;
    int ny = 40;
    int N = (nx+1)*(ny+1);
    double delta = 1;
    double dt = 1;
    int Ta = 40;
    int Tb = 0;
    int Tc = 30;
    int Td = 0;

    double kb = 0.1;
    double kd = 0.6;
    int IT_MAX = 2000;

    gsl_matrix* A = gsl_matrix_calloc(N,N);
    gsl_matrix* B = gsl_matrix_calloc(N,N);
    gsl_vector* c = gsl_vector_calloc(N);

    fill_matrix_vec(A,B,c,N,nx,ny,dt,delta,Ta,Tb,Tc,Td,kb,kd);

    gsl_vector* t0 = gsl_vector_calloc(N);
    fill_vec_T(t0,N,nx,ny,Ta,Tc);

    gsl_permutation* p = gsl_permutation_calloc(N);
    int signum;
    gsl_linalg_LU_decomp(A, p, &signum);

    algo_CN(A,B,c,t0,N,nx,ny,IT_MAX,delta,p);

    gsl_matrix_free(A);
    gsl_matrix_free(B);
    gsl_vector_free(c);
    gsl_vector_free(t0);
    gsl_permutation_free(p);


    return 0;
}


void fill_matrix_vec(gsl_matrix* A,gsl_matrix* B,gsl_vector* c,int N,
                int nx,int ny,double dt,double delta,
                int Ta,int Tb,int Tc,int Td,double kb,double kd)
{
    for(int i=1; i<nx; i++)
    {
        for(int j=1; j<ny; j++)
        {
            int l = i + j*(nx+1);
            double value = dt/(2*delta*delta);

            gsl_matrix_set(A, l, l-1, value);
            gsl_matrix_set(A, l, l+1, value);
            gsl_matrix_set(A, l, l+nx+1, value);
            gsl_matrix_set(A, l, l-nx-1, value);

            double value2 = -2*dt/pow(delta,2) - 1;
            gsl_matrix_set(A, l, l, value2);

            value *= -1;
            value2 *= -1;
            value2 -= 2;    //-- daje +

            gsl_matrix_set(B, l, l-1, value);
            gsl_matrix_set(B, l, l+1, value);
            gsl_matrix_set(B, l, l+nx+1, value);
            gsl_matrix_set(B, l, l-nx-1, value);

            gsl_matrix_set(B, l, l, value2);
        }

        
    }

    for(int j=0; j<=ny; j++)
    {
        for(int i=0; i<=nx; i+=nx)
        {
            int l = i + j*(nx+1);
            gsl_matrix_set(A, l, l, 1);
            gsl_matrix_set(B, l, l, 1);
            gsl_vector_set(c, l, 0);
        }
    }

    for(int i=1; i<nx; i++)                     //(30)
    {
        int j= ny;
        int l = i + j*(nx+1);

        double value = -1./(kb*delta);
        gsl_matrix_set(A, l, l-nx-1, value);    //
        gsl_matrix_set(A, l, l, 1 - value);     //- - daje +
        gsl_vector_set(c, l, Tb);

        for(int j2=0; j2<=ny; j2++)
        {
            gsl_matrix_set(B, l, j2, 0);        //(35)
        }


    }

    for(int i=1; i<nx; i++)                     //(40)
    {
        int j=0;
        int l = i + j*(nx+1);

        double value = 1 + 1./(kd*delta);
        gsl_matrix_set(A, l, l, value); 
        gsl_matrix_set(A, l, l+nx+1, - value + 1);          //(43)
        gsl_vector_set(c, l, Td);

        for(int j2=0; j2<=ny; j2++)
        {
            gsl_matrix_set(B, l, j2, 0);        //(45)
        }
    }
}


void fill_vec_T(gsl_vector* t0,int N,int nx,int ny,int Ta,int Tc)
{
    for(int j=0; j<=ny; j++)
    {
        int i;

        i=0;
        int l = i + j*(nx+1);
        gsl_vector_set(t0, l, Ta);

        i=nx;
        l = i + j*(nx+1);
        gsl_vector_set(t0, l, Tc);
    }
}

void algo_CN(gsl_matrix* A,gsl_matrix* B,gsl_vector* c,gsl_vector *t0,int N,
            int nx,int ny,int IT_MAX, double delta, gsl_permutation* p)
{
    gsl_vector* d = gsl_vector_calloc(N);
    gsl_vector* t = gsl_vector_calloc(N);

    for(int it=0; it<=IT_MAX; it++)
    {
        gsl_vector_memcpy(t, t0);

        if(it == 100 || it == 200 || it == 500 || it == 1000 || it == 2000)
        {
            int f = it/100;
            result_to_file(f,t,N,nx,ny,delta);
        }



        d = gsl_vector_calloc(N);
        gsl_blas_dgemv(CblasNoTrans, 1, B, t, 0, d);

        gsl_blas_daxpy(1 , c, d);

        gsl_linalg_LU_solve(A, p, d, t);
        
        gsl_vector_memcpy(t0, t);
    }
}

void result_to_file(int f, gsl_vector* t, int n, int nx, int ny, double delta)
{
    char name1[7] = "T";
    char name2[9] = "Dyf";

    switch(f)
    {
        case 1:
            strcat(name1,"1.dat");
            strcat(name2,"1.dat");
            break;
        case 2:
            strcat(name1,"2.dat");
            strcat(name2,"2.dat");
            break;
        case 5:
            strcat(name1,"3.dat");
            strcat(name2,"3.dat");
            break;
        case 10:
            strcat(name1,"4.dat");
            strcat(name2,"4.dat");
            break;
        case 20:
            strcat(name1,"5.dat");
            strcat(name2,"5.dat");
            break;
        default:
            strcat(name1,"d.dat");
            strcat(name2,"d.dat");
            break;

    }


    FILE* tf = fopen(name1,"w");
    FILE* Df = fopen(name2,"w");

    gsl_vector* Dt = gsl_vector_calloc(n);

    for(int i=1; i<nx; i++)
    {
        for(int j=1; j<ny; j++)
        {
            int l = i+1 + j*(nx+1);
            double t1 = gsl_vector_get(t,l);
            l = i + j*(nx+1);
            double t2 = gsl_vector_get(t,l);
            l = i-1 + j*(nx+1);
            double t3 = gsl_vector_get(t,l);
            l = i + (j+1)*(nx+1);
            double t4 = gsl_vector_get(t,l);
            l = i + j*(nx+1);
            double t5 = gsl_vector_get(t,l);
            l = i + (j-1)*(nx+1);
            double t6 = gsl_vector_get(t,l);

            double value = (t1 -2*t2 +t3)/pow(delta,2) + (t4-2*t5+t6)/pow(delta,2);
            gsl_vector_set(Dt, l, value);
        }
    }

    for(int x=0; x<=nx; x++)
    {
        for(int y=0; y<=ny; y++)
        {
            int l = x + y*(nx+1);
            fprintf(tf, "%d\t%d\t%g\n", x, y, gsl_vector_get(t, l));
            fprintf(Df, "%d\t%d\t%g\n", x, y, gsl_vector_get(Dt, l));
        }
    }

    fclose(tf);
    fclose(Df);
}