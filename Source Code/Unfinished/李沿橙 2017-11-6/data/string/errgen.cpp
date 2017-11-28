#include<bits/stdc++.h>
using namespace std;
int a[1000100],b[1000100],bb;
struct treap
{
	int l[1000100],r[1000100],size[1000100],tag[1000100],num[1000100],data[1000100],tt;
	int init(int ql,int qr)
	{   
		int t=++tt,mid=(ql+qr)>>1;
		num[t]=a[mid];
		if (num[t]>26) data[t]=(1<<27);else data[t]=(1<<num[t]);
		size[t]=qr-ql+1;
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
	void update(int s)
	{
		size[s]=size[l[s]]+size[r[s]]+1;
		data[s]=data[l[s]]|data[r[s]];
		if (num[s]>26) data[s]|=(1<<27);else data[s]|=(1<<num[s]);
	}
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
	int search(int root,int w)
	{
		//if ((size[root]==1)&&(num[root]!=w)&&(num[root]<=26)) assert(0);
		//if (size[root]==1) return 1;
		pushdown(root);
		bool b1=data[l[root]]&((1<<27)|(1<<w));
		bool b2=data[r[root]]&((1<<27)|(1<<w));
		if (((!b1)&&(!b2))||((rand()%100==0)&&((num[root]>=27)||(num[root]==w))))
		{
			if ((num[root]!=w)&&(num[root]<=26)) assert(0);
			return size[l[root]]+1;
		}
			
		if ((b1)&&(!b2)) return search(l[root],w);
		if ((!b1)&&(b2)) return size[l[root]]+1+search(r[root],w);
		if (rand()%2) return search(l[root],w);else return size[l[root]]+1+search(r[root],w);
	}
	int find(int &root,int ql,int w)
	{
		pair<int,int> p=split(root,ql-1);
		int ans=search(p.second,w);
		root=merge(p.first,p.second);
		return ans+ql-1;
	}
	void dfs(int s)
	{
		pushdown(s);
		if (l[s]) dfs(l[s]);
		cerr<<num[s]<<' ';
		if (r[s]) dfs(r[s]);
	}
	int get(int root,int k)
	{
		pushdown(root);
		if (size[l[root]]+1==k) return num[root];
		if (size[l[root]]>=k) return get(l[root],k);
		return get(r[root],k-size[l[root]]-1);
	}
}treap;
char st[1000100];
int main()
{
	srand(time(NULL));
	int n,m;long long k;scanf("%d%d%lld",&n,&m,&k);cout<<n<<' '<<m<<' '<<k<<endl;
	for (int i=1;i<=n;i++)
	{
		if (rand()%10) st[i]='?';else st[i]='a'+rand()%26;
		putchar(st[i]);
	}
	putchar('\n');
	int top=26;
	for (int i=1;i<=n;i++) if (st[i]=='?') a[i]=++top;else a[i]=st[i]-'a'+1;
	int root=treap.init(1,n),rem=m;
	for (int i=1;i<=m/2;i++)
	{
		rem--;
		int l=rand()%n+1,r=rand()%n+1;if (l>r) swap(l,r);
		treap.reverse(root,l,r);cout<<l<<' '<<r<<endl;
	}
	//for (int i=1;i<=n;i++) cerr<<a[i]<<' ';cerr<<endl<<endl;
	//treap.dfs(root);cerr<<endl<<endl;
	//for (int i=1;i<=n;i++) cerr<<treap.get(root,i)<<' ';cerr<<endl<<endl;
	for (int i=1;i<=n;i++) if ((a[i]<=26)&&(treap.get(root,i)<=26)&&(a[i]!=treap.get(root,i)))
	{
		rem--;if (rem<0) assert(0);
		int w=treap.find(root,i+1,a[i]);//if (w<i) {cerr<<i<<' '<<w<<endl;assert(0);}
		if ((treap.get(root,w)!=a[i])&&(treap.get(root,w)<=26)) {cerr<<i<<' '<<w<<endl;assert(0);}
		cout<<i<<' '<<w<<endl;
		treap.reverse(root,i,w);
	}
	for (int i=1;i<=n;i++) cerr<<a[i]<<' '<<treap.get(root,i)<<endl;
	while (rem>=2)
	{
		rem-=2;
		int l=rand()%n+1,r=rand()%n+1;if (l>r) swap(l,r);
		cout<<l<<' '<<r<<endl;
		cout<<l<<' '<<r<<endl;
	}
	if (rem) cout<<"1 1\n";
	/*treap.dfs(root);
	//for (int i=1;i<=n;i++) cout<<a[i]<<' ';cout<<endl;
	//for (int i=1;i<=n;i++) cout<<b[i]<<' ';cout<<endl;
	for (int i=1;i<=top;i++) fa[i]=i;
	for (int i=1;i<=n;i++) merge(a[i],b[i]);
	//for (int i=1;i<=top;i++) cout<<i<<' '<<getf(i)<<endl;
	for (int i=1;i<=26;i++) if (getf(i)<i) {printf("Bad Luck Allen\n");return 0;}
	mi[0]=1;for (int i=1;i<=12;i++) mi[i]=mi[i-1]*26;mi[13]=2e18;
	for (int i=top;i>=27;i--) g[i]=(getf(i)==i)+g[i+1];
	if (k>mi[min(g[27],13)]) {printf("Bad Luck Allen\n");return 0;}//return 0;
	for (int i=1;i<=26;i++) ans[i]=i;
	for (int i=27;i<=top;i++) if (getf(i)==i)
	{
		ans[i]=1;
		if (g[i+1]>12) continue;
		while (k>mi[g[i+1]]) {ans[i]++;k-=mi[g[i+1]];}
	}
	for (int i=1;i<=n;i++) putchar(ans[getf(a[i])]+'a'-1);*/
}	
