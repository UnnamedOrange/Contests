#pragma GCC opitmize("O3")
#pragma G++ opitmize("O3")
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
struct Edge{ int u,v,c; } G[1000010];
int n,m,t=0,x[1010],y[1010],A,B,f[1010];
inline bool c1(Edge a,Edge b){ return a.c<b.c; }
inline int gF(int x){ return x==f[x]?x:f[x]=gF(f[x]); }
inline void adj(int x,int y,int c){ G[t++]=(Edge){x,y,c}; }
int main(){
	freopen("pupil.in","r",stdin);
	freopen("pupil.out","w",stdout);
	scanf("%d%d%d",&n,&A,&B);
	for(int i=1;i<=n;++i){
		scanf("%d%d",x+i,y+i);
		adj(0,i,A); f[i]=i;
		for(int j=1;j<i;++j)
			if(B*(abs(x[i]-x[j])+abs(y[i]-y[j]))<A)
				adj(i,j,B*(abs(x[i]-x[j])+abs(y[i]-y[j])));
	}
	sort(G,G+t,c1); int c=0,S=0;
	for(int x,y,i=0;i<t;++i){
		x=gF(G[i].u); y=gF(G[i].v);
		if(x!=y){ ++c; S+=G[i].c; f[x]=y; }
		if(c==n) break;
	}
	printf("%d\n",S);
}
