#include <stdio.h>

void Series_Sum( double sum[] );

int main()
{
    int i;
    double x, sum[3001];
    
    Series_Sum( sum );

    x = 0.0;
    for (i=0; i<=3000; i++) {
        printf("%6.2f %16.12f\n", x + (double)i * 0.10, sum[i]);
    }

    return 0;
}

/* Your function will be put here */  
void Series_Sum(double sum[]) { 
    for(int i=0;i<=3000;i++) 
    {
        sum[i]=0;
    } 
    double assist;
    for(int i=10;i<=3000;i+=10) 
    {
        assist=i/10;
        for(int j=1;j<=assist;j++) 
        {
            sum[i]+=1.0/assist*1.0/j;
        }
    }
    double k;
    int help;
    double middle=0;  
    sum[0]=1.644934066848;

    
  
    
    for(int i=1;i<=3000;i++) 
    {
        if(i%10==0)
           continue;
        assist=i*1.0/10;
        help=i*1.0/10;
        middle=0;
        for(k=1;k<=100000;k++) 
        {
            middle+=(1+help-assist)/(k*1.0*(k+assist)*(k+help)*(k+help+1));
        }
        sum[i]=sum[help*10]+(help-assist)*(sum[help*10]-sum[help*10+10]+middle);
    }

}


