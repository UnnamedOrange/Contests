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
char c[10000];
int h[20001][1002],q[100];
const int mod=998244353;
int main()
{	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	int n,m; scanf("%d%d",&n,&m);
	memset(h,-1,sizeof(h));
	for(rint i=1;i<=n;i++)
	{	scanf("%s",c+1); int len=strlen(c+1); h[i][0]=0;
		for(rint j=len;j>=1;j--) h[i][len-j+1]=((ll)h[i][len-j]*233+c[j]-'0')%mod;
	}
	int opt,tot=n;
	for(rint i=1;i<=m;i++)
	{	scanf("%d",&opt);
		if(opt==1)
		{	scanf("%s",c+1); int len=strlen(c+1); tot++; h[tot][0]=0;
			for(rint j=len;j>=1;j--) h[tot][len-j+1]=((ll)h[tot][len-j]*233+c[j]-'0')%mod;
		}
		else
		{	int t;scanf("%d",&t); for(rint i=1;i<=t;i++) scanf("%d",&q[i]);
			int l=1,r=1000;
			int ans=0;
			while(l<=r)
			{	int mid=(l+r)>>1; bool b=true;
				for(rint i=1;i<t;i++) if(h[q[i]][mid]==-1||h[q[i+1]][mid]==-1||h[q[i]][mid]!=h[q[i+1]][mid]) b=false;
				if(b) ans=mid,l=mid+1;
				else r=mid-1;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}


