#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
using namespace std;

const int maxn=1e3+10;
int n,a,b,fa[maxn],x[maxn],y[maxn],tot,ans;
struct edge{
	int u,v,w;
	bool operator< (edge o)const{
		return w<o.w;
	}
}e[maxn*maxn];

int findfa(int x){
	if(fa[x]==x)return x;
	return fa[x]=findfa(fa[x]);
}

int main(){
	freopen("pupil.in","r",stdin);
	freopen("pupil.out","w",stdout);
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n+1;++i)fa[i]=i;
	for(int i=1;i<=n;++i)
		scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			e[++tot]=(edge){i,j,b*(abs(x[i]-x[j])+abs(y[i]-y[j]))};
	for(int i=1;i<=n;++i)
		e[++tot]=(edge){i,n+1,a};
	sort(e+1,e+tot+1);
	for(int i=1;i<=tot;++i){
		int u=findfa(e[i].u),v=findfa(e[i].v);
		if(u!=v){
			fa[u]=v;
			ans+=e[i].w;
		}
	}
	printf("%d\n",ans);
	return 0;
}
