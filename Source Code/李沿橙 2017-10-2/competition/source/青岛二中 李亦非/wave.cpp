#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int a[2020200];
int n,k;
int find_min(int x)
{
	int mn=a[x];
	x++;
	while(x<=n&&a[x]-mn<k)
	{
		mn=min(mn,a[x]);
		x++;
	}
	return x;
}
int find_max(int x)
{
	int mx=a[x];
	x++;
	while(x<=n&&mx-a[x]<k)
	{
		mx=max(mx,a[x]);
		x++;
	}
	return x;
}
int read()
{
	int x=0;
	char c;
	c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=x*10+c-'0',c=getchar();
	return x;
}
int main()
{
	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	int i,ans;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++)
		a[i]=read();
	//	scanf("%d",&a[i]);
	i=1;ans=1;
	while(i<=n)
	{
		i=find_min(i);
		if(i>n)
			break;
		ans++;
		i=find_max(i);
		if(i>n)
			break;
		ans++;
	}
	printf("%d",ans);
	return 0;
}
