#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
struct edge
{
	int t,n,l;
}e[33*33];
int h[33];
int tot;
void adde(int u,int v,int l)
{
	tot++;
	e[tot].t=v;
	e[tot].l=l;
	e[tot].n=h[u];
	h[u]=tot;
	return;
}
int d[33];
bool inq[33];
bool spfa() 
{
	int i;
	queue<int> Q;
	for(i=0;i<=24;i++)
	{
		d[i]=-1e9;
		inq[i]=0;
	}
	d[0]=0;
	inq[0]=1;
	Q.push(0);
	while (Q.empty()==0) 
	{
		int u=Q.front();
		Q.pop();
		inq[u]=0;
		if (d[u]>1000) return 0;
		for (i=h[u];i;i=e[i].n)
		{
			int v=e[i].t,l=e[i].l;
			if (d[v]<d[u]+l)
			{
				d[v]=d[u]+l;
				if (inq[v]==0)
				{
					inq[v]=1;
					Q.push(v);
				}
			}
		}
	}
	return 1;
}
int a[30],b[30];
bool solve(int ans) 
{
	int i;
	for (i=0;i<=24;i++)h[i]=0;
	tot=0;
	for (i=9;i<=24;i++) adde(i-8,i,a[i]);
	for (i=1;i<=8;i++) adde(i+16,i,a[i]-ans);
	for (i=1;i<=24;i++) adde(i-1,i,0);
	for (i=1;i<=24;i++) adde(i,i-1,-b[i]);
	adde(0,24,ans);
	adde(24,0,-ans);
	return spfa();
}
int main(int argc, char ** argv)
{
	freopen("cashier.in", "r", stdin);freopen("cashier.out", "w", stdout);
	int test,i;
	scanf("%d",&test);
	for(i=1;i<=test;i++)
	{
		for (i=1;i<=24;i++)scanf("%d", &a[i]);
		for (i=1;i<=24;i++)scanf("%d", &b[i]);
		int ans=0;
		while(1) 
		{
			if(++ans>1000) 
			{
				ans=-1;
				break;
			}
			if(solve(ans))break;
		}
		printf("%d\n",ans);
	}
	return 0;
}
