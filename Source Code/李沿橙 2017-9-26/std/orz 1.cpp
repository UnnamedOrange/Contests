#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
char ch;
bool ok;
void read(int &x)
{
	for (ok=0,ch=getchar(); !isdigit(ch); ch=getchar()) if (ch=='-') ok=1;
	for (x=0; isdigit(ch); x=x*10+ch-'0',ch=getchar());
	if (ok) x=-x;
}
const int maxn=500005;
const int inf=0x3f3f3f3f;
typedef long long int64;
int n,k,A[maxn],B[maxn];
int64 ans;
struct Data
{
	int posa,posb;
} tmp;
Data operator+(const Data &a,const Data &b)
{
	return A[a.posa]+B[a.posb]<A[b.posa]+B[b.posb]?a:b;
}
struct Node
{
	Data case1,case2,case3;
	int min1a,min1b,min2a,min2b,minv;
};
Node operator+(const Node &a,const Node &b)
{
	Node c;
	c.case1=a.case1+b.case1+(Data)
	{
		a.min1a,b.min1b
	};
	c.case3=a.case3+b.case3+(Data)
	{
		b.min1a,a.min1b
	};
	c.min1a=A[a.min1a]<A[b.min1a]?a.min1a:b.min1a;
	c.min1b=B[a.min1b]<B[b.min1b]?a.min1b:b.min1b;
	if (a.minv<b.minv)
	{
		c.case2=a.case2+b.case3+(Data)
		{
			b.min1a,a.min2b
		};
		c.min2a=a.min2a;
		c.min2b=B[a.min2b]<B[b.min1b]?a.min2b:b.min1b;
	}
	else if (a.minv>b.minv)
	{
		c.case2=a.case3+b.case2+(Data)
		{
			b.min2a,a.min1b
		};
		c.min2a=A[a.min1a]<A[b.min2a]?a.min1a:b.min2a;
		c.min2b=b.min2b;
	}
	else
	{
		c.case2=a.case2+b.case2+(Data)
		{
			b.min2a,a.min2b
		};
		c.min2a=a.min2a;
		c.min2b=b.min2b;
	}
	c.minv=min(a.minv,b.minv);
	return c;
}
struct seg
{
#define ls k<<1
#define rs (k<<1)+1
	Node node[maxn<<2];
	int tag[maxn<<2];
	void addtag(int k,int v)
	{
		tag[k]+=v,node[k].minv+=v;
	}
	void update(int k)
	{
		node[k]=node[ls]+node[rs];
	}
	void pushdown(int k)
	{
		if (tag[k])
		{
			addtag(ls,tag[k]),addtag(rs,tag[k]),tag[k]=0;
		}
	}
	void build(int k,int l,int r)
	{
		if (l==r)
		{
			node[k]=(Node)
			{
				(Data) {l,l},(Data) {0,0},(Data) {l,l},l,l,l,0,0
			};
			return;
		}
		int m=(l+r)>>1;
		build(ls,l,m),build(rs,m+1,r),update(k);
	}
	void modify_s(int k,int l,int r,int x,int y,int v)
	{
		if (l==x&&r==y)
		{
			addtag(k,v);
			return;
		}
		int m=(l+r)>>1;
		pushdown(k);
		if (y<=m) modify_s(ls,l,m,x,y,v);
		else if (x<=m) modify_s(ls,l,m,x,m,v),modify_s(rs,m+1,r,m+1,y,v);
		else modify_s(rs,m+1,r,x,y,v);
		update(k);
	}
	void modify(int k,int l,int r,int x)
	{
		if (l==r) return;
		int m=(l+r)>>1;
		pushdown(k);
		if (x<=m) modify(ls,l,m,x);
		else modify(rs,m+1,r,x);
		update(k);
	}
} T;
int main()
{
	freopen("orz.in","r",stdin),freopen("orz.out","w",stdout);
	read(n),read(k),A[0]=B[0]=inf;
	for (int i=1; i<=n; i++) read(A[i]);
	for (int i=1; i<=n; i++) read(B[i]);
	T.build(1,1,n);
	while (k--)
	{
		tmp=T.node[1].case1+T.node[1].case2;
		int x=tmp.posa,y=tmp.posb;
		ans+=A[x]+B[y];
		if (x<y) T.modify_s(1,1,n,x,y-1,1);
		if (y<x) T.modify_s(1,1,n,y,x-1,-1);
		A[x]=B[y]=inf,T.modify(1,1,n,x),T.modify(1,1,n,y);
	}
	printf("%lld\n",ans);
	return 0;
}
