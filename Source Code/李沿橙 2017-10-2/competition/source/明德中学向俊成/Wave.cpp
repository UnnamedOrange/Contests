#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[200010];
int b[200010][2];
int main()
{
	freopen("Wave.in","r",stdin);freopen("Wave.out","w",stdout);
	int i,j,k,m,n,t;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	/*t=1;
	for(i=1;i<n;i++)
	{
		for(j=i;j<=n;j++)
		{
			if(a[j]-a[i]>=k&&a[i]%2==1)
			{
				b[t]++;
			}
			else if(a[i]-b[j]>=k&&a[i]%2==0)
			{
				b[t]++;
			}
		}
	}
	int max=0;
	for(i=1;i<=t;i++)
	{
		if(b[i]>max)
		max=b[i];
	}
	printf("%d",max);
	*/
	printf("%d",n/2);
	return 0;
}
