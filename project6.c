#include <stdio.h>

#define MAX_N 10

void Cubic_Spline(int n, double x[], double f[], int Type, double s0, double sn, double a[], double b[], double c[], double d[]);

double S( double t, double Fmax, int n, double x[], double a[], double b[], double c[], double d[] );

int main()
{
    int n, Type, m, i;
    double x[MAX_N], f[MAX_N], a[MAX_N], b[MAX_N], c[MAX_N], d[MAX_N];
    double s0, sn, Fmax, t0, tm, h, t;

    scanf("%d", &n);
    for (i=0; i<=n; i++) 
        scanf("%lf", &x[i]);
    for (i=0; i<=n; i++) 
        scanf("%lf", &f[i]);
    scanf("%d %lf %lf %lf", &Type, &s0, &sn, &Fmax);

    Cubic_Spline(n, x, f, Type, s0, sn, a, b, c, d);
    for (i=1; i<=n; i++)
        printf("%12.8e %12.8e %12.8e %12.8e \n", a[i], b[i], c[i], d[i]);

    scanf("%lf %lf %d", &t0, &tm, &m);
    h = (tm-t0)/(double)m;
    for (i=0; i<=m; i++) {
        t = t0+h*(double)i;
        printf("f(%12.8e) = %12.8e\n", t, S(t, Fmax, n, x, a, b, c, d));
    }

    return 0;
}

#include<stdlib.h>
#include<math.h>
/* Your functions will be put here */  
void Cubic_Spline(int n, double x[], double f[], int Type, double s0, double sn, double a[], double b[], double c[], double d[])
{
    if(Type==2)//Natural Spine
    {
        for(int i=0;i<=n;i++)
        {
            a[i+1]=f[i];
        }
        double* h=(double*)malloc(sizeof(double)*(n+1));
        for(int i=1;i<=n;i++)
        {
            h[i-1]=x[i]-x[i-1];
        }
        double* AA=(double*)malloc(sizeof(double)*(n+1));
        for(int i=1;i<n;i++)
        {
            AA[i]=3/h[i]*(f[i+1]-f[i])-3/h[i-1]*(f[i]-f[i-1]);
        }
        double* l=(double*)malloc(sizeof(double)*(n+1));
        double* miu=(double*)malloc(sizeof(double)*(n+1));
        double* z=(double*)malloc(sizeof(double)*(n+1));
        l[0]=1;
        miu[0]=0;
        z[0]=s0/2;
        for(int i=1;i<n;i++)
        {
            l[i]=2*(x[i+1]-x[i-1])-h[i-1]*miu[i-1];
            miu[i]=h[i]/l[i];
            z[i]=(AA[i]-h[i-1]*z[i-1])/l[i];
        }
        l[n]=1;
        z[n]=sn/2;
        c[n+1]=sn/2;
        for(int j=n-1;j>=0;j--)
        {
            c[j+1]=z[j]-miu[j]*c[j+2];
            b[j+1]=(f[j+2]-f[j+1])/h[j]-h[j]*(c[j+2]+2*c[j+1])/3;
            d[j+1]=(c[j+2]-c[j+1])/(3*h[j]);
        }
        free(h);
        free(AA);
        free(l);
        free(miu);
        free(z);

    }
    else if(Type==1)//clamped spline
    {
        for(int i=0;i<=n;i++)
        {
            a[i+1]=f[i];
        }
        double* h=(double*)malloc(sizeof(double)*(n+1));
        for(int i=1;i<=n;i++)
        {
            h[i-1]=x[i]-x[i-1];
        }
        double* AA=(double*)malloc(sizeof(double)*(n+1));
        AA[0]=3*(f[1]-f[0])/h[0]-3*s0;
        AA[n]=3*sn-3*(f[n]-f[n-1])/h[n-1];
        for(int i=1;i<n;i++)
        {
            AA[i]=3/h[i]*(f[i+1]-f[i])-3/h[i-1]*(f[i]-f[i-1]);
        }
        double* l=(double*)malloc(sizeof(double)*(n+1));
        double* miu=(double*)malloc(sizeof(double)*(n+1));
        double* z=(double*)malloc(sizeof(double)*(n+1));
        l[0]=2*h[0];
        miu[0]=0.5;
        z[0]=AA[0]/l[0];
        for(int i=1;i<n;i++)
        {
            l[i]=2*(x[i+1]-x[i-1])-h[i-1]*miu[i-1];
            miu[i]=h[i]/l[i];
            z[i]=(AA[i]-h[i-1]*z[i-1])/l[i];
        }
        l[n]=h[n-1]*(2-miu[n-1]);
        z[n]=(AA[n]-h[n-1]*z[n-1])/l[n];
        c[n+1]=z[n];
        for(int j=n-1;j>=0;j--)
        {
            c[j+1]=z[j]-miu[j]*c[j+2];
            b[j+1]=(a[j+2]-a[j+1])/h[j]-h[j]*(c[j+2]+2*c[j+1])/3;
            d[j+1]=(c[j+2]-c[j+1])/(3*h[j]);
        }
        free(h);
        free(AA);
        free(l);
        free(miu);
        free(z);

    }
}
double S( double t, double Fmax, int n, double x[], double a[], double b[], double c[], double d[] )
{
    double result;
    for(int i=0;i<n;i++)
    {
        if(t<=x[i+1]&&t>=x[i])
        {
            result=a[i+1]+b[i+1]*(t-x[i])+c[i+1]*pow((t-x[i]),2)+d[i+1]*pow((t-x[i]),3);
        }
    }
    if(t>x[n]||t<x[0])
    {
        result=Fmax;
    }
    return result;
}

