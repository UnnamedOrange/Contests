#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define MAXA 1010
using namespace std;
int cnt,n;
inline int gcd(int a,int b)
{
	return a?gcd(b%a,a):b;
}
int a[N],g[MAXA][MAXA];double ans;
bool used[N];
bool dfs(int d,int res,double p)
{
	bool w=false;
	for(int i=1;i<=n;i++)
		if(!used[i])
		{
			int e=g[d][a[i]],f=true;
			p/=res;used[i]=true;
			if(e==1) ans+=p*(n-res&1);
			else f=dfs(e,res-1,p);
			if(!f) w=true;
			p*=res;used[i]=false;
		}
	return w;
}
int main()
{
	freopen("cards.in","r",stdin);
	freopen("cards.out","w",stdout);
	scanf("%d",&n);int MaxA=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		MaxA=max(MaxA,a[i]);
	for(int i=0;i<=MaxA;i++)
		for(int j=0;j<=MaxA;j++)
			g[i][j]=gcd(i,j);
	int d=0;
	for(int i=1;i<=n;i++)
		d=g[d][a[i]];
	if(d>1) return !printf("%d.00000000 %d.00000000",n&1,n&1);
	else if(n<=10){
		bool x=dfs(0,n,1.0);
		printf("%.8llf %d.00000000",ans,x);
	}
	else printf("0.000000 0.000000\n");
	return 0;
}
