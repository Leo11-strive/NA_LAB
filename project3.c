#include <stdio.h>
#include<stdlib.h>
#define Max_size 10000 /* max number of dishes */

void Price( int n, double p[] );

int main()
{
    int n, i;
    double p[Max_size];

    scanf("%d", &n);
    for (i=0; i<n; i++) 
        scanf("%lf", &p[i]);
    Price(n, p);
    for (i=0; i<n; i++)
        printf("%.2f ", p[i]);
    printf("\n");

    return 0;
}

/* Your function will be put here */  
void Price( int n, double p[] )
{
    double* pp=(double*)malloc(sizeof(double)*(n+1));
    for(int i=0;i<n;i++)
    {
        pp[i+1]=p[i];
    }
    double* m=(double*)malloc(sizeof(double)*(n));
    double* Q=(double*)malloc(sizeof(double)*(n));
    double* l=(double*)malloc(sizeof(double)*(2*n));
    double* u=(double*)malloc(sizeof(double)*(n));
    double* z=(double*)malloc(sizeof(double)*(n)); 
    double* assist=(double*)malloc(sizeof(double)*(n));
    double* result=(double*)malloc(sizeof(double)*(n+1));
    for(int i=1;i<=n-1;i++)
    {
        if(i==1||i==n-1)
        {
            assist[i]=-0.5;
        }
        else
        {
            assist[i]=0;
        }
    }
    l[2]=2;
    u[1]=0.5/l[2];
    z[1]=pp[1]/l[2]; 
    for(int i=2;i<=n-2;i++)
    {
        l[2*i-1]=0.5;
        l[2*i]=2.0-u[i-1]*l[2*i-1];
        u[i]=0.5/l[2*i];
        z[i]=(pp[i]-l[2*i-1]*z[i-1])/l[2*i];
    }
    l[2*(n-1)-1]=0.5;  
    l[2*(n-1)]=2.0-l[2*(n-1)-1]*u[n-2];
    z[n-1]=(pp[n-1]-l[2*(n-1)-1]*z[n-2])/l[2*(n-1)];  
    Q[n-1]=z[n-1];  
    for(int i=n-2;i>=1;i--)
    {
        Q[i]=z[i]-u[i]*Q[i+1];
    }  
    l[2]=2;
    u[1]=0.5/l[2];
    z[1]=assist[1]/l[2];
    for(int i=2;i<=n-2;i++)
    {
        l[2*i-1]=0.5;
        l[2*i]=2.0-u[i-1]*l[2*i-1];
        u[i]=0.5/l[2*i];
        z[i]=(assist[i]-l[2*i-1]*z[i-1])/l[2*i];
    }
    l[2*(n-1)-1]=0.5;
    l[2*(n-1)]=2.0-l[2*(n-1)-1]*u[n-2];
    z[n-1]=(assist[n-1]-l[2*(n-1)-1]*z[n-2])/l[2*(n-1)];
    m[n-1]=z[n-1];
    for(int i=n-2;i>=1;i--)
    {
        m[i]=z[i]-u[i]*m[i+1];
    }
    result[n]=(pp[n]-0.5*(Q[1]+Q[n-1]))/(2+0.5*(m[1]+m[n-1]));  
    for(int i=1;i<=n-1;i++)
    {
        result[i]=m[i]*result[n]+Q[i];
    }
    for(int i=0;i<n;i++)
    {
        p[i]=result[i+1];
    }
    free(pp);
    free(m);
    free(Q);
    free(l);
    free(u);
    free(z);
    free(assist);
    free(result);

}