#include<bits/stdc++.h>
using namespace std;
int ans=0,cnp=1,n,maxx,k,m,u,v,yes=0,mark[1000][1000],vis[10000],degree[10000],head[1000];
queue<int>q,q2;
struct xxx
{
	int u,to,last;
}a[100000];
int read()
{
	char c;
	int x=0,w=1;
	c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
void init()
{
	for(int i=1;i<=n;i++)head[i]=-1,degree[i]=0;
	while(!q.empty())q.pop();
	cnp=1;
}
void add(int u,int v)
{
	a[cnp].last=head[u];
	a[cnp].u=u;
	a[cnp].to=v;
	head[u]=cnp++;
}
void kahn()
{
	while(!q.empty())
	{
		int x=q.front();
		ans++;
		vis[x]=1;
		maxx=0;
		q.pop();
		for(int i=head[x];i!=-1;i=a[i].last)
		{
			int y=a[i].to;
			degree[x]--;
			degree[y]--;
			if(degree[y]>0)q2.push(y);
		}
		for(int i=1;i<=n;i++)if(degree[i]>maxx)maxx=degree[i];
		if(maxx==0)return;
		for(int i=1;i<=n;i++)if(degree[i]==maxx)q.push(i);
	}
}
int main()
{
	freopen("ping.in","r",stdin);
	freopen("ping.out","w",stdout);
	n=read(),k=read();
	init();
	for(int i=1;i<=k;i++)
	{
		int x=read();
		int y=read();
		add(x,y);
		add(y,x);
		degree[x]++;
		degree[y]++;
	}
	m=read();
	for(int i=1;i<=m;i++)
	{
		u=read();
		v=read();
	}
	for(int i=1;i<=n;i++)if(degree[i]>maxx)maxx=degree[i];
	for(int i=1;i<=n;i++)if(degree[i]==maxx)q.push(i);
	kahn();
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)if(vis[i])cout<<i<<" ";
	cout<<endl;
	return 0;
}
