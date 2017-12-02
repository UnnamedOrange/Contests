#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 30000
using namespace std;
typedef long long ll;
struct node
{
	ll sum;
	bool lazy;
	int lazy2;
}t[N*4+5];
void tag(int,int,int,int);
void pud(int x,int l,int r)
{
	int mid=(r+l)>>1;
	if(t[x].lazy)
	{
	t[x].lazy=0;
	tag(0,l,mid,x<<1);tag(0,mid+1,r,x<<1|1);
	}
	if(t[x].lazy2)
	{
	tag(t[x].lazy2,l,mid,x<<1);tag(t[x].lazy2,mid+1,r,x<<1|1);
	t[x].lazy2=0;
	}
}
void tag(int x,int l,int r,int pos)
{
	if(x==0)
	{
		t[pos].lazy2=0;t[pos].lazy=1;
		t[pos].sum=0;
	}
	else
	{
		t[pos].lazy2+=x;t[pos].sum+=1ll*x*(r-l+1);
	}
}
void make(int pos,int l,int r,int le,int ri)
{
	if(le<=l&&r<=ri){tag(1,l,r,pos);return;}
	pud(pos,l,r);
	int mid=(l+r)>>1;
	if(ri<=mid)make(pos<<1,l,mid,le,ri);
	else if(le>mid)make(pos<<1|1,mid+1,r,le,ri);
	else
	{
		make(pos<<1,l,mid,le,ri);make(pos<<1|1,mid+1,r,le,ri);
	}
	t[pos].sum=t[pos<<1].sum+t[pos<<1|1].sum;
}
void del(int pos,int l,int r,int le,int ri)
{
	if(le<=l&&r<=ri){tag(0,l,r,pos);return;}
	pud(pos,l,r);
	int mid=(l+r)>>1;
	if(ri<=mid)del(pos<<1,l,mid,le,ri);
	else if(le>mid)del(pos<<1|1,mid+1,r,le,ri);
	else
	{
		del(pos<<1,l,mid,le,ri);del(pos<<1|1,mid+1,r,le,ri);
	}
	t[pos].sum=t[pos<<1].sum+t[pos<<1|1].sum;
}
int Sum(int pos,int l,int r,int le,int ri)
{
	if(le<=l&&r<=ri){return t[pos].sum;}
	pud(pos,l,r);
	int mid=(l+r)>>1;
	if(ri<=mid)return Sum(pos<<1,l,mid,le,ri);
	else if(le>mid)return Sum(pos<<1|1,mid+1,r,le,ri);
	else
	{
		return Sum(pos<<1,l,mid,le,ri)+Sum(pos<<1|1,mid+1,r,le,ri);
	}
}
vector<int>ques[30005];
vector<int>pis[30005];
struct edge
{
	int to,dis;
}d[30005];
int head[30005],cnt;
void add(int u,int v,int dis)
{
	cnt++;
	d[cnt].to=v;
	d[cnt].dis=dis;
	head[u]=cnt;
}
int c[30005],a[30005];
int find(int x)
{
	if(c[x]!=x)c[x]=find(c[x]);
	return c[x];
}
int p;
int ans[30005];
void dfs(int x)
{
	int nx=head[x];
	if(nx)
	{
	dfs(d[nx].to);
	make(1,1,30000,d[nx].dis,30000);
	}
	int len=ques[x].size();
	for(int i=0;i<len;++i)ans[pis[x][i]]=Sum(1,1,30000,ques[x][i],ques[x][i]);
	if(nx&&d[nx].dis>1)
	del(1,1,30000,1,d[nx].dis-1);
}
int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	for(int i=1;i<=30000;++i)c[i]=a[i]=i;
	scanf("%d",&p);
	int kik=0;
	char s[3];
	for(int i=1;i<=p;++i)
	{
		scanf("%s",s);
		if(s[0]=='M')
		{
			int t1,t2;
			scanf("%d%d",&t1,&t2);
			t1=find(t1);t2=find(t2);
			add(a[t1],t2,i);
			int t3,t4;
			t3=a[t1];t4=a[t2];
			c[t2]=t1;a[t1]=t4;
		}
		else 
		{
			kik++;
			int t1;
			scanf("%d",&t1);
			ques[t1].push_back(i);
			pis[t1].push_back(kik);
		}
	}
	for(int i=1;i<=30000;++i)
	if(find(i)==i)
	{
		dfs(i);
		del(1,1,30000,1,30000);
	}
	for(int i=1;i<=kik;++i)
	{
		printf("%d\n",ans[i]);
	}		
	return 0;
}
