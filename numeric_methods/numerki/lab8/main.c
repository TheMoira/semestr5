#include "stdio.h"
#include "stdlib.h"
#include "math.h"

void print(float** tab, int nx, int ny);
float** get_ready(int nx, int ny);
void delete_matrix(float** tab, int nx);

void WB(float** v, int nx, int ny);
void fill_vs(float** str, float** vx, float** vy, int nx, int ny, float delta, int i1, int i2, int j1);
float vm(float** vx, float** vy, int nx, int ny);

void AD(FILE* output, float** str, int nx, int ny, int i1, int i2, int j1, float D, float delta, 
float** vx, float** vy, float xa, float ya, float sigma);

float** prepare_u0(int nx, int ny, float xa, float ya, float sigma, float delta);
void copy_matrix(float** to, float** from, int nx, int ny);

float CN(float** u0, float** u1, float delta, float D, float dt, float** vx, float** vy, int i, int j, int left, int right);
int zastawka(int i, int j, int i1, int i2, int j1);


float xsr(float** u, int nx, int ny, float delta);
float c(float** u, int nx, int ny, float delta);

int main()
{
    int nx = 400;
    int ny = 90;
    int i1 = 200;
    int i2 = 210;
    int j1 = 50;
    float delta = 0.01;
    float sigma = 10*delta;
    float xa = 0.45;
    float ya = 0.45;

    FILE* data = fopen("psi.dat", "r");
    FILE* output = fopen("out.txt", "w");
    FILE* output2 = fopen("out2.txt", "w");
    int temp;

    //str - fukcja strumienia
    float** str = calloc(nx+1, sizeof(float*));
    for(int i=0; i<=nx; i++)
    {
        str[i] = calloc(ny+1,sizeof(float));
        for(int j=0; j<=ny; j++)
        {
            fscanf(data, "%d%d%g\n", &temp, &temp, &(str[i][j]));
        }
    }

    float** vx = get_ready(nx,ny);
    float** vy = get_ready(nx,ny);

    float D;

    D = 0;
    AD(output, str, nx, ny, i1, i2, j1, D,delta, vx, vy, xa,ya,sigma);

    D = 0.1;
    AD(output2, str, nx, ny, i1, i2, j1, D,delta, vx, vy, xa,ya,sigma);


    delete_matrix(vx,nx);
    delete_matrix(vy,nx);
    

    fclose(data);
    fclose(output);
    fclose(output2);

    return 0;
}


void print(float** tab, int nx, int ny)
{
    for(int i=0; i<=nx; i++)
    {
        for(int j=0; j<=ny; j++)
        {
            printf("%d\t%d\t%g\n", i,j,tab[i][j]);
        }
    }
}


float** get_ready(int nx, int ny)
{
    float** tab = calloc(nx+1, sizeof(float*));
    for(int i=0; i<=nx; i++)
    {
        tab[i] = calloc(ny+1,sizeof(float));
    }

    return tab;
}


void delete_matrix(float** tab, int nx)
{
    for(int i=0; i<=nx; i++)
    {
        free(tab[i]);
    }
}


void WB(float** v, int nx, int ny)
{
    for(int j=0; j<ny; j++)
    {
        //v[-1][j] = v[nx][j]
        v[0][j] = v[nx][j];

        //v[nx+1][j] = v[0][j]
        v[nx+2][j] = v[1][j];
    }
}

void fill_vs(float** str, float** vx, float** vy, int nx, int ny, float delta, int i1, int i2, int j1)
{
    for(int i=1; i<nx; i++)
    {
        for(int j=1; j<ny; j++)
        {
            if(i>=i1 && i<=i2 && j<=j1)
            {
                vx[i][j] = 0;
                vy[i][j] = 0;
            }
            else
            {
                vx[i][j] = (str[i][j+1] - str[i][j-1])/(2.*delta);
                vy[i][j] = (-str[i+1][j] + str[i-1][j])/(2.*delta);
            }
        }
    }

    for(int i=0; i<=nx; i++)
    {

    }

    for(int j=0; j<=ny; j++)
    {
        vx[0][j] = vx[1][j];
        vx[nx][j] = vx[nx-1][j];
    }
}

float vm(float** vx, float** vy, int nx, int ny)
{
    float max = 0;
    float temp;

    for(int i=0; i<=nx; i++)
    {
        for(int j=0; j<=ny; j++)
        {
            temp = sqrt(pow(vx[i][j],2) + pow(vy[i][j],2));
            if(temp>max)
            {
                max = temp;
            }
        }
    }

    return max;
}


void AD(FILE* output, float** str, int nx, int ny, int i1, int i2, int j1, float D, float delta, 
float** vx, float** vy, float xa, float ya, float sigma)
{
    float **u0 = prepare_u0(nx,ny,xa,ya,sigma, delta);
    float** u1 = get_ready(nx,ny);
    fill_vs(str,vx,vy,nx,ny,delta,i1,i2,j1);
    float vmax = vm(vx,vy,nx,ny);
    float dt = delta/(4. * vmax);

    float it_max = 3500;
    copy_matrix(u1,u0,nx,ny);

    for(int it=1; it<=it_max; it++)
    {
        for(int k=1; k<=20; k++)
        {
            for(int i=0; i<=nx; i++)
            {
                for(int j=1; j<ny; j++)
                {
                    if(!zastawka(i,j,i1,i2,j1))
                    {
                        if(i==0)
                        {
                            u1[i][j] = CN(u0,u1,delta,D,dt,vx,vy,i,j,nx,i+1);
                        }
                        else if(i==nx)
                        {
                            u1[i][j] = CN(u0,u1,delta,D,dt,vx,vy,i,j,i-1,0);
                        }
                        else
                        {
                            u1[i][j] = CN(u0,u1,delta,D,dt,vx,vy,i,j, i-1, i+1);
                        }
                    }
                }
            }

            
        }
        copy_matrix(u0,u1,nx,ny);
        printf("%d\n",it);
        fprintf(output,"%d\t%g\t%g\n", it, xsr(u0,nx,ny,delta), c(u0,nx,ny,delta));
    }

    delete_matrix(u0,nx);
    delete_matrix(u1,nx);
    
}

float** prepare_u0(int nx, int ny, float xa, float ya, float sigma, float delta)
{
    float ** u0 = get_ready(nx,ny);

    for(int i=0; i<=nx; i++)
    {
        for(int j=0; j<=ny; j++)
        {
            float x = i*delta;
            float y = j*delta;
            u0[i][j] = exp(-(pow(x - xa,2) + pow(y-ya,2))/(2.*pow(sigma,2)))/(2*M_PI*pow(sigma,2));
        }
    }

    return u0;
} 

void copy_matrix(float** to, float** from, int nx, int ny)
{
    for(int i=0; i<=nx; i++)
    {
        for(int j=0; j<=ny; j++)
        {
            to[i][j] = from[i][j];
        }
    }
}

int zastawka(int i, int j, int i1, int i2, int j1)
{
    if(i>=i1 && i<=i2 && j<=j1)
    {
        return 1;
    }
    return 0;
}

float CN(float** u0, float** u1, float delta, float D, float dt, float** vx, float** vy, int i, int j, int left, int right)
{
    float part1 = (u0[right][j] - u0[left][j] + u1[right][j] - u1[left][j])/(2. * delta);
    float part2 = 1./(1 + (2*D*dt/pow(delta,2)));
    float part3 = u0[i][j] - (dt * vx[i][j] * 0.5) * part1;
    float part4 = (u0[i][j+1] - u0[i][j-1] + u1[i][j+1] - u1[i][j-1])/(2. * delta);
    float part5 = dt*0.5*vy[i][j] * part4;
    float part6 = (u0[right][j] + u0[left][j] + u0[i][j+1] + u0[i][j-1] - 4*u0[i][j])/pow(delta,2);
    float part7 = (u1[right][j] + u1[left][j] + u1[i][j+1] + u1[i][j-1])/pow(delta,2);
    float part8 = dt*0.5*D*(part6 + part7);

    return part2 * (part3 - part5 + part8);
}

float xsr(float** u, int nx, int ny, float delta)
{
    float sum=0;

    for(int i=0; i<=nx; i++)
    {
        for(int j=0; j<=ny; j++)
        {
            sum += delta*i*u[i][j] * pow(delta,2);
        }
    }

    return sum;
}

float c(float** u, int nx, int ny, float delta)
{
    float sum=0;

    for(int i=0; i<=nx; i++)
    {
        for(int j=0; j<=ny; j++)
        {
            sum += u[i][j] * pow(delta,2);
        }
    }

    return sum;
}