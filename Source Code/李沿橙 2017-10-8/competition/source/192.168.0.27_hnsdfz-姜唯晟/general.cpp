#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXN 100005
int n,k,t,ans=0;
int h[MAXN],f[MAXN];
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

void dfs(int x,int fa)
{
	for(int i=h[x];i;i=e[i].next)
	{
		if(e[i].to==fa) continue;
		dfs(e[i].to,x);
	}
	if(f[x]==0)
	{
		ans++;
		for(int i=h[fa];i;i=e[i].next)
		{
			f[e[i].to]=1;
		}
	}
}

void work1()
{
	ans=0;
	dfs(1,0);
	printf("%d\n",ans);
}

int main()
{
	freopen("general.in","r",stdin);
	freopen("general.out","w",stdout);
	scanf("%d%d%d",&n,&k,&t);
	for(int i=1;i<=n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		ADDE(u,v);
		ADDE(v,u);
	}
	if(k==0) printf("%d\n",n);
	else if(k==1)
	{
		work1();
	}
	else
	{
		printf("%d\n",n/k);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
