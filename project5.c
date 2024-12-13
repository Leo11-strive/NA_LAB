#include <stdio.h>

#define MAX_SIZE 10

int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN);

int main()
{
    int n, MAXN, m, i, j, k;
    double a[MAX_SIZE][MAX_SIZE], v[MAX_SIZE];
    double lambda, TOL;

    scanf("%d", &n);
    for (i=0; i<n; i++) 
        for (j=0; j<n; j++) 
            scanf("%lf", &a[i][j]);
    scanf("%lf %d", &TOL, &MAXN);
    scanf("%d", &m);
    for (i=0; i<m; i++) {
        scanf("%lf", &lambda);
        for (j=0; j<n; j++)
            scanf("%lf", &v[j]);
        switch (EigenV(n, a, &lambda, v, TOL, MAXN)) {
            case -1: 
                printf("%12.8f is an eigenvalue.\n", lambda );
                break;
            case 0:
                printf("Maximum number of iterations exceeded.\n");
                break;
            case 1:
                printf("%12.8f\n", lambda );
                for (k=0; k<n; k++)
                    printf("%12.8f ", v[k]);
                printf("\n");
                break;
        }
    }

    return 0;
}

/* Your function will be put here */ 
#include<math.h> 
#include<stdlib.h>
int solvematrix(int n, double q, double* v, double a[][MAX_SIZE]);
int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN)
{
    double q=0,assist=0,help=0;
    q=*lambda;
    int p=0;
    double* need=(double*)malloc(n*sizeof(double));
    for(int i=0;i<n;i++)
    {
        if(fabs(v[i])>v[p])
        {
            p=i;
        }
    }
    for(int i=0;i<n;i++)
    {
        v[i]=v[i]/v[p];
    }
    int k=1;
    int m=0;
    double ERR=0;
    double miu=0;
    for(k=1;k<=MAXN;k++)
    {
        for(int i=0;i<n;i++)
        {
            need[i]=v[i];
        }
        if(solvematrix(n,q,v,a)==-1)
        {
            return -1;
        }
        m=0;
        for(int i=0;i<n;i++)
        {
            if(fabs(v[i])>fabs(v[m]))
            {
                m=i;
            }
        }
        miu=v[m];
        for(int i=0;i<n;i++)
        {
            v[i]=v[i]/miu;
        }
        
        ERR=0;
        for(int i=0;i<n;i++)
        {
            if(fabs(v[i]-need[i])>ERR)
            {
                ERR=fabs(v[i]-need[i]);
            }
        }
        if(ERR<TOL)
        {
            miu=q+1/miu;
            *lambda=miu;
            return 1;
        }
    }
    return 0;
}
int solvematrix(int n, double q, double* v, double a[][MAX_SIZE])
{
    double** para=(double**)malloc(n*sizeof(double*));  
    for(int i=0;i<n;i++)
    {
        para[i]=(double*)malloc(n*sizeof(double));
    }  
    for(int i=0;i<n;i++)
    {

        for(int j=0;j<n;j++)
        {
            para[i][j]=a[i][j];
        }
    }
    for(int i=0;i<n;i++)
    {
        para[i][i]-=q;
    }
    double** L=(double**)malloc(n*sizeof(double*));
    for(int i=0;i<n;i++)
    {
        L[i]=(double*)malloc(n*sizeof(double));
    }
    double** U=(double**)malloc(n*sizeof(double*));
    for(int i=0;i<n;i++)
    {
        U[i]=(double*)malloc(n*sizeof(double));
    }
    if(para[0][0]==0)
    {
        return -1;
    }  
    for(int i=0;i<n;i++)
    {
        L[i][i]=1;
    }
    U[0][0]=para[0][0];  
    for(int i=1;i<n;i++)
    {
        U[0][i]=para[0][i];
        L[i][0]=para[i][0]/U[0][0];
    }
    for(int i=1;i<n-1;i++)
    {
        U[i][i]=para[i][i];
        for(int s=0;s<i;s++)
        {
            U[i][i]-=L[i][s]*U[s][i];
        }
        if(U[i][i]==0)
        {
            return -1;
        }
        for(int j=i+1;j<n;j++)
        {
            U[i][j]=para[i][j];
            for(int s=0;s<i;s++)
            {
                U[i][j]-=L[i][s]*U[s][j];
            }
            L[j][i]=para[j][i];
            for(int s=0;s<i;s++)
            {
                L[j][i]-=L[j][s]*U[s][i];
            }
            L[j][i]/=U[i][i];
        }
    }
    U[n-1][n-1]=para[n-1][n-1];
    for(int s=0;s<n-1;s++)
    {
        U[n-1][n-1]-=L[n-1][s]*U[s][n-1];
    }
    if(U[n-1][n-1]==0)
    {
        return -1;
    }  
    double* y=(double*)malloc(n*sizeof(double));
    y[0]=v[0];
    for(int i=1;i<n;i++)
    {
        y[i]=v[i];
        for(int s=0;s<i;s++)
        {
            y[i]-=L[i][s]*y[s];
        }
    }
    v[n-1]=y[n-1]/U[n-1][n-1];
    for(int i=n-2;i>=0;i--)
    {
        v[i]=y[i];
        for(int s=i+1;s<n;s++)
        {
            v[i]-=U[i][s]*v[s];
        }
        v[i]/=U[i][i];
    }
    free(y);
    for(int i=0;i<n;i++)
    {
        free(para[i]);
        free(L[i]);
        free(U[i]);
    }
    return 0;
}