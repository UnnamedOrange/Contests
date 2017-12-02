#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXN 100005
#define MAXK 300005
int n,m;
int fff=0;
int ans[MAXN];
int k;
int h[MAXN],f[MAXN];
int dep[MAXN],fa[MAXN];
int x[MAXK],y[MAXK];
int tmp[MAXN];
using namespace std;

struct EDGE
{
	int to;
	int next;
}e[MAXN*2];

int cnt=0;
void ADDE(int from,int to)
{
	cnt++;
	e[cnt].to=to;
	e[cnt].next=h[from];
	h[from]=cnt;
}

void dfs(int p,int fat)
{
	fa[p]=fat;
	for(int i=h[p];i;i=e[i].next)
	{
		if(e[i].to==fat) continue;
		dep[e[i].to]=dep[p]+1;
		dfs(e[i].to,p);
	}
}

int ck(int num)
{
	for(int i=1;i<=num;i++)
	{
		f[i]=0;
	}
	for(int i=1;i<=num;i++)
	{
		f[tmp[i]]=1;
	}
	for(int i=1;i<=k;i++)
	{
		int ffff=0;
		int tmpx=x[i],tmpy=y[i];
		if(dep[tmpx]<dep[tmpy]) swap(tmpx,tmpy);
		while(dep[tmpx]!=dep[tmpy])
		{
			if(f[tmpx]==1) ffff=1;
			tmpx=fa[tmpx];
		}
		while(tmpx!=tmpy)
		{
			if(f[tmpx]==1 || f[tmpy]==1) ffff=1;
			tmpx=fa[tmpx];
			tmpy=fa[tmpy];
		}
		if(f[tmpx]==1) ffff=1;
		if(ffff==0) return 0;
	}
	return 1;
}

void dfs(int tot,int last,int now)
{
	if(now==tot+1)
	{
		if(ck(tot))
		{
			fff=1;
			for(int i=1;i<=tot;i++)
			{
				ans[i]=tmp[i];
			}
		}
		return ;
	}
	for(int i=last+1;i<=n;i++)
	{
		tmp[now]=i;
		dfs(tot,i,now+1);
		tmp[now]=0;
		if(fff==1) return ;
	}
}

int main()
{
	freopen("ping.in","r",stdin);
	freopen("ping.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		ADDE(u,v);
		ADDE(v,u);
	}
	dep[1]=1;
	dfs(1,0);
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
	}
	for(int i=1;i<=n;i++)
	{
		dfs(i,0,1);
		if(fff==1)
		{
			printf("%d\n",i);
			for(int j=1;j<=i;j++)
			{
				printf("%d ",ans[j]);
			}
			printf("\n");
			break;
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
