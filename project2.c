#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#define ZERO 1e-13 /* X is considered to be 0 if |X|<ZERO */
#define MAXN 11    /* Max Polynomial Degree + 1 */

double Polynomial_Root(int n, double c[], double a, double b, double EPS);

int main()
{
    int n;
    double c[MAXN], a, b;
    double EPS = 0.00005;
    int i;

    scanf("%d", &n);
    for (i=n; i>=0; i--) 
        scanf("%lf", &c[i]);
    scanf("%lf %lf", &a, &b);
    printf("%.4f\n", Polynomial_Root(n, c, a, b, EPS));

    return 0;
}

/* Your function will be put here */ 


double calculatef(double f[], int n, double input)
{
    double answer=0;
    for(int i=0;i<=n;i++)
    {
        answer=answer*input+f[n-i];
    }
    return answer;
}
double Polynomial_Root(int n, double c[], double a, double b, double EPS)
{
    double* d=(double*)malloc(n*sizeof(double));
    double* e=(double*)malloc((n-1)*sizeof(double));
    if(n==1)
       return (-c[0]/c[1]);
    double help;
    if(a>b)
    {
        double help=a;
        a=b;
        b=help;
    }
    if(a==b)
        return a;
    for(int m=0;m<n;m++)
    {
        d[m]=c[m+1]*(m+1);
    }
    for(int m=0;m<n-1;m++)
    {
        e[m]=d[m+1]*(m+1);
    }
    double current=a;
    double assist=a;
    int g;
    for(int q=0;q<5;q++)
    {
       current=a+(double)q*((b-a)/4);
       g=0;
       while(g<2000)
       {
           assist=current;
           current=assist-(calculatef(c,n,assist)*calculatef(d,n-1,assist))/(calculatef(d,n-1,assist)*calculatef(d,n-1,assist)-calculatef(c,n,assist)*calculatef(e,n-2,assist));
           if(current<a||current>b)
               break;
           if(fabs(current-assist)<EPS/2||fabs(calculatef(c,n,current))<ZERO/2)
               return current;

           if(current<a||current>b)
               break;
           g++;
       }
    }
    free(e);
    free(d);

}
