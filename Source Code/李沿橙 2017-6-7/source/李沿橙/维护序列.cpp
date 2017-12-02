#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;

inline int readIn()
{
	int a;
	scanf("%d",&a);
	return a;
}

const int maxn=262150;
int n,m;
int mod;
long long tree[maxn];
struct handle
{
	long long mul;
	long long add;
	handle():mul(1),add(0)
	{

	}
} lazy[maxn];

namespace Regular
{
	void build(int node=1, int l=1, int r=n)
	{
		if(l==r)
		{
			tree[node]=readIn()%mod;
			return;
		}
		int mid=(l+r)/2;
		build(node<<1, l, mid);
		build((node<<1)+1, mid+1, r);
		tree[node]=(tree[node<<1]+tree[(node<<1)+1])%mod;
	}

	int g_L,g_R,g_Var;

	void pushDown(int node, int l, int r)
	{
		int lc=node<<1;
		int rc=(node<<1)+1;
		int mid=(l+r)/2;
		if(lazy[node].mul!=-1)
		{
			tree[lc]=(tree[lc] % mod) * (lazy[node].mul % mod) % mod;
			if(lazy[lc].mul == -1) lazy[lc].mul=lazy[node].mul % mod;
			else lazy[lc].mul=(lazy[lc].mul % mod) * (lazy[node].mul % mod) % mod;
			if(lazy[lc].add != -1) lazy[lc].add=(lazy[node].mul % mod) * (lazy[lc].add % mod) % mod;

			tree[rc]=(tree[rc] % mod) * (lazy[node].mul % mod) % mod;
			if(lazy[rc].mul == -1) lazy[rc].mul=lazy[node].mul % mod;
			else lazy[rc].mul=(lazy[rc].mul % mod) * (lazy[node].mul % mod) % mod;
			if(lazy[rc].add != -1) lazy[rc].add=(lazy[node].mul % mod) * (lazy[rc].add % mod) % mod;

			lazy[node].mul = -1;
		}
		if(lazy[node].add!=-1)
		{
			tree[lc] = (tree[lc] % mod + lazy[node].add * (mid-l+1) % mod) % mod;
			if(lazy[lc].add == -1) lazy[lc].add=lazy[node].add % mod;
			else lazy[lc].add=(lazy[lc].add % mod + lazy[node].add % mod) % mod;

			tree[rc] = (tree[rc] % mod + lazy[node].add * (r-mid) % mod) % mod;
			if(lazy[rc].add == -1) lazy[rc].add=lazy[node].add % mod;
			else lazy[rc].add=(lazy[rc].add % mod + lazy[node].add % mod) % mod;

			lazy[node].add = -1;
		}
	}

	int sum(int node=1, int l=1, int r=n)
	{
		if(g_L<=l && r<=g_R)
		{
			return tree[node] % mod;
		}
		pushDown(node, l, r);
		int lc=node<<1;
		int rc=(node<<1)+1;
		int mid=(l+r)/2;
		int ans=0;
		if(g_L <= mid) ans+=sum(lc, l, mid);
		if(g_R > mid) ans+=sum(rc, mid+1, r);
		return ans % mod;
	}

	void add(int node=1, int l=1, int r=n)
	{
		if(g_L<=l && r<=g_R)
		{
			tree[node]=(tree[node] % mod + g_Var * (r-l+1) % mod) % mod;
			if(lazy[node].add == -1) lazy[node].add = g_Var;
			else lazy[node].add = (lazy[node].add % mod + g_Var) % mod;
			return;
		}
		pushDown(node, l, r);
		int lc=node<<1;
		int rc=(node<<1)+1;
		int mid=(l+r)/2;
		if(g_L <= mid) add(lc, l, mid);
		if(g_R > mid) add(rc, mid+1, r);
		tree[node]=(tree[lc]+tree[rc])%mod;
	}
	void mul(int node=1, int l=1, int r=n)
	{
		if(g_L<=l && r<=g_R)
		{
			tree[node]=tree[node] % mod * g_Var % mod;
			if(lazy[node].mul == -1) lazy[node].mul = g_Var;
			else lazy[node].mul = lazy[node].mul % mod * g_Var % mod;
			if(lazy[node].add != -1) lazy[node].add = (lazy[node].add % mod) * g_Var % mod;
			return;
		}
		pushDown(node, l, r);
		int lc=node<<1;
		int rc=(node<<1)+1;
		int mid=(l+r)/2;
		if(g_L <= mid) mul(lc, l, mid);
		if(g_R > mid) mul(rc, mid+1, r);
		tree[node]=(tree[lc]+tree[rc])%mod;
	}

	enum
	{
	    MUL=1,
	    ADD,
	    SUM
	};
	void run()
	{
		while(m--)
		{
			int ins=readIn();
			if(ins==MUL)
			{
				g_L=readIn();
				g_R=readIn();
				g_Var=readIn() % mod;
				mul();
			}
			else if(ins==ADD)
			{
				g_L=readIn();
				g_R=readIn();
				g_Var=readIn() % mod;
				add();
			}
			else if(ins==SUM)
			{
				g_L=readIn();
				g_R=readIn();
				printf("%d\n",sum());
			}
		}
	}
	void input()
	{
		n=readIn();
		mod=readIn();
		build();
		m=readIn();
	}
}

namespace Violent
{
	void run()
	{

	}
	void input()
	{
		
	}
}

int main()
{
	Regular::input();
	Regular::run();
	return 0;
}
