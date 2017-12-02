#include<bits/stdc++.h>
using namespace std;
int a[1000100],b[1000100],bb;
struct treap
{
	int l[1000100],r[1000100],size[1000100],tag[1000100],num[1000100],tt;
	int init(int ql,int qr)
	{   
		int t=++tt,mid=(ql+qr)>>1;num[t]=a[mid];size[t]=qr-ql+1;
		if (ql<=mid-1) l[t]=init(ql,mid-1);
		if (mid+1<=qr) r[t]=init(mid+1,qr);
		return t;
	}
	void pushdown(int s)
	{
		if (!tag[s]) return;
		tag[l[s]]^=1;tag[r[s]]^=1;tag[s]^=1;
		swap(l[s],r[s]);
	}
	void update(int s){size[s]=size[l[s]]+size[r[s]]+1;}
	int merge(int s,int t)
	{
		if (!s) return t;if (!t) return s;
		pushdown(s);pushdown(t);
		if (rand()%(size[s]+size[t])<size[s])
		{
			r[s]=merge(r[s],t);
			update(s);
			return s;
		}
		else
		{
			l[t]=merge(s,l[t]);
			update(t);
			return t;
		}
	}
	pair<int,int> split(int s,int k)
	{
		pushdown(s);
		if (!k) return make_pair(0,s);
		if (size[s]<=k) return make_pair(s,0);
		if (size[l[s]]>=k)
		{
			pair<int,int> p=split(l[s],k);
			l[s]=p.second;update(s);
			return make_pair(p.first,s);
		}
		else
		{
			pair<int,int> p=split(r[s],k-(size[l[s]]+1));
			r[s]=p.first;update(s);
			return make_pair(s,p.second);
		}
	}
	void reverse(int& root,int ql,int qr)
	{
		pair<int,int> p1=split(root,ql-1),p2=split(p1.second,qr-ql+1);
		tag[p2.first]^=1;
		root=merge(p1.first,merge(p2.first,p2.second));
	}
	void dfs(int s)
	{
		pushdown(s);
		if (l[s]) dfs(l[s]);
		b[++bb]=num[s];
		if (r[s]) dfs(r[s]);
	}
}treap;
char st[1000100];
int fa[1000100],ans[1000100],g[1000100],wei[1000100];long long mi[15];
int getf(int s){if (fa[s]==s) return fa[s];return fa[s]=getf(fa[s]);}
void merge(int u,int v)
{
	u=getf(u);v=getf(v);
	if (u>v) swap(u,v);
	fa[v]=u;
}
int main()
{
	srand(233);
	int n,m;long long k;scanf("%d%d%lld\n%s",&n,&m,&k,st+1);if (strlen(st+1)!=n) assert(0);
	int top=26;
	for (int i=1;i<=n;i++) if (st[i]=='?') {a[i]=++top;wei[top]=i;}else a[i]=st[i]-'a'+1;
	int root=treap.init(1,n);
	while (m--)
	{
		int l,r;scanf("%d%d",&l,&r);
		treap.reverse(root,l,r);
	}
	treap.dfs(root);
	//for (int i=1;i<=n;i++) cout<<a[i]<<' ';cout<<endl;
	//for (int i=1;i<=n;i++) cout<<b[i]<<' ';cout<<endl;
	for (int i=1;i<=top;i++) fa[i]=i;
	for (int i=1;i<=n;i++) merge(a[i],b[i]);
	//for (int i=1;i<=top;i++) cout<<i<<' '<<getf(i)<<endl;
	for (int i=1;i<=26;i++) if (getf(i)<i) {cerr<<i<<endl;printf("ERROR!\n");return 0;}
	mi[0]=1;for (int i=1;i<=12;i++) mi[i]=mi[i-1]*26;mi[13]=2e18;
	for (int i=top;i>=27;i--) g[i]=(getf(i)==i)+g[i+1];
	if (k>mi[min(g[27],13)]) {printf("Bad Luck\n");return 0;}//return 0;
	for (int i=1;i<=26;i++) ans[i]=i;
	for (int i=27;i<=top;i++) if (getf(i)==i)
	{
		ans[i]=1;
		if (g[i+1]>12) continue;
		while (k>mi[g[i+1]]) {ans[i]++;k-=mi[g[i+1]];}
	}
	for (int i=1;i<=n;i++) putchar(ans[getf(a[i])]+'a'-1);
}	
