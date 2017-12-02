#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<ctime>
#include<map>
#include<queue>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
#define fi first
#define se second
typedef long long ll;
using namespace std;
int a[1000001],k,go[1000001],n;
bool vis[1000001];
int bfs(int xx)
{	queue< pair< pair<int,int>,int> > q; q.push(make_pair(make_pair(xx,a[xx]-k),1)); vis[xx]=true;
	int la=0,ans=0;debug(xx);
	while(!q.empty())
	{	int x=q.front().fi.fi,y=q.front().fi.se,now=q.front().se; q.pop();
		debug(x),debug(y),debug(now),debug(la);fgx;
		if(la&&y>=k-a[la]) vis[la]=true,q.push(make_pair(make_pair(la,y-(k-a[la])),now+1)),go[la]=x,la=0;
		if(!vis[x-1]&&x-1>=1)
		{	if(a[x-1]>=k) vis[x-1]=true,q.push(make_pair(make_pair(x-1,y+(a[x-1]-k)),now+1));
			else if(y>=k-a[x-1]) vis[x-1]=true,q.push(make_pair(make_pair(x-1,y-(k-a[x-1])),now+1));
			else if(!la)
			{	la=x-1;
				if(go[x]) q.push(make_pair(make_pair(go[x],y),now));
			}
			else return ans;
		}
		if(!vis[x+1]&&x+1<=n)
		{	if(a[x+1]>=k) vis[x+1]=true,q.push(make_pair(make_pair(x+1,y+(a[x+1]-k)),now+1));
			else if(y>=k-a[x+1]) vis[x+1]=true,q.push(make_pair(make_pair(x+1,y-(k-a[x+1])),now+1));
			else if(!la)la=x-1;
			else return ans;
		}
		ans=max(ans,now);
	}
	return ans;
}
int main()
{	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	int m; scanf("%d%d",&n,&m);
	for(rint i=1;i<=n;i++) scanf("%d",&a[i]);
	for(rint u=1;u<=m;u++)
	{	for(rint i=1;i<=n;i++) vis[i]=false,go[i]=0;
		scanf("%d",&k); int ans=0;
		for(rint i=1;i<=n;i++)
		if(a[i]>=k&&!vis[i]) ans+=bfs(i);
		printf("%d\n",ans);
	}
	return 0;
}


