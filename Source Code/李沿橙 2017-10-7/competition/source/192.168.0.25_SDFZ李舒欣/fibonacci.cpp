#include<bits/stdc++.h>
using namespace std;
#define maxn 202000
queue<int>q;
stack<int>s;
int head[maxn],q2,q1,m,top=1,cnp=1,a1,b1,ans,r[maxn],st[maxn][5],point[maxn],head2[maxn],mon[17],dep[maxn],ra[maxn],index[maxn];
int fib[30]={1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946};
int read()
{
	int x=0;
	char c;
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
struct xxx
{
	int to,num,co,last;
}a[maxn],b[maxn];
void add(int u,int v)
{
	a[cnp].to=v;
	a[cnp].last=head[u];
	head[u]=cnp++;
}
void add2(int u,int v)
{
	ra[v]=fib[r[v]-1]+(++mon[r[v]]);
	b[cnp].to=ra[v];
	b[cnp].last=head2[u];
	head2[u]=cnp++;
}
int dfsp(int g)//建立兔子图&&&出生月份 
{
	int u=r[g];
	for(int i=1;i<=m-u-1;i++)
	{
		r[++top]=u+i+1;
		add(g,top);
		dfsp(top);
	}
}
void bfs()//建立兔子图&&&正式编号 
{
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i!=-1;i=a[i].last)
		{
			add2(ra[x],a[i].to);
			s.push(a[i].to);
		}
		while(!s.empty())
		{
			q.push(s.top());
			s.pop();
		}
	}
}
void dfs(int u,int last)//建立st图预处理dfs 
{
	index[++top]=u;
	for(int i=head2[u];i!=-1;i=b[i].last)
	{
		int e=b[i].to;
		if(e!=last)
		{
			dep[e]=dep[u]+1;
			dfs(e,u);
			index[++top]=u;
		}
	}
	if(!point[u])point[u]=top;
}
int RMQ()
{
	int t=log(top+0.0)/log(2.0);
	for(int i=1;i<=top;i++)st[i][0]=index[i];
	for(int j=1;j<t;j++)
		for(int i=1;(i+1<<(j-1))<=top+1;i++)
			st[i][j]=min(st[i][j-1],st[i+1<<(j-1)][j-1]);
}
int main()
{
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	q1=read();
	m=8;
	memset(head,-1,sizeof(head));
	r[1]=0;
	dfsp(1);
	q.push(1);
	ra[1]=1;
	top=0,cnp=1;
	memset(head2,-1,sizeof(head));
	bfs();
	top=0;
	dfs(1,0);
	RMQ();
	for(int i=1;i<=q1;i++)
	{
		a1=read();
		b1=read();
		a1=point[a1],b1=point[b1];
		if(a1>b1)swap(a1,b1);
		int k=log(b1-a1+1);
		if(k>=1)
		{
			ans=min(st[a1][k-1],st[a1+(1<<k)-1][k-1]);
			if(ans)printf("%d\n",ans);
			else printf("1\n");
		}
		else 
		{
			if(k==0)ans=min(st[a1][0],st[b1][0]);
			printf("%d\n",ans);
		}
	}
	return 0;
}
