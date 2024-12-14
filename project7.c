#include <stdio.h>
#include <math.h>

double f0( double x, double l, double t )
{
    return sqrt(1.0+l*l*t*t*cos(t*x)*cos(t*x));
}

double Integral(double a, double b, double (*f)(double x, double y, double z), 
double eps, double l, double t);

int main()
{
    double a=0.0, b, eps=0.005, l, t;

    scanf("%lf %lf %lf", &l, &b, &t);
    printf("%.2f\n", Integral(a, b, f0, eps, l, t));

    return 0;
}

/* Your function will be put here */ 
double Integral(double a, double b, double (*f)(double x, double y, double z), 
double eps, double l, double t)
{
    int n = 500000;
    if(a==b)
        return 0;
    double h = (b-a)/n;
    double X0=f(a,l,t)+f(b,l,t);
    double X1=0;
    double X2=0;
    double X;
    
    for(int i=1;i<=n-1;i++)
    {
        X=a+i*h;
        if(i%2==0)
        {
            X2=X2+f(X,l,t);
        }
        else
        {
            X1=X1+f(X,l,t);
        }
    }
    return (X0+2*X2+4*X1)*h/3/100;
}
    