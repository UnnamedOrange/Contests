#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXN 1005
#define MOD 1000000007
int n;
int a[MAXN];
int h[MAXN],f[MAXN],fa[MAXN];
int dep[MAXN],ans[MAXN];
using namespace std;

struct EDGE
{
	int to;
	int next;
	int f;
}e[MAXN*2];

int cnt=0;
void ADDE(int from,int to)
{
	cnt++;
	e[cnt].to=to;
	e[cnt].next=h[from];
	h[from]=cnt;
}

void dfs(int x,int fat)
{
	f[x]=1;
	fa[x]=fat;
	for(int i=h[x];i;i=e[i].next)
	{
		if(f[e[i].to]==1 || e[i].to==fat || e[i].f==1) continue;
		dep[e[i].to]=dep[x]+1;
		dfs(e[i].to,x);
	}
}

int get_fa(int x)
{
	if(fa[x]!=x) return get_fa(fa[x]);
}

int get_dis(int x,int y)
{
	int dis=0;
	int tmpx=x,tmpy=y;
	if(dep[tmpx]<dep[tmpy]) swap(tmpx,tmpy);
	while(dep[tmpx]!=dep[tmpy])
	{
		dis+=a[tmpx];
		tmpx=fa[tmpx];
	}
	while(tmpx!=tmpy)
	{
		dis+=a[tmpx];
		tmpx=fa[tmpx];
		dis+=a[tmpy];
		tmpy=fa[tmpy];
	}
	dis+=a[tmpx];
	return dis;
}

void work()
{
	for(int i=1;i<=n;i++)
	{
		f[i]=0;
		ans[i]=0;
	}
	for(int i=1;i<=n;i++)
	{
		if(f[i]==0)
		{
			dep[i]=1;
			dfs(i,i);
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			int treeh=get_fa(i);
			if(treeh!=get_fa(j)) continue;
			int dis=get_dis(i,j);
			if(dis>ans[treeh]) ans[treeh]=dis;
		}
	}
	long long totans=1;
	for(int i=1;i<=n;i++)
	{
		if(ans[i]!=0)
		{
			totans*=ans[i];
			totans%=MOD;
		}
	}
	printf("%lld\n",totans);
}

int main()
{
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n-1;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		ADDE(u,v);
		ADDE(v,u);
	}
	work();
	for(int i=1;i<=n-1;i++)
	{
		int x;
		scanf("%d",&x);
		e[x*2].f=1;
		e[x*2-1].f=1;
		work();
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
