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
int a[410][410],now[401],num[1000010];
ll sum[410][410];
int main()
{   freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	int n,m,k; scanf("%d%d%d",&n,&m,&k); ll ans=0;
	for(rint i=1;i<=n;i++)
	for(rint j=1;j<=m;j++) scanf("%d",&a[i][j]),sum[j][i]=sum[j][i-1]+a[i][j];
	for(rint i=1;i<=n;i++)
	for(rint j=i;j<=n;j++)
	{	for(rint u=1;u<=m;u++) now[u]=(now[u-1]+sum[u][j]-sum[u][i-1])%k,num[now[u]]++,cout<<now[u]<<" "; cout<<endl;
		for(rint u=0;u<k;u++) cout<<num[u]<<" ";cout<<endl;
		for(rint u=1;u<=m;u++) {num[now[u]]--; if(!now[u])ans+=num[0]+1; else ans+=num[k-now[u]];}
	}
	printf("%lld\n",ans);
 	return 0;
}



