#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXN 305
int n;
int cnt1=0,cntans1=0;
double ans1=0,ans2=0;
int a[MAXN],tmp[MAXN],f[MAXN];
using namespace std;

int gcd(int x,int y)
{
	if(x==0) return y;
	if(y==0) return x;
	return x%y==0?y:gcd(y,x%y);
}

int ck()
{
	int GCD=0;
	for(int i=1;i<=n;i++)
	{
		GCD=gcd(tmp[i],GCD);
		if(GCD==1)
		{
			if(i%2==1) return 0;
			else return 1;
		}
	}
	if(n%2==1) return 1;
	else return 0;
}

void dfs(int t)
{
	if(t==n+1)
	{
		cnt1++;
		if(ck()) cntans1++;
		return ;
	}
	for(int i=1;i<=n;i++)
	{
		if(f[i]==1) continue;
		f[i]=1;
		tmp[t]=a[i];
		dfs(t+1);
		tmp[t]=0;
		f[i]=0;
	}
}

int main()
{
	freopen("cards.in","r",stdin);
	freopen("cards.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	dfs(1);
	ans1=(double)cntans1/(double)cnt1;
	printf("%.9lf %.9lf",ans1,ans2);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
