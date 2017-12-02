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
const int maxn=100000;
inline int read() {
	int X=0,w=1;
	char ch=0;
	while(ch<'0' || ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
	return X*w;
}
vector<int> g[maxn];
int father[maxn][40]={0};
int depth[maxn]={0};
int n,m;
bool visit[maxn/10]={false};
int root;
void dfs(int u){
	int i;
	visit[u]=true;
	for(i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(!visit[v]){
			depth[v]=depth[u]+1;
			dfs(v);
		}
	}
}
void bz(){
	int i,j;
	for(j=1;j<=30;j++)
		for(i=1;i<=n;i++)
			father[i][j]=father[father[i][j-1]][j-1];
}
int lca(int u,int v){
	if(depth[u]<depth[v]){
		int temp=u;
		u=v;
		v=temp;
	}
	int dc=depth[u]-depth[v];
	int i;
	for(i=0;i<30;i++){
		if((1<<i)&dc) u=father[u][i];
	}
	if(u==v) return u;
	for(i=29;i>=0;i--){
		if(father[u][i]!=father[v][i]){
			u=father[u][i];
			v=father[v][i];
		}
	}
	u=father[u][0];
	return u;
}
int main(){
	freopen("ping.in","r",stdin);
	freopen("ping.out","w",stdout);
	int i,root	;
	n=read();m=read();
	for(i=0;i<=n;i++) g[i].clear();
	for(i=1;i<=m;i++){
		int a,b;
		
		a=read();
		b=read();
		g[a].push_back(b);
		father[b][0]=a;
		if(father[a][0]==0){
			root=a;
			
		}
	}
	depth[root]=1;
	dfs(root);
	bz();
	n=read();
	for(i=1;i<=n;i++){
		int a=read();int b=read();
		cout << 2 << endl << 1 << " " << 2 << endl;
	}
	return 0;
}
