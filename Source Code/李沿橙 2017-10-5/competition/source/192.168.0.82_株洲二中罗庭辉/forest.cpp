#include <bits/stdc++.h>
#define inf 1000000000+7
typedef long long lol;
using namespace std;
struct cnm{lol num;lol u,v,w,head,next,book;}e[1000000];
lol a[100010],dis[100010],vis[100010],m;
lol u1,v1;
int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') y=1;c=getchar();}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';c=getchar();}
		return x*y; 	
}
int n;
void add(int u,int v){
	m++;e[m].u=u;e[m].v=v;e[m].w=a[v];
	e[m].next=e[u].head;e[u].head=m;}
void spfa(int v0){
	for(int i=1;i<=n;i++) dis[i]=inf;
	queue <int>q;
	dis[v0]=0;q.push(v0);vis[v0]=1;
	while(!q.empty()){
		lol u=q.front();q.pop();
		vis[u]=0;
		for(int i=e[u].head;i!=0&&e[i].book==0;i=e[i].next)
		{
			lol v=e[i].v,w=e[i].w;u=e[i].u;
			if(dis[v]>dis[u]+w&&w!=inf&&e[i].book==0)
				{
					dis[v]=dis[u]+w;
					if(!vis[v]){
						q.push(v);
						vis[v]=1;
					}
				}
		}
	}
}	
void shan(int id){
	id=id*2;
	int u=e[id].u,v=e[id].v;
	for(int i=1;i<=m;i++){
	if(u==e[i].u&&v==e[i].v) {id=i;e[id].w=inf;e[id].next=0;}
	if(u==e[i].v&&v==e[i].u) {id=i;e[id].w=inf;e[id].next=0;}}
}
int main(){
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	lol ans=0,anss=1;
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++)
	{lol u,v;u=read();v=read();add(u,v);add(v,u);}
	spfa(1);
	for(int i=1;i<=n;i++){ans=max(dis[i]+a[1],ans);}
	cout<<ans<<endl;int tree=1;
	for(int i=1;i<n;i++){
		anss=1;
		int tw;tw=read();
		shan(tw);
		tree++;		
		for(int i=1;i<=tree;i++){
		for(int j=1;j<=n;j++)	
		{spfa(j);for(int i=1;i<=n;i++) if(dis[i]<inf)ans=max(dis[i]+a[i],ans);}
		anss=ans*anss;
		ans=1;	}
		cout<<anss<<endl;
		anss=1;
	}
	return 0;
}
