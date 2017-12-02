#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int f[1000005],w[1000005];
int a[1000005];
int i,j,n,k;
int  main()
{
	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	cin>>n>>k;
	for(i=1;i<=n;i++) cin>>a[i];
	for(i=1;i<=n;i++) f[i]=1;
	for(i=2;i<=n;i++)
	{	for(j=1;j<=i;j++)
		{
			if((f[j]+1)%2==0)
			{
				if(a[i]-a[j]>=k) f[i]=max(f[i],f[j]+1);
			}
			else 
			{
				if(a[j]-a[i]>=k) f[i]=max(f[i],f[j]+1);
			}
		}
	}	
	cout<<f[n];
	return 0;
}