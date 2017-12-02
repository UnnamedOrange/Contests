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
typedef long long ll;
using namespace std;
int vis[10000001];
int main()
{	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	int n,maxn=0;cin>>n; ll ans=0;
	for(rint i=1;i<=n;i++)
	{	int k=i,now=0;
		while(k)
		{	now|=1<<(k%10);
			k/=10;
		}
		vis[now]++; maxn=max(maxn,now);
	}
	for(rint i=1;i<=maxn;i++) if(vis[i]>=2) ans+=(ll)vis[i]*(vis[i]-1)/2;
	printf("%lld\n",ans);
	return 0;
}

