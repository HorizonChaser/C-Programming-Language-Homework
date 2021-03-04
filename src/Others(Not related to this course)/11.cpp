#include<stdio.h>

int sum[20000000] = {0};

int main()
{
	double a;
	int t,n,i,j,k;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%lf%d",&a,&t);
		for(j=1;j<=t;j++)
		{
			k=int(j*a);
			sum[k]++;
		}
	}
	for(i=0;;i++)
	{
		if(sum[i]%2==1)
		{
			printf("%d",i);
			break;
		}
	}
	return 0;
}
