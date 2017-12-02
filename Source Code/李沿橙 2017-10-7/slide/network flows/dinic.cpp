/*	Never stop fighting for what you believe in.	*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;
#define MAXN 20005
#define MAXM 100005
struct edge {
	int next,to,flow;
}e[MAXM<<1];

int n,m,ecnt=1,head[MAXN],tag[MAXN],cur[MAXN];

void add(int u,int v,int f) {
	e[++ecnt].to=v; e[ecnt].next=head[u]; e[ecnt].flow=f; head[u]=ecnt;
	e[++ecnt].to=u; e[ecnt].next=head[v]; e[ecnt].flow=0; head[v]=ecnt;
}

int q[MAXN];
bool bfs() {
	memset(tag+1,0,n<<2);
	int he=1,ta=2;
	q[1]=1;
	tag[1]=1;
	while (he!=ta) {
		int x=q[he++];
		for (int now=head[x];now;now=e[now].next) {
			if (e[now].flow && !tag[e[now].to]) {
				tag[e[now].to]=tag[x]+1;
				q[ta++]=e[now].to;
			}
		}
	}
	return tag[n]>0;
}
  
int dfs(int x,int flow) {
	if (x==n) return flow;
	int usd=0;
	for (int &now=cur[x];now;now=e[now].next) {
		if (e[now].flow && tag[x]<tag[e[now].to]) {
			int ret=dfs(e[now].to,min(e[now].flow,flow-usd));
			if (ret) {
				usd+=ret;
				e[now].flow-=ret;
				e[now^1].flow+=ret;
				if (usd==flow) return flow;
			}
		}
	}
	return usd;
}
  
long long dinic() {
	long long ans=0;
	while (bfs()) {
		for (int i=2;i<=n;i++) cur[i]=head[i];
		for (int now=head[1];now;now=e[now].next) {
			if (e[now].flow) {
				int ret=dfs(e[now].to,e[now].flow);
				if (ret) {
					ans+=ret;
					e[now].flow-=ret;
					e[now^1].flow+=ret;
				}
			}
		}
	}
	return ans;
}

int main() {
	cin>>n>>m;
	for (int i=1,u,v,w;i<=m;i++) {
		cin>>u>>v>>w;
		add(u,v,w);
	}
	cout<<dinic()<<endl;
	return 0;
}


