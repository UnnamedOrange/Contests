#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<cmath>
#include<ctime>
#include<queue>
#include<map>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
typedef long long ll;
using namespace std;
int a[1010],minn=1000000000,n,m,k;
bool l[1000],vis[100][100];
void dfs(bool now[],int dep)
{	if(dep>=minn) return;
	bool tag=true; for(rint i=1;i<=n;i++) if(!now[i]){tag=false;break;}
	if(tag) minn=dep;
	for(rint i=1;i<=n;i++)
	for(rint j=1;j<=m;j++)
	{	bool fl=false;
		for(rint k=i;k<=i+a[j]-1;k++) if(!now[k]){fl=true;break;}
		if(fl&&!vis[i][i+a[j]-1])
		{	for(rint k=i;k<=i+a[j]-1;k++) now[k]=(!now[k]);
			vis[i][i+a[j]-1]=true;dfs(now,dep+1);vis[i][i+a[j]-1]=false;
			for(rint k=i;k<=i+a[j]-1;k++) now[k]=(!now[k]);
		}
	}
}
int main()
{   freopen("starlit.in","r",stdin);
	freopen("starlit.out","w",stdout);
	scanf("%d%d%d",&n,&k,&m); int x;
	for(rint i=1;i<=n;i++) l[i]=true;
	for(rint i=1;i<=k;i++) scanf("%d",&x),l[x]=false;
	for(rint i=1;i<=m;i++) scanf("%d",&a[i]);
	if(m==1)
	{	int ans=0;
		for(rint i=1;i<=n;i++)
		if(!l[i])
		{	for(rint j=i;j<=i+a[1]-1;j++) l[j]=(!l[j]);
			ans++; bool tag=true;
			for(rint j=1;j<=n;j++) if(!l[j]) {tag=false;break;}
			if(tag) {printf("%d\n",ans);return 0;}
		}
	}
	dfs(l,0);
	printf("%d",minn);
 	return 0;
}



