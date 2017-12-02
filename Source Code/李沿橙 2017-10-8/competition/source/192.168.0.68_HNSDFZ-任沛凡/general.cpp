#include<queue>
#include<cstdio>
#define maxn 200010
#define maxm 400010
using namespace std;
struct data
{
	int x,d;
	bool operator < (const data &b) const
	{
		return d<b.d;
	}
}u;
int to[maxm],nxt[maxm],first[maxn];
int d[maxn],dis[maxn],fa[maxn];
bool vis[maxn],ban[maxm];
int n,k,t,sum,cnt=1;
priority_queue<data> q;
void add(int x,int y)
{
	d[x]++;
	to[++cnt]=y;
	nxt[cnt]=first[x];
	first[x]=cnt;
}
void pre(int x)
{
	if(d[x]==1)
	{
		u.x=x;
		u.d=dis[x];
		q.push(u);
	}
	for(int i=first[x];i;i=nxt[i])
	{
		int v=to[i];
		if(v!=fa[x])
		{
			fa[v]=x;
			dis[v]=dis[x]+1;
			pre(v);
		}
	}
}
void dfs(int x,int y)
{
	vis[x]=1;
	if(y==0)
	{
		if(d[x]==1)
		for(int i=first[x];i;i=nxt[i])
		{
			if(ban[i])
			continue;
			int v=to[i];
			d[x]--;
			d[v]--;
			ban[i]=ban[i^1]=1;
			if(x==fa[v])
			fa[v]=v;
			if(d[v]==1)
			{
				u.x=v;
				u.d=dis[v];
				q.push(u);
			}
		}
		return;
	}
	for(int i=first[x];i;i=nxt[i])
	{
		if(ban[i])
		continue;
		int v=to[i];
		d[x]--;
		d[v]--;
		ban[i]=ban[i^1]=1;
		dfs(v,y-1);
	}
}
int main()
{
	freopen("general.in","r",stdin);
	freopen("general.out","w",stdout);
	int x,y;
	scanf("%d%d%d",&n,&k,&t);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	fa[1]=1;
	pre(1);
	while(!q.empty())
	{
		u=q.top();
		q.pop();
		x=u.x;
		if(vis[x])
		continue;
		y=k;
		while(y--&&x!=fa[x])
		x=fa[x];
		dfs(x,k);
		sum++;
	}
	printf("%d\n",sum);
	return 0;
}
