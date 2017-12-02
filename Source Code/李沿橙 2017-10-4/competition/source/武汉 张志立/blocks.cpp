#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
int n,m; 
int s1,s2,ms;
int l,k;
int i,j,t,h;
int r[1000005];
int a[1000005],f[1000005],w[1000005];
int suma[1000005],sumf[1000005];
int main()
{
    freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	cin>>n>>m;
	for(l=1;l<=n;l++)
	{
		cin>>r[l];
	}
	for(i=1;i<=m;i++)
{
	
	cin>>k;
	int tt=0;
	a[0]=-1;
	for(l=1;l<=n;l++) a[l]=0,f[l]=0;
	for(l=1;l<=n;l++)
	{
		if(r[l]>=k && a[tt]>=0) a[tt]+=r[l]-k,f[tt]++;
		if(r[l]>=k && a[tt]<0) a[++tt]+=r[l]-k,f[tt]=1;
		if(r[l]<k) a[++tt]+=r[l]-k,f[tt]=1;
	
	}
	ms=0;
	
	for(l=1;l<=tt;l++)
	{
		suma[l]=suma[l-1]+a[l];
		sumf[l]=sumf[l-1]+f[l];
	}
	
	
    for(l=1;l<=tt;l++)
    {
    	for(j=1;j<=l;j++)
    	{
    		s1=suma[l]-suma[j]+a[j];
			s2=sumf[l]-sumf[j]+f[j];
    		if(s1>=0 && s2>ms) ms=s2;
    	}
	}
	cout<<ms<<' ';
}
	return 0;
	
}

