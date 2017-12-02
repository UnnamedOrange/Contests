#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN=100000;

#define x first
#define y second
#define mp make_pair
#define pii pair<int,int>

#define debug(...) fprintf(stderr,__VA_ARGS__)

pii operator + (pii A,pii B) { return mp(A.x+B.x,A.y+B.y); }

int read()
{
	int ret=0;
	char c=getchar();

	while (c<'0' || c>'9') c=getchar();

	while (c>='0' && c<='9') {
		ret=ret*10+c-'0'; c=getchar(); }

	return ret;
}

pii front[MAXN+10];
int orderx[MAXN+10],stdx[MAXN+10];

int sta[MAXN+10],end[MAXN+10];

pii b[(MAXN<<1)+10];

struct Tree
{
	int root;

	int ls[(MAXN<<1)+10],rs[(MAXN<<1)+10],fa[(MAXN<<1)+10];

	int sz[(MAXN<<1)+10];
	
	pii ans[(MAXN<<1)+10];

	void update(int x)
	{
		ans[x]=b[x]+ans[ls[x]]+ans[rs[x]];
		sz[x]=1+sz[ls[x]]+sz[rs[x]];
		return ;
	}

	void turnleft(int x)
	{
		int r=rs[x],rl=ls[r],f=fa[x];

		if (f) {
			if (ls[f]==x) ls[f]=r; else rs[f]=r;
			fa[r]=f; }
		else {
			root=r; fa[r]=0; }

		fa[x]=r; ls[r]=x;
		rs[x]=rl; if (rl) fa[rl]=x;

		update(x);
		return ;
	}

	void turnright(int x)
	{
		int l=ls[x],lr=rs[l],f=fa[x];

		if (f) {
			if (ls[f]==x) ls[f]=l; else rs[f]=l;
			fa[l]=f; }
		else {
			root=l; fa[l]=0; }

		fa[x]=l; rs[l]=x;
		ls[x]=lr; if (lr) fa[lr]=x;

		update(x);
	}

	void splay(int x,int top)
	{
		while (fa[x]!=top) {
			int f=fa[x];

			if (ls[f]==x) turnright(f);
			else turnleft(f); }

		update(x);
		return ;
	}

	int order(int x)
	{
		int ret=sz[ls[x]]+1;

		while (fa[x]) {
			if (rs[fa[x]]==x) ret+=sz[ls[fa[x]]]+1;
			x=fa[x]; }

		return ret;
	}

	int find(int x)
	{
		int now=root;

		while (true) {
			if (sz[ls[now]]+1<x) {
				x-=sz[ls[now]]+1; now=rs[now]; }
			else if (sz[ls[now]]+1==x) return now;
			else now=ls[now];	}
	}

	int build(int l,int r)
	{
		if (l>r) return 0;

		int mid=(l+r)>>1;
		ls[mid]=build(l,mid-1); fa[ls[mid]]=mid;
		rs[mid]=build(mid+1,r); fa[rs[mid]]=mid;

		update(mid);
		return mid;
	}
}tr;

int n,m;

void sortx()
{
	static int num[MAXN+10];
	memset(num,0,sizeof(num));

	for (int i=1;i<=m;i++) num[front[i].x]++;
	for (int i=1;i<=n;i++) stdx[i]=num[i]+=num[i-1];
	for (int i=1;i<=m;i++) orderx[++num[front[i].x-1]]=i;

	return ;
}

int Time=0;

void dfs(int x)
{
	Time++; sta[x]=Time; b[Time]=mp(1,0);

	for (int i=stdx[x-1]+1;i<=stdx[x];i++) {
		int next=front[orderx[i]].y;
		dfs(next); }

	Time++; end[x]=Time; b[Time]=mp(0,1);
	return ;
}

char str[10];

int nowf[MAXN+10];

void init()
{
	n=read();

	for (int i=2;i<=n;i++) {
		int fa=read();
		nowf[i]=fa;
		front[++m]=mp(fa,i); }

	sortx();

	dfs(1);

	tr.root=tr.build(1,n<<1);

	int T=read();

	while (T--) {
		memset(str,'\0',sizeof(str));
		scanf("\n%s",str);
		
		if (!strcmp(str,"Change")) {
			int x=read(),f=read();
			tr.splay(tr.find(tr.order(sta[x])-1),0);
			tr.splay(tr.find(tr.order(end[x])+1),tr.root);

			int cnt=tr.ls[tr.rs[tr.root]];
			tr.ls[tr.rs[tr.root]]=0; tr.fa[cnt]=0;

			tr.update(tr.rs[tr.root]); tr.update(tr.root);
	
			tr.splay(sta[f],0);
			tr.splay(tr.find(tr.order(sta[f])+1),sta[f]);
			
			tr.ls[tr.rs[tr.root]]=cnt; tr.fa[cnt]=tr.rs[tr.root];
			
			tr.update(tr.rs[tr.root]); tr.update(tr.root); }
		
		else if (!strcmp(str,"Query1")) {
			int x=read();
			tr.splay(sta[x],0);
			printf("%d\n",tr.ans[tr.ls[tr.root]].x-tr.ans[tr.ls[tr.root]].y); }
		
		else if (!strcmp(str,"Query2")) {
			int x=read();
			tr.splay(sta[x],0); tr.splay(end[x],sta[x]);
			printf("%d\n",tr.ans[tr.ls[tr.rs[tr.root]]].x);	} }

	return ;
}

int main()
{
	freopen("physics.in","r",stdin);
	freopen("physics.out","w",stdout);
	init();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
