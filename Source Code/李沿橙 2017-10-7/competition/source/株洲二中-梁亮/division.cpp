#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>

using namespace std;
int n,k;
bool pingf[262150];
int a[131080];
int l[131080],r[131080],group=1;
int main()
{
	freopen("division.in","r",stdin);
	freopen("division.out","w",stdout);
	
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	if(k==2)	{printf("1\n\n");return 0;}
	
	for(int i=1;i<=512;++i)
		pingf[i*i]=true;
	
	l[1]=1;
	for(int i=2;i<=n;++i)
	{
		r[group]=i-1;
		for(int j=l[group];j<=r[group];++j)
			if(pingf[a[j]+a[i]])	{r[group++]=i-1;l[group]=i;break;}
	}
	
	
	printf("%d\n",group);
	for(int i=1;i<group;++i)
		printf("%d ",r[i]);
	return 0;
}
