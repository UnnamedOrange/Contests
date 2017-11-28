#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1

const int maxn=50010;
const int INF=0x3f3f3f3f;

int n,m,en,cnt,depth[maxn],l[maxn],r[maxn],col[maxn<<2|1],count[maxn<<2|1],s[maxn];

long long sumd[maxn<<2|1],sum[maxn<<2|1];

struct edge
{
	int e;
	edge *next;
}*v[maxn],ed[maxn],*se[maxn];

void add_edge(int s,int e)
{
	en++;
	ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;
}

void dfs()
{
	int size=1;
	s[1]=1;
	se[1]=v[1];
	l[1]=1;
	cnt++;
	for (;size;)
	{
		if (!se[size])
		{
			r[s[size]]=cnt;
			size--;
		}
		else
		{
			s[size+1]=se[size]->e;
			depth[s[size+1]]=depth[s[size]]+1;
			l[s[size+1]]=++cnt;
			se[size+1]=v[se[size]->e];
			se[size]=se[size]->next;
			size++;
		}
	}
}

void update(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void push_col(int l,int r,int rt)
{
	if (count[rt])
	{
		col[rt<<1]+=col[rt];col[rt<<1|1]+=col[rt];
		count[rt<<1]+=count[rt];count[rt<<1|1]+=count[rt];
		int m=(l+r)>>1;
		sum[rt<<1]+=(long long)col[rt]*(m-l+1)+sumd[rt<<1]*count[rt];
		sum[rt<<1|1]+=(long long)col[rt]*(r-m)+sumd[rt<<1|1]*count[rt];
		count[rt]=0;col[rt]=0;
	}
}

void changetree(int l,int r,int rt,int p,int delta)
{
	if (l==r)
	{
		sumd[rt]+=delta;
		return;
	}
	int m=(l+r)>>1;
	if (p<=m) changetree(lson,p,delta);
	else changetree(rson,p,delta);
	sumd[rt]=sumd[rt<<1]+sumd[rt<<1|1];
}

void modify(int l,int r,int rt,int nowl,int nowr,int delta)
{
	if (nowl<=l && r<=nowr)
	{
		col[rt]+=delta;
		count[rt]++;
		sum[rt]+=(long long)delta*(r-l+1)+sumd[rt];
		return;
	}
	push_col(l,r,rt);
	int m=(l+r)>>1;
	if (nowl<=m) modify(lson,nowl,nowr,delta);
	if (m<nowr) modify(rson,nowl,nowr,delta);
	update(rt);
}

long long query(int l,int r,int rt,int nowl,int nowr)
{
	if (nowl<=l && r<=nowr) return sum[rt];
	push_col(l,r,rt);
	int m=(l+r)>>1;
	if (nowl<=m)
	{
		if (m<nowr) return query(lson,nowl,nowr)+query(rson,nowl,nowr);
		else return query(lson,nowl,nowr);
	}
	else return query(rson,nowl,nowr);
}

int main()
{
	freopen("truetears.in","r",stdin);
	freopen("truetears.out","w",stdout);

	scanf("%d%d",&n,&m);
	for (int a=2;a<=n;a++)
	{
		int id;
		scanf("%d",&id);
		add_edge(id,a);
	}
	dfs();
	for (int a=1;a<=n;a++)
		changetree(1,n,1,l[a],depth[a]);
	char s[3];
	for (;m--;)
	{
		scanf("%s",s);
		if (s[0]=='Q')
		{
			int id;
			scanf("%d",&id);
			printf(LL "\n",query(1,n,1,l[id],r[id]));
		}
		else
		{
			int p,delta;
			scanf("%d%d",&p,&delta);
			delta-=depth[p];
			modify(1,n,1,l[p],r[p],delta);
		}
	}

	return 0;
}
