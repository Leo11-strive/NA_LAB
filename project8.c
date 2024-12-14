#include <stdio.h>
#include <math.h>

#define MAX_m 200
#define MAX_n 5

double f1(double x)
{
    return sin(x);
}

double f2(double x)
{
    return exp(x);
}

int OPA( double (*f)(double t), int m, double x[], double w[], double c[], double *eps );

void print_results( int n, double c[], double eps)
{    
    int i;

    printf("%d\n", n);
    for (i=0; i<=n; i++)
        printf("%12.4e ", c[i]);
    printf("\n");
    printf("error = %9.2e\n", eps);
    printf("\n");
}

int main()
{
    int m, i, n;
    double x[MAX_m], w[MAX_m], c[MAX_n+1], eps;

    m = 90;
    for (i=0; i<m; i++) {
        x[i] = 3.1415926535897932 * (double)(i+1) / 180.0;
        w[i] = 1.0;
    }
    eps = 0.001;
    n = OPA(f1, m, x, w, c, &eps);
    print_results(n, c, eps);

    m = 200;
    for (i=0; i<m; i++) {
        x[i] = 0.01*(double)i;
        w[i] = 1.0;
    }
    eps = 0.001;
    n = OPA(f2, m, x, w, c, &eps);
    print_results(n, c, eps);

    return 0;
}

/* Your function will be put here */  
double Presult(double *c, int n, double x)
{
    double result = 0;
    for(int i=0;i<=n;i++)
    {
        result+=c[i]*pow(x,i);
    }
    return result;
}
double Psum(double* c1, int n1, int n2,double x[], double w[], int m, double* c2)
{
    double sum = 0;
    for(int i=0;i<m;i++)
    {
        sum+=w[i]*Presult(c1,n1,x[i])*Presult(c2,n2,x[i]);
    }
    return sum;
}

double PsumY(double* c, int n, double x[], double w[], int m, double (*f)(double t))
{
    double sum = 0;
    for(int i=0;i<m;i++)
    {
        sum+=w[i]*f(x[i])*Presult(c,n,x[i]);
    }
    return sum;
}
void Pminus(double* c1, int n1, double* c2, int n2, double* c3)
{
    int max=n1;
    if(n1<n2)
       max=n2;
    for(int i=0;i<=max;i++)
    {
        c3[i]=c1[i]-c2[i];
    }
}
void PminusTri(double* c1, int n1, double* c2, int n2, double* c3, int n3, double* c4)
{
    int max=n1;
    if(n1<n2)
       max=n2;
    if(max<n3)
       max=n3;
    for(int i=0;i<=max;i++)
    {
        c4[i]=c1[i]-c2[i]-c3[i];
    }
}
int OPA( double (*f)(double t), int m, double x[], double w[], double c[], double *eps )
{
    double** fai=(double**)malloc(sizeof(double*)*(MAX_n+1));
    for(int i=0;i<=MAX_n;i++)
    {
        fai[i]=(double*)malloc(sizeof(double)*(MAX_n+1));
    }
    for(int i=0;i<=MAX_n;i++)
    {
        for(int j=0;j<=MAX_n;j++)
        {
            fai[i][j]=0;
        }
    }
    fai[0][0]=1;
    double* b=(double*)malloc(sizeof(double)*(MAX_n+1));
    for(int i=0;i<=MAX_n;i++)
    {
        b[i]=0;
    }
    double* d=(double*)malloc(sizeof(double)*(MAX_n+1));
    for(int i=0;i<=MAX_n;i++)
    {
        d[i]=0;
    }
    double* assist=(double*)malloc(sizeof(double)*(MAX_n+1));
    for(int i=0;i<=MAX_n;i++)
    {
        assist[i]=0;
    }
    double* assist1=(double*)malloc(sizeof(double)*(MAX_n+1));
    for(int i=0;i<=MAX_n;i++)
    {
        assist1[i]=0;
    }
    double* assist2=(double*)malloc(sizeof(double)*(MAX_n+1));
    for(int i=0;i<=MAX_n;i++)
    {
        assist2[i]=0;
    }
    assist[0]=0;
    assist[1]=1;
    b[1]=Psum(assist,1,0,x,w,m,fai[0])/Psum(fai[0],0,0,x,w,m,fai[0]);
    fai[1][0]=-b[1];
    fai[1][1]=1;
    for(int i=2;i<=MAX_n;i++)
    {
        for(int j=0;j<i;j++)
        {
            assist1[0]=0;
            assist1[j+1]=fai[i-1][j];
        }
        d[i]=Psum(assist1,i,i-2,x,w,m,fai[i-2])/Psum(fai[i-2],i-2,i-2,x,w,m,fai[i-2]);
        b[i]=Psum(assist1,i,i-1,x,w,m,fai[i-1])/Psum(fai[i-1],i-1,i-1,x,w,m,fai[i-1]);
        for(int j=0;j<i;j++)
        {
            assist[j]=fai[i-1][j]*b[i];
        }
        for(int j=0;j<i-1;j++)
        {
            assist2[j]=fai[i-2][j]*d[i];
        }
        PminusTri(assist1,i,assist,i-1,assist2,i-2,fai[i]);
    }
    int n=MAX_n;
    double* a=(double*)malloc(sizeof(double)*(MAX_n+1));
    double error=0;
    int result=0;
    for(int i=0;i<=MAX_n;i++)
    {
        c[i]=0;
    }
    for(int i=0;i<=n;i++)
    {
        a[i]=PsumY(fai[i],i,x,w,m,f)/Psum(fai[i],i,i,x,w,m,fai[i]);
        
        for(int j=0;j<=i;j++)
        {
            c[j]+=a[i]*fai[i][j];
        }
        error=0;
        for(int j=0;j<m;j++)
        {
            error+=w[j]*pow(f(x[j])-Presult(c,i,x[j]),2);
        }
        if(error<=*eps)
        {
            result=i;
            *eps=error;
            return result;
        }
    }
    *eps=error;
    return MAX_n;
}
