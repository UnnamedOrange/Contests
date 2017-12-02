#include <iostream> 
#include <cstdio> 
#include <fstream> 
#include <algorithm> 
#include <cmath> 
#include <deque> 
#include <vector> 
#include <queue> 
#include <string> 
#include <cstring> 
#include <map> 
#include <stack> 
#include <set> 
using namespace std;
const int N=100010;
const int UP=20;
const int mo=1e9+7;
inline long long read()
{
    long long X=0,w=1; char ch=0;
    while(ch<'0' || ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0' && ch<='9') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}
struct point{
	long x,y;
	void make(long x,long y){
		this->x=x;
		this->y=y;
	}
}root[N],b[N];
long n;
long fa[N][UP+1],dep[N],father[N],w[N],a[N],len[N],c[N],out[N];
void init(){
	long i,j;
	for(i=1;i<=n;i++){
		for(j=1;(1<<j)<=dep[i];j++) fa[i][j]=fa[fa[i][j-1]][j-1];
		father[i]=i;
		root[i].make(i,i);
		w[i]=a[i];
	}
}
long lca(long x,long y){
	long up,xx=x,yy=y;
	if(dep[x]>dep[y]) swap(x,y);
	for(up=UP;up>=0;up--){
		if(dep[y]-(1<<up)>=dep[x])y=fa[y][up];
	}
	up=UP;
	while(x!=y){
		while(up>=0 && fa[x][up]==fa[y][up]) up--;
		if(up<0) break;
		x=fa[x][up];
		y=fa[y][up];
		up--;
	}
	if(x==y) return len[xx]+len[yy]-2*len[x]+a[x];
	else return len[xx]+len[yy]-2*len[fa[x][x]]+a[fa[x][0]];
}
vector<long>maps[N];
bool ok[N];
void dfs(long now){
	long i,to,next;
	ok[now]=true;
	for(i=0;i<maps[now].size();i++){
		to=maps[now][i];
		if(!ok[to]){
			fa[to][0]=now;
			dep[to]=dep[now]+1;
			len[to]=a[to]+len[now];
			dfs(to);}}}
long ksm(long a,long b){
	if(b>1)
		if(b&1) return (long long)ksm((long long)a*a%mo,b>>1)*a%mo;
		else return ksm((long long)a*a%mo,b>>1);
	else return a;
}
long cha(long x){return (father[x]==x)?x:father[x]=cha(father[x]);}
void bin(long x,long y){father[char(x)]=cha(y);}
int main(){
    freopen("forest.in","r",stdin);
    freopen("forest.out","w",stdout);
    long i,xx,yy,r1,r2,r3,r4,w1,w2,w3,w4,maxx;
    long long ans=1;
    n=read();
    for(i=1;i<=n;i++){
    	a[i]=read();
    	ans=ans*a[i]%mo;
	}
	out[n]=ans;
	for(i=1;i<n;i++){
		xx=read();yy=read();
		b[i].make(xx,yy);
		maps[xx].push_back(yy);maps[yy].push_back(xx);
	}
	dfs(1);
	init();
	for(i=1;i<n;i++) c[i]=read();
	for(i=n-1;i>=1;i--){
		xx=cha(b[c[i]].x);yy=cha(b[c[i]].y);
		r1=root[cha(xx)].x;r2=root[cha(xx)].y;r3=root[cha(yy)].x;r4=root[cha(yy)].y;
		w1=lca(r1,r3);w2=lca(r1,r4);w3=lca(r2,r3);w4=lca(r2,r4);
		maxx=max(w1,max(w2,max(w3,max(w4,max(w[xx],w[yy])))));
		ans=ans*ksm(w[xx],mo-2)%mo*ksm(w[yy],mo-2)%mo*maxx%mo;
		bin(xx,yy);
		if(maxx==w1) root[cha(xx)].make(r1,r3);if(maxx==w2) root[cha(xx)].make(r1,r4);if(maxx==w3) root[cha(xx)].make(r2,r3);if(maxx==w4) root[cha(xx)].make(r2,r4);
		if(maxx==w[xx]) root[cha(xx)].make(r1,r2);if(maxx==w[yy]) root[cha(xx)].make(r3,r4);
		w[cha(xx)]=maxx;
		out[i]=ans;
	}
    for(i=1;i<=n;i++) printf("%ld\n",out[i]);
    return 0;
}
