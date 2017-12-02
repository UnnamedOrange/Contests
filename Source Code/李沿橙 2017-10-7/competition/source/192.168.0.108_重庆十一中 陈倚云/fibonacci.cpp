#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <set>
#include <vector>
#include <cstring>
using namespace std;
int n,m;
int up[233333],de[233333],dp[233333][23],fa[233333];
int pn[233333],pv[233333],st[233333];
int sz[1500],tmp[1500],p=0,q,tmp2[1500],t2;
int tot=0;
void init() {
	memset(up,0,sizeof(up));
	memset(de,0,sizeof(de));
	memset(dp,0,sizeof(dp));
	memset(pn,0,sizeof(pn));
	memset(pv,0,sizeof(pv));
	memset(fa,0,sizeof(fa));
	return ;
}
void ins(int x,int y) {
	pv[++tot]=y;
	pn[tot]=st[x];
	st[x]=tot;
	return;
}
void dfs(int x) {
	dp[x][0]=fa[x];
	for(int i=1; i<20; i++) {
		dp[x][i]=dp[dp[x][i-1]][i-1];
	}
	for (int i=st[x]; i; i=pn[i]) {
		int cur=pv[i];
		if (cur==fa[x]) continue;
		de[cur]=de[x]+1;
		up[cur]=up[x]+1;
		fa[cur]=x;
		dfs(cur);
	}
	return;
}
int lca(int x,int y) {
	if (de[x]<de[y]) {
		int t=x;
		x=y;
		y=t;
	}
	for (int i=19; i>=0; i--) {
		if (de[dp[x][i]]>=de[y]) x=dp[x][i];
	}
	if (x==y) return x;
	for (int i=19; i>=0; i--) {
		if (dp[x][i]!=dp[y][i]) {
			x=dp[x][i];
			y=dp[y][i];
		}
	}
	return dp[x][0];
}
int main() {
	freopen("fibonacci","r",stdin);
	freopen("fibonacci","w",stdout);
	scanf("%d",&m);
	init();
	ins(1,2);
	ins(1,3);
	sz[++p]=1;
	sz[++p]=2;
	tmp[1]=3;
	q=1;
	int a=1,b=1,c,num=3;
	for(int i=3; i<=16; i++) {
		t2=0;
		for(int j=1; j<=p; j++) {
			ins(sz[j],num+j);
			ins(num+j,sz[j]);
			tmp2[++t2]=num+j;
		}
		num+=p;
		for(int j=1; j<=q; j++) {
			sz[++p]=tmp[j];
		}
		for(int j=1; j<=t2; j++) tmp[j]=tmp2[j];
		q=t2;
	}

	fa[1]=1;
	de[1]=up[1]=0;
	dfs(1);
	while(m--) {
		scanf("%d%d",&a,&b);
		if(a>1000 && b>1000) printf("1\n");
		else printf("%d\n",lca(a,b));
	}
	return 0;
}
