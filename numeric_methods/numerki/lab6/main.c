#include "stdio.h"
#include "math.h"
#include "mgmres.h"
#include <stdlib.h>

//tworzenie wektorow

//pseudokod
void Macierz_rzadka(double* V, double* b, int* ia, int* ja, double* a, double eps1, double eps2,
int N, int nx, int ny, double v1, double v2, double v3, double v4, double delta, double ro1, double ro2);

//konwersje: i,j -> l / l -> i,j
int f_l(int i, int j, int nx);
int* f_index(int l, int nx);

//wypisywanie po uzciu pmgmres
void print(double* a, double *b, double delta, int N, int nx, FILE* f);
void print_v(double*V, int N, FILE* f);

//dodatkowe
double epsL(double eps1, double eps2, int l, int nx);
double elem_macierz(int l, int nx, double eps1, double eps2, double delta, int wybor);

//ro
double** ro1_tab(int nx, int ny, double xmax, double ymax,double delta);
double** ro2_tab(int nx, int ny, double xmax, double ymax, double delta);

double ro_part(int param, double val, double sigma, double max, double delta);

double** prepare_matrix(int x, int y);
void wyzeruj(double* tab, int N)
{
    for(int i=0; i<N; i++)
    {
        tab[i]=0;
    }
}

void wyzeruj2(int* tab, int N)
{
    for(int i=0; i<N; i++)
    {
        tab[i]=0;
    }
}


int main()
{
    double delta = 0.1;
    int nx = 4;
    int ny = 4;
    double eps1 = 1;
    double eps2 = 1;
    double V1, V2, V3, V4;
    V1 = V2 = 10;
    V3 = V4 = -10;
    double ro1 = 0;
    double ro2 = 0;
    int N = (nx+1)*(ny+1);

    double* a = calloc(5*N, sizeof(double));
    int* ja = calloc(5*N, sizeof(int));
    int* ia = calloc(N+1, sizeof(int));
    for(int i=0; i<=N; i++)
    {
        ia[i] = -1;
    }
    double* b = calloc(N, sizeof(double));
    double* V = calloc(N, sizeof(double));
    
    
    FILE *f1 = fopen("plik1.txt", "w+");
    FILE *fa = fopen("mapaA.txt", "w+");
    FILE *fb = fopen("mapaB.txt", "w+");
    FILE *fc = fopen("mapaC.txt", "w+");
    

    Macierz_rzadka(V,b,ia,ja,a,eps1,eps2,N,nx,ny,V1,V2,V3,V4,delta, ro1, ro2);
    
    int itr_max = 500;
    int tol_abs = 1e-8;
    int tol_rel = 1e-8;
    //printf("%d\n",ia[N]);
    pmgmres_ilu_cr(N, ia[N] , ia, ja, a, V, b, itr_max , 500, tol_abs, tol_rel );

    print(a,b,delta,N,nx,f1);

    //zadanie 5
    
    //a
    nx = 50;
    ny = 50;
    N = (nx+1)*(ny+1);
    wyzeruj(V,N);
    wyzeruj(b,N);
    wyzeruj2(ja,5*N);
    wyzeruj(a,5*N);
        for(int i=0; i<=N; i++)
    {
        ia[i] = -1;
    }

    Macierz_rzadka(V,b,ia,ja,a,eps1,eps2,N,nx,ny,V1,V2,V3,V4,delta, ro1, ro2);
    pmgmres_ilu_cr(N, ia[N] , ia, ja, a, V, b, itr_max , 500, tol_abs, tol_rel );
    print_v(V,N,fa);

    //b
    nx = 100;
    ny = 100;

    wyzeruj(V,N);
    wyzeruj(b,N);
    wyzeruj2(ja,5*N);
    wyzeruj(a,5*N);
    N = (nx+1)*(ny+1);
        for(int i=0; i<=N; i++)
    {
        ia[i] = -1;
    }

    Macierz_rzadka(V,b,ia,ja,a,eps1,eps2,N,nx,ny,V1,V2,V3,V4,delta, ro1, ro2);
    pmgmres_ilu_cr(N, ia[N] , ia, ja, a, V, b, itr_max , 500, tol_abs, tol_rel );
    print_v(V,N,fb);

    //c
    nx = 200;
    ny = 200;

    wyzeruj(V,N);
    wyzeruj(b,N);
    wyzeruj2(ja,5*N);
    wyzeruj(a,5*N);
    N = (nx+1)*(ny+1);
        for(int i=0; i<=N; i++)
    {
        ia[i] = -1;
    }

    Macierz_rzadka(V,b,ia,ja,a,eps1,eps2,N,nx,ny,V1,V2,V3,V4,delta, ro1, ro2);
    pmgmres_ilu_cr(N, ia[N] , ia, ja, a, V, b, itr_max , 500, tol_abs, tol_rel );
    print_v(V,N,fc);


    //zadanie 6
    nx = 100;
    ny = 100;

    V1=V2=V3=V4=0;
    double xmax = delta*nx;
    double ymax = delta*ny;
    double sigma = xmax/10.;

    double** tab_ro1 = ro1_tab(nx+1,ny+1,xmax,ymax,delta);
    double** tab_ro2 = ro2_tab(nx+1,ny+1,xmax,ymax,delta);


    //koniec
    fclose(f1);
    fclose(fa);
    fclose(fb);
    fclose(fc);

    free(a);
    free(ia);
    free(ja);
    free(b);
    free(V);
    
    return 0;
}

int f_l(int i, int j, int nx)
{
    return i + j * (nx + 1);
}

int* f_index(int l, int nx)
{
    int j = floor(l/(nx + 1));
    int i = l - j * (nx + 1);
    int* index = calloc(2,sizeof(int));
    index[0] = i;
    index[1] = j;

    return index;
}

void Macierz_rzadka(double* V, double* b, int* ia, int* ja, double* a, double eps1, double eps2,
int N, int nx, int ny, double v1, double v2, double v3, double v4, double delta, double ro1, double ro2)
{
    int k = -1;
    int i,j;
    int* index;

    for(int l=0; l<N; l++)
    {
        int brzeg = 0;
        double vb = 0;

        index = f_index(l,nx);
        i = index[0];
        j = index[1];

        if(i==0)
        {
            brzeg = 1;
            vb = v1;
        }

        if(j==ny)
        {
            brzeg = 1;
            vb = v2;
        }

        if(i==nx)
        {
            brzeg = 1;
            vb = v3;
        }

        if(j==0)
        {
            brzeg = 1;
            vb = v4;
        }


        if(brzeg == 1)
        {
            b[l] = vb;
        }
        else
        {
            b[l] = -(ro1+ro2);
        }

        ia[l] = -1;

        if((l-nx-1) >= 0 && brzeg==0)
        {
            k++;
            if(ia[l]<0)
            {
                ia[l] = k;
            }
            a[k] = elem_macierz(l, nx, eps1, eps2, delta, 1);
            ja[k] = l - nx - 1;
        }

        if(l-1>=0 && brzeg==0)
        {
            k++;
            if(ia[l]<0)
            {
                ia[l] = k;
            }
            a[k] = elem_macierz(l, nx, eps1, eps2, delta, 2);
            ja[k] = l - 1;
        }

        k++;
        if(ia[l]<0)
        {
            ia[l] = k;
        }

        if(brzeg==0)
        {
            a[k] = elem_macierz(l, nx, eps1, eps2, delta, 3);
        }
        else
        {
            a[k] = 1;
        }
        ja[k] = l;

        if(l<N && brzeg==0)
        {
            k++;
            a[k] = elem_macierz(l, nx, eps1, eps2, delta, 4);
            ja[k] = l+1;
        }

        if(l<(N-nx-1) && brzeg==0)
        {
            k++;
            a[k] = elem_macierz(l, nx, eps1, eps2, delta, 5);
            ja[k] = l + nx + 1;
        }

    }

    int nz_num = k+1;
    ia[N] = nz_num;


    free(index);
}


double epsL(double eps1, double eps2, int l, int nx)
{
    int* ind = f_index(l,nx);
    int i=ind[0];
    free(ind);
    return i <= (nx/2) ? eps1 : eps2;
}

double elem_macierz(int l, int nx, double eps1, double eps2, double delta, int wybor)
{
    double epsl = epsL(eps1, eps2, l, nx);
    double epsl1 = epsL(eps1, eps2, l+1, nx);
    double epsl2 = epsL(eps1, eps2, l + nx + 1, nx);

    double wynik;
    switch(wybor)
    {
        case 1:
            wynik = epsl/pow(delta,2);
            break;
        case 2:
            wynik = epsl/pow(delta,2);
            break;
        case 3:
            wynik = -(2*epsl + epsl1 + epsl2)/pow(delta,2);
            break;
        case 4:
            wynik = epsl1/pow(delta,2);
            break;
        case 5:
            wynik = epsl2/pow(delta,2);
            break;
        default:
            wynik = -1006766;
            break;
    }

    return wynik;
}


void print(double* a, double *b, double delta, int N, int nx, FILE* f)
{
    fprintf(f,"k\t\ta[k]\n");
    for(int k=0; k<5*N; k++)
    {
        fprintf(f,"%d\t\t%g\n",k,a[k]);
    }
    
    fprintf(f,"l\ti\tj\tb[l]\n");
    for(int l=0; l<25; l++)
    {
        int* ind = f_index(l,nx);
        int i = ind[0];
        int j = ind[1];

        fprintf(f,"%d\t%d\t%d\t%g\n",l,i,j,b[l]);
    }
    

}

void print_v(double*V, int N, FILE* f)
{
    for(int i=0; i<N; i++)
    {
        fprintf(f,"%d\t%g\n", i, V[i]);
    }
}

double** ro1_tab(int nx, int ny, double xmax, double ymax, double delta)
{
    double **tab = prepare_matrix(nx+1,ny+1);
    double ro1;
    double ro2;
    double sigmax = 0.1*xmax;
    double sigmay = 0.1*ymax;

    for(int i=0; i<nx; i++)
    {
        for(int j=0; j<ny; j++)
        {
            ro1 = ro_part(i,0.35,sigmax,xmax,delta);
            ro2 = ro_part(j,0.5,sigmay,ymax,delta);
            tab[i][j] = exp(ro1 + ro2);
        }
    }

    return tab;
}

double** ro2_tab(int nx, int ny, double xmax, double ymax, double delta)
{
    double **tab = prepare_matrix(nx+1,ny+1);
    double ro1;
    double ro2;
    double sigmax = 0.1*xmax;
    double sigmay = 0.1*ymax;

    for(int i=0; i<nx; i++)
    {
        for(int j=0; j<ny; j++)
        {
            ro1 = ro_part(i,0.65,sigmax,xmax,delta);
            ro2 = ro_part(j,0.5,sigmay,ymax,delta);
            tab[i][j] = -exp(ro1 + ro2);
        }
    }

    return tab;
}

double ro_part(int param, double val, double sigma, double max, double delta)
{
    return -pow(param*delta-val*max,2)/pow(sigma,2);
}

double** prepare_matrix(int x, int y)
{
    double **tab = malloc(x * sizeof(double*));

    for(int i=0; i<x; i++)
    {
        tab[i] = malloc(y*sizeof(double));
    }

    return tab;
}