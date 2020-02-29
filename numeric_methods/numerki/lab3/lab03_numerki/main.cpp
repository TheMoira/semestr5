#include <iostream>
#include <cmath>
#include <vector>

using namespace std;



//funkcja f (wzor 2)
double f(double v);

//funkcja g (wzor 3)
double g(double alfa, double x, double v);

//sch.num: metoda trapezów, gdzie x/vprev = x/vn, x/v = x/vn+1, wszystko fajnie liczymy
//zwracany vector, gdzie vec[0] = xn+1, a vec[1] = vn+1
vector<double> trapez(double xprev, double vprev, double alfa, double dt);

//sch.num: metoda RK2, gdzie x/vprev = x/vn, x/v = x/vn+1, wszystko fajnie liczymy
//zwracany vector, gdzie vec[0] = xn+1, a vec[1] = vn+1
vector<double> RK2(double xprev, double vprev, double alfa, double dt);

//funkcja v(x) albo ta docelowa, no idea, co z tym u, co ona ma zwracać??
double vx(double alfa, double x, double v);

//krok czasowy - zauwaz zaleznosci miedzy pierwsy=zymi dwoma komentarzami
//nie jestem pewna czy po zakonczonym ifie zmieniac t+=dt;
void krok(bool opt, double dt, double x0, double v0, double tmax, double alfa, int p, double TOL, double S);



int main()
{
    double x0 = 0.01;
    double v0 = 0;
    double dt0 = 1;
    double S = 0.75;
    int p = 2;
    double tmax = 40;
    double alfa = 5;
    double TOL;

    //void krok(bool opt, double dt, double x0, double v0, double tmax, double alfa, int p, double TOL, double S)
    
    
    //**********metoda trapezów************
    
    //TOL = 1e-2;
    TOL = 1e-2;
    cout<<"#*****MT\tTOL = "<<TOL<<endl;
    krok(1,dt0,x0,v0,tmax,alfa,p,TOL,S);


    //TOL = 1e-5;
    TOL = 1e-5;
    cout<<"#*****MT\tTOL = "<<TOL<<endl;
    krok(1,dt0,x0,v0,tmax,alfa,p,TOL,S);


    //**********metoda RK2***********

    //TOL = 1e-2;
    TOL = 1e-2;
    cout<<"#*****MRK2\tTOL = "<<TOL<<endl;
    krok(0,dt0,x0,v0,tmax,alfa,p,TOL,S);

    //TOL = 1e-5;
    TOL = 1e-5;
    cout<<"#*****MRK2\tTOL = "<<TOL<<endl;
    krok(0,dt0,x0,v0,tmax,alfa,p,TOL,S);

    return 0;
}




double f(double v)
{
    return v;
}

double g(double alfa, double x, double v)
{
    return alfa*(1-pow(x,2)) * v - x;
}


vector<double> trapez(double xprev, double vprev, double alfa, double dt)
{
    vector<double> wynik(2);

    double x = xprev;
    double v = vprev;
    double dx, dv, F, G, a11, a12, a21, a22;
    double o = 1e-10;

    do
    {
        F = x - xprev - (dt/2.)*(f(v) + f(vprev));
        G = v - vprev - (dt/2.)*(g(alfa,xprev,vprev) + g(alfa,x,v));

        a11 = 1;
        a12 = -dt/2.;
        a21 = -(dt/2.)*(-2*alfa*x*v-1);
        a22 = 1 - (dt/2.)*alfa*(1-pow(x,2));

        dx = (-F*a22 + G*a12)/(a11*a22 - a12*a21);
        dv = (-G*a11 + F*a21)/(a11*a22 - a12*a21);

        x = x + dx;
        v = v + dv;
    
    }while(o < fabs(dx) || o < fabs(dv));

    wynik[0] = x;
    wynik[1] = v;

    return wynik;

}


vector<double> RK2(double xprev, double vprev, double alfa, double dt)
{
    vector<double> wynik(2);

    double k1x = f(vprev);
    double k1v = g(alfa,xprev,vprev);

    double k2x = f(vprev + dt*k1v);
    double k2v = g(alfa,xprev + dt*k1x, vprev + dt*k1v);

    double x = xprev + (dt/2.)*(k1x + k2x);
    double v = vprev + (dt/2.)*(k1v + k2v);

    wynik[0] = x;
    wynik[1] = v;

    return wynik;
}

//co to jest u?
double vx(double alfa, double x, double v)
{
    return g(alfa,x,v) - alfa*(1-pow(x,2))*f(v) ;
}

void krok(bool opt, double dt, double x0, double v0, double tmax, double alfa, int p, double TOL, double S)
{
    double t = 0;
    vector<double> vec1(2);
    vector<double> vec2(2);
    vector<double> vec3(2);

    //RK2(double xprev, double vprev, double alfa, double dt)
    vector<double> (*fun)(double,double, double, double) = opt? trapez : RK2;

    while(t<tmax)
    {
        vec1 = fun(x0,v0,alfa,dt);
        vec2 = fun(vec1[0],vec1[1],alfa,dt);
        vec3 = fun(x0,v0,alfa,2*dt);

        double Ex = (vec2[0] - vec3[0])/(pow(2,p) - 1);
        double Ev = (vec2[1] - vec3[1])/(pow(2,p) - 1);

        double diff = max(fabs(Ex), fabs(Ev));

        if(diff < TOL)
        {
            t += 2*dt;
            x0 = vec2[0];
            v0 = vec2[1];
            //cout<<"t = "<<t<<"\tdt = "<<dt<<"\txn = "<<x0<<"\tvn = "<<v0<<"\tv(x) = "<<vx(alfa,x0,v0)<<endl;
            cout<<t<<"\t"<<dt<<"\t"<<x0<<"\t"<<v0<<endl;
        }

        dt *= pow((S*TOL)/diff, 1./(p+1));
    }

    cout<<endl<<endl;
}