#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXN 50005
#define MOD 1000000007
int n,m;
int k;
long long ans=0;
int w[MAXN];
int f[MAXN];
using namespace std;

void dfs(int x,int l,int r,int last)
{
	if(x==k)
	{
		long long tot=1;
		for(int i=l;i<=r;i++)
		{
			if(f[i]==1) tot=(tot*w[i])%MOD;
		}
		ans+=tot;
		while(ans<0) ans+=MOD;
		while(ans>=MOD) ans-=MOD;
	}
	for(int i=last+1;i<=r;i++)
	{
		if(f[i]==1) continue;
		f[i]=1;
		dfs(x+1,l,r,i);
		f[i]=0;
	}
}

int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(int i=1;i<=m;i++)
	{
		int opt;
		scanf("%d",&opt);
		if(opt==1)
		{
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			for(int j=a;j<=b;j++)
			{
				w[j]+=c;
			}
		}
		else if(opt==2)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			for(int j=a;j<=b;j++)
			{
				w[j]=-w[j];
			}
		}
		else if(opt==3)
		{
			for(int j=1;j<=n;j++) f[j]=0;
			int a,b;
			scanf("%d%d%d",&a,&b,&k);
			ans=0;
			dfs(0,a,b,a-1);
			printf("%lld\n",ans);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
