#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100007
using namespace std;
int n,m,ans,cnt,p;
int head[N<<1],du[N],du2[N],point[N],vis[N];
struct edge {
	int u,v,net;
} e[N<<1];
struct node {
	int du,pos;
	bool operator < (const node &x) const {
		return du>x.du;
	}

} a[N<<1];
inline int read() {
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
inline void add(int u,int v) {
	e[++cnt].v=v;
	e[cnt].net=head[u];
	head[u]=cnt;
}
bool judge() {
	for(int i=1; i<=n; i++) if(du[i]>2) return false;
	return true;
}
void dfs(int u) {
	for(int i=head[u]; i; i=e[i].net) {
		int v=e[i].v;
		if(vis[v]) continue;
		vis[v]=1;
		p++;
		if(p%2==0) point[++ans]=v;
		dfs(v);
	}
}
void work1() {
	cnt=0;
	p=0;
	for(int i=1; i<=n; i++) {
		if(!vis[i] && du2[i]==1) {
			vis[i]=1;
			p=1;
			dfs(i);
		}
	}
	printf("%d\n",ans);
	for(int i=1; i<=ans; i++) printf("%d ",point[i]);
	return ;
}
int main() {
	freopen("ping.in","r",stdin);
	freopen("ping.out","w",stdout);
	int x,y,o;
	n=read();
	o=read();
	for(int i=1; i<n; i++) {
		x=read();
		y=read();
		du[x]++;
		du[y]++;
	}
	m=read();
	for(int i=1; i<=m; i++) {
		x=read();
		y=read();
		add(x,y);
		add(y,x);
		a[x].pos=x;
		a[x].du++;
		a[y].pos=y;
		a[y].du++;
		du2[x]++;
		du2[y]++;
	}
	sort(a+1,a+n+1);
	cnt=0;
	if(judge()) {
		work1();
		return 0;
	}
	for(int i=1; i<=n; i++) {
		int flag=0;
		if(a[i].du==0) continue;
		a[i].du=0;
		for(int j=head[a[i].pos]; j; j=e[j].net) {
			int v=e[j].v;
			for(int k=1; k<=n; k++) {
				if(a[k].pos==v && a[k].du) {
					a[k].du--,flag=1;
					break;
				}
			}
		}
		if(flag) ans++,point[++cnt]=a[i].pos;
	}
	printf("%d\n",ans);
	for(int i=1; i<=ans; i++) printf("%d ",point[i]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
