#include <stdio.h>
#include <math.h>
#include<stdlib.h>

#define MAX_SIZE 10
#define bound pow(2, 127)
#define ZERO 1e-9 /* X is considered to be 0 if |X|<ZERO */

enum bool { false = 0, true = 1 };
#define bool enum bool

int Jacobi( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN );

int Gauss_Seidel( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN );

int main()
{
    int n, MAXN, i, j, k;
    double a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE], x[MAX_SIZE];
    double TOL;

    scanf("%d", &n);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++)
            scanf("%lf", &a[i][j]);
        scanf("%lf", &b[i]);
    }
    scanf("%lf %d", &TOL, &MAXN);

    printf("Result of Jacobi method:\n");
    for ( i=0; i<n; i++ )
        x[i] = 0.0;
    k = Jacobi( n, a, b, x, TOL, MAXN );
    switch ( k ) {
        case -2:
            printf("No convergence.\n");
            break;
        case -1: 
            printf("Matrix has a zero column.  No unique solution exists.\n");
            break;
        case 0:
            printf("Maximum number of iterations exceeded.\n");
            break;
        default:
            printf("no_iteration = %d\n", k);
            for ( j=0; j<n; j++ )
                printf("%.8f\n", x[j]);
            break;
    }
    printf("Result of Gauss-Seidel method:\n");
    for ( i=0; i<n; i++ )
        x[i] = 0.0;
    k = Gauss_Seidel( n, a, b, x, TOL, MAXN );
    switch ( k ) {
        case -2:
            printf("No convergence.\n");
            break;
        case -1: 
            printf("Matrix has a zero column.  No unique solution exists.\n");
            break;
        case 0:
            printf("Maximum number of iterations exceeded.\n");
            break;
        default:
            printf("no_iteration = %d\n", k);
            for ( j=0; j<n; j++ )
                printf("%.8f\n", x[j]);
            break;
    }

    return 0;
}

/* Your function will be put here */  
int findbigdown(double** a,int i,int n, int k)
{
    double big;
    int line;
    big=fabs(a[k][i]);
    line=k;
    for(int j=k;j<n;j++)
    {
        if(fabs(a[j][i])>big)
        {
            big=fabs(a[j][i]);
            line=j;
        }    
    }
    return line;
}
int findbigabove(double** a,int i, int n,int k)
{
    double big;
    int line;
    big=fabs(a[k][i]);
    line=k;
    for(int j=0;j<k;j++)
    {
        if(fabs(a[j][i])>big)
        {
            big=fabs(a[j][i]);
            line=j;
        }    
    }
    return line;
}
int Jacobi( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN )
{
    int* assist=(int*)malloc(sizeof(int)*n);
    double** z=(double**)malloc(sizeof(double*)*MAX_SIZE);
    double* bb= (double*)malloc(sizeof(double)*n);
    for(int i=0;i<n;i++)
    {
        bb[i]=b[i];
    }
    for(int i=0;i<n;i++)
    {
        z[i]=(double*)malloc(sizeof(double)*MAX_SIZE);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            z[i][j]=a[i][j];
        }
    }
    double big;
    int line;
    double* help;
    double help1;
    int j=0;
    for(int i=0;i<n;i++)
    {
        line=findbigdown(z,i,n,j);
        if(fabs(z[line][i])>0)
        {
           help=z[line];
           z[line]=z[j];
           z[j]=help;
           help1=bb[line];
           bb[line]=bb[j];
           bb[j]=help1;
           assist[i]=j;
           j++;
        }
        else
        {
            line=findbigabove(z,i,n,j);
            if(fabs(z[line][i])>0)
            {
                assist[i]=line;
            }
            else
            {
                return -1;
            }
        }
    }
    int s,p;
    double* helper=(double*)malloc(sizeof(double)*n);  
    for(int i=0;i<n;i++)
    {
        helper[i]=x[i];
    }
    for(p=0;p<MAXN;p++)
    {
        for(int i=0;i<n;i++)
        {
            x[i]=bb[i]/z[assist[i]][i];
            for(int t=0;t<n;t++)
            {
                if(t!=i)
                {
                    x[i]-=z[assist[i]][t]*helper[t]/z[assist[i]][i];
                }
            }
        }
        for(int i=0;i<n;i++)
        {
            if(fabs(x[i])>=bound)
            {
                return -2;
            }
        }
        for(s=0;s<n;s++)
        {
            if(fabs(x[s]-helper[s])>=TOL)
            {
                break;
            }
        }
        if(s==n)
        {
            return p+1;
        }
        for(int i=0;i<n;i++)
        {
            helper[i]=x[i];
        }
        
        
    }
    if(p==MAXN)
    {
        return 0;
    }  
}
int Gauss_Seidel( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN )
{
    int* assist=(int*)malloc(sizeof(int)*n);
    double** z=(double**)malloc(sizeof(double*)*MAX_SIZE);
    double* bb= (double*)malloc(sizeof(double)*n);
    for(int i=0;i<n;i++)
    {
        bb[i]=b[i];
    }
    for(int i=0;i<n;i++)
    {
        z[i]=(double*)malloc(sizeof(double)*MAX_SIZE);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            z[i][j]=a[i][j];
        }
    }
    double big;
    int line;
    double* help;
    double help1;
    int j=0;
    for(int i=0;i<n;i++)
    {
        line=findbigdown(z,i,n,j);
        if(fabs(z[line][i])>0)
        {
           help=z[line];
           z[line]=z[j];
           z[j]=help;
           help1=bb[line];
           bb[line]=bb[j];
           bb[j]=help1;
           assist[i]=j;
           j++;
        }
        else
        {
            line=findbigabove(z,i,n,j);
            if(fabs(z[line][i])>0)
            {
                assist[i]=line;
            }
            else
            {
                return -1;
            }
        }
    }
    int s,p;
    double* helper=(double*)malloc(sizeof(double)*n);  
    for(int i=0;i<n;i++)
    {
        helper[i]=x[i];
    }
    for(p=0;p<MAXN;p++)
    {
        for(int i=0;i<n;i++)
        {
            x[i]=bb[i]/z[assist[i]][i];
            for(int t=0;t<n;t++)
            {
                if(t!=i)
                {
                    x[i]-=z[assist[i]][t]*x[t]/z[assist[i]][i];
                }
            }
        }
        for(int i=0;i<n;i++)
        {
            if(fabs(x[i])>=bound)
            {
                return -2;
            }
        }
        for(s=0;s<n;s++)
        {
            if(fabs(x[s]-helper[s])>=TOL)
            {
                break;
            }
        }
        if(s==n)
        {
            return p+1;
        }
        for(int i=0;i<n;i++)
        {
            helper[i]=x[i];
        }
        
        
    }
    if(p==MAXN)
    {
        return 0;
    }  
}