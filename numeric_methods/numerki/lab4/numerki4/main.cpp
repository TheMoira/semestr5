#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double** prepare_matrix(int x, int y);

void wypelnij(double** matrix,int x, int y, double val);
void rel_glob(int nx, int ny, double V1, double V2, double wg, double e, double delta, double** ro);
void loc_glob(int nx, int ny, double V1, double V2, double wg, double e, double delta, double** ro);

double** ro1_tab(int nx, int ny, double xmax, double ymax,double delta);
double** ro2_tab(int nx, int ny, double xmax, double ymax, double delta);

double ro_part(int param, double val, double sigma, double max, double delta);
double count_S(int nx,int ny,double** Vs, double delta,double** ro);

void print_matrix(double** matrix, int nx, int ny);


int main()
{
    double e = 1;
    double delta = 0.1;
    int nx = 150;
    int ny = 100;
    double V1 = 10;
    double V2 = 0;
    double xmax = delta*nx;
    double ymax = delta*ny;

    double** ro1 = ro1_tab(nx+1,ny+1,xmax,ymax,delta);
    double** ro2 = ro2_tab(nx+1,ny+1,xmax,ymax,delta);
    double** ro = prepare_matrix(nx,ny);

    for(int i=0; i<nx; i++)
    {
        for(int j=0; j<ny; j++)
        {
            ro[i][j] = ro1[i][j] + ro2[i][j];
        }
    }
    
    double TOL = 1e-8;
    double wg = 0.6;
    cout<<"globalna: wg = "<<wg<<endl;
    rel_glob(nx,ny,V1,V2,wg,e,delta,ro);

     wg = 1;
    cout<<"globalna: wg = "<<wg<<endl;
    rel_glob(nx,ny,V1,V2,wg,e,delta,ro);

    double wl = 1.0;
    cout<<"globalna: wl = "<<wl<<endl;
    loc_glob(nx,ny,V1,V2,wl,e,delta,ro);

    wl = 1.4;
    cout<<"globalna: wl = "<<wl<<endl;
    loc_glob(nx,ny,V1,V2,wl,e,delta,ro);

    wl = 1.8;
    cout<<"globalna: wl = "<<wl<<endl;
    loc_glob(nx,ny,V1,V2,wl,e,delta,ro);

    wl = 1.9;
    cout<<"globalna: wl = "<<wl<<endl;
    loc_glob(nx,ny,V1,V2,wl,e,delta,ro); 

    for(int i=0; i<nx+1; i++)
    {
        delete [] ro[i];
    }

    return 0;
}


double** prepare_matrix(int x, int y)
{
    double **tab = new double *[x];
    for (int i = 0; i < x; i++) 
    {
        tab[i] = new double[y];
    }

    return tab;
}

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


void rel_glob(int nx, int ny, double V1, double V2, double wg, double e, double delta, double** ro)
{
    double TOL = 1e-8;
    double** Vn = prepare_matrix(nx+1,ny+1);
    double** Vs = prepare_matrix(nx+1,ny+1);

    wypelnij(Vn, nx+1,ny+1, 0);
    wypelnij(Vs, nx+1,ny+1, 0);

    double Sprev = 1;
    double S;
    double war;

    for(int i=0; i<nx; i++)
    {
        Vn[i][0] = V2;
        Vs[i][0] = V2;
        Vn[i][ny-1] = V1;
        Vs[i][ny-1] = V1;
    }

    int k = 0;

    do{
        k++;
        //wypełnianie (9)
        for(int i=1; i<nx; i++)
        {
            for(int j=1; j<ny; j++)
            {
                Vn[i][j] = (Vs[i+1][j] + Vs[i-1][j] + Vs[i][j-1] + delta*delta*ro[i][j])/4.;
            }

        }



        //wypelniamy pozostale Vn0,j oraz Vnnx,j (10),(11)
        for(int j = 0; j<ny; j++)
        {
            Vn[0][j] = Vn[1][j];
            Vn[nx][j] = Vn[nx-1][j];
        }


        //mieszamy Vs (12)

        for(int i=0; i<nx; i++)
        {
            for(int j=0; j<ny; j++)
            {
                Vs[i][j] = (1 - wg) * Vs[i][j] + wg * Vn[i][j];
            }
        }

        S = count_S(nx,ny,Vs,delta,ro);
        war = fabs((S - Sprev)/Sprev);
        Sprev = S;

    }while(war >= TOL);

    print_matrix(Vs, nx, ny);
    cout<<"k = "<<k<<endl;


}


void loc_glob(int nx, int ny, double V1, double V2, double wl, double e, double delta, double** ro)
{
    double TOL = 1e-8;
    double** V = prepare_matrix(nx+1,ny+1);

    wypelnij(V, nx+1,ny+1, 0);

    double Sprev = 1;
    double S;
    double war;

    for(int i=0; i<nx; i++)
    {
        V[i][0] = V2;
        V[i][ny-1] = V1;
    }

    int k = 0;

    do{
        k++;
        //wypełnianie (9)
        for(int i=1; i<nx; i++)
        {
            for(int j=1; j<ny; j++)
            {
                V[i][j] = (1-wl) * V[i][j] + wl*(V[i+1][j] + V[i-1][j] + V[i][j+1] + V[i][j-1] + delta*delta*ro[i][j]/e)/4.;
            }
        }


        //wypelniamy pozostale Vn0,j oraz Vnnx,j (10),(11)
        for(int j = 0; j<ny; j++)
        {
            V[0][j] = V[1][j];
            V[nx-1][j] = V[nx-2][j];
        }


        S = count_S(nx,ny,V,delta,ro);
        war = (S - Sprev)/Sprev;
        Sprev = S;

    }while(war > TOL);

    print_matrix(V, nx, ny);
    cout<<"k = "<<k<<endl;

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

double count_S(int nx,int ny,double** V, double delta,double** ro)
{
    double suma = 0;

    for(int i=0; i<nx-1; i++)
    {
        for(int j=0; j<ny-1; j++)
        {
            suma += pow(delta,2) * (pow((V[i+1][j] - V[i][j])/delta,2)/2. + pow((V[i+1][j+1] - V[i][j])/delta,2)/2. - ro[i][j]*V[i][j]);
        }
    }

    return suma;
}

void print_matrix(double** matrix, int nx, int ny)
{
    for(int i=0; i<nx; i++)
    {
        for(int j=0; j<ny; j++)
        {
            cout<<i<<"  "<<j<<"  "<<matrix[i][j]<<endl;
        }
    }
}