#include <iostream>
#include <climits>
#include <cstdio>
#include <cctype>

using namespace std;

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch)) f=ch=='-'?-1:f,ch=getchar();
	while (isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x*f;
}

int buf[30];

inline void write(int x)
{
	if (x<0) putchar('-'),x=-x;
	for (; x; x/=10) buf[++buf[0]]=x%10;
	if (!buf[0]) buf[++buf[0]]=0;
	for (; buf[0]; putchar('0'+buf[buf[0]--]));
}

typedef long double db;

const int N=1000005;
const int INF=INT_MAX;
const int C=10;

inline db cross(int k1,int b1,int k2,int b2)
{
	return ((db)b2-b1)/((db)k1-k2);
}

inline void update(int &x,int y)
{
	x=x<y?x:y;
}

int f[N],c[N],v[N],k[N],b[N],nxt[N],adj[N];
int qhead[C][C];
int n,maxc,ans,tot;

inline void store(int id)
{
	int i=c[id]-1,j=id%c[id];
	k[id]=v[id],b[id]=f[id]-v[id]*(id/c[id]);
	for (; qhead[i][j]&&v[adj[qhead[i][j]]]>=v[id]; qhead[i][j]=nxt[qhead[i][j]]);
	for (; nxt[qhead[i][j]]; qhead[i][j]=nxt[qhead[i][j]])
	{
		int i1=adj[qhead[i][j]],i2=adj[nxt[qhead[i][j]]];
		if (cross(k[i1],b[i1],k[i2],b[i2])>cross(k[i1],b[i1],k[id],b[id])) break;
	}
	adj[++tot]=id,nxt[tot]=qhead[i][j],qhead[i][j]=tot;
}

inline int fx(int id,int x)
{
	return k[id]*x+b[id];
}

inline int query(int i,int j,int x)
{
	for (; nxt[qhead[i][j]]; qhead[i][j]=nxt[qhead[i][j]])
	{
		int i1=adj[qhead[i][j]],i2=adj[nxt[qhead[i][j]]];
		if (cross(k[i1],b[i1],k[i2],b[i2])>x) break;
	}
	return qhead[i][j]?fx(adj[qhead[i][j]],x):INF;
}

void dp()
{
	f[0]=0,store(0);
	for (int i=1; i<=n; ++i)
	{
		f[i]=INF;
		for (int j=0; j<maxc; ++j) update(f[i],query(j,i%(j+1),i/(j+1)));
		if (i<n&&f[i]!=INF) store(i);
	}
}

int main()
{
	freopen("bus.in","r",stdin),freopen("bus.out","w",stdout);
	n=read(),maxc=read();
	for (int i=0; i<n; ++i) c[i]=read(),v[i]=read();
	dp();
	for (int i=1; i<=n; ++i) write(f[i]==INF?-1:f[i]),putchar(i<n?' ':'\n');
	fclose(stdin),fclose(stdout);
	return 0;
}
