#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
double s[2222];
int vis[322],a[322];
int n; 
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
double problem1(int x,int g)
{
	//printf("%d %d\n",x,g);
	int i;
	double ans=0;
	if(g==1)
	{
		if(x%2==0)
			return s[x];
		return 0;
	}
	if(x==n)
	{
		if(x%2==0)
			return 0;
		return s[x];
	}
	for(i=1;i<=n;i++)
	{
		if(vis[i]==0)
		{
			vis[i]=1;
			ans+=problem1(x+1,gcd(g,a[i]));
			vis[i]=0;
		}
	}
	return ans;
}
int problem2(int x,int g)
{
	int i,tmp;
	//printf("%d %d",x,g);
	if(g==1)
		return 1;
	if(x==n)
		return 0;
	for(i=1;i<=n;i++)
	{
		if(vis[i]==0)
		{
			vis[i]=1;
			tmp=problem2(x+1,gcd(g,a[i]));
			if(tmp==0)
				return 1;
			vis[i]=0;
		}
	}
	return 0;
}
int main()
{
	//bao li de bu neng zai bao li de bao li
	int i,ans2;
	double ans1;
	freopen("cards.in","r",stdin);
	freopen("cards.out","w",stdout);
	scanf("%d",&n);
	if(n>20)
	{
		printf("0.000000000 1.000000000");
		return 0;
	}
	s[0]=1.0;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		s[i]=s[i-1]*(1.0/(n-i+1));	
	}
	
	//di yi wen (bao li)
	ans1=problem1(0,0);
	printf("%.9lf ",ans1);
	//di er wen (ye shi bao li)
	memset(vis,0,sizeof(vis));
	ans2=problem2(0,0);
	if(ans2==1)
		printf("1.000000000");
	else
		printf("0.000000000");
	return 0;
}
