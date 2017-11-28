#include <cmath>
#include <queue>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 200010
#define ll long long
#define inf 1000000000
using namespace std;
inline int read() 
{ 
    int x=0,f=1;char ch=getchar(); 
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();} 
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} 
    return x*f; 
}
int n,m;
ll lastans;
int a[N];
int main()
{
	freopen("bad6.in","r",stdin);
	freopen("badbl.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	a[i]=read();
	for(int i=1;i<=m;i++)
	{
		lastans=abs(lastans);
		int opt=read();
		if(opt==1)
		{
			int x=read(),v=read();
			x=(x^lastans)%n+1;
			a[x]=v;
		}
		else if(opt==2)
		{
			int x=read(),v=read();
			x=(x^lastans)%n+1;
			a[x]+=v;
		}
		else if(opt==3)
		{
			int l=read(),r=read();
			l=(l^lastans)%n+1,r=(r^lastans)%n+1;
			if(l>r)swap(l,r);
			for(int i=l;i<=r;i++)
			a[i]=-a[i];
		}
		else if(opt==4)
		{
			int l=read(),r=read();
			l=(l^lastans)%n+1,r=(r^lastans)%n+1;
			if(l>r)swap(l,r);
			int mx=-inf;
			for(int i=l;i<=r;i++)
			mx=max(mx,a[i]);
			printf("%d\n",mx);
			lastans=mx;
		}
		else if(opt==5)
		{
			int l=read(),r=read();
			l=(l^lastans)%n+1,r=(r^lastans)%n+1;
			if(l>r)swap(l,r);
			int mn=inf;
			for(int i=l;i<=r;i++)
			mn=min(mn,a[i]);
			printf("%d\n",mn);
			lastans=mn;
		}
		else if(opt==6)
		{
			int l=read(),r=read();
			l=(l^lastans)%n+1,r=(r^lastans)%n+1;
			if(l>r)swap(l,r);
			ll sum=0;
			for(int i=l;i<=r;i++)
			sum+=a[i];
			printf("%lld\n",sum);
			lastans=sum;
		}
	}
}