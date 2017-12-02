#include<algorithm>
#include<iostream>
#include<cstdio>
#define Max(a,b) a=a>b?a:b

using namespace std;
const int N=1000005;
int p[N],a[N]={0};
int main()
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	int k,n,m,ans,maxn;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&p[i])/*,maxn=max(maxn,p[i])*/;
	for(int i=1;i<=m;i++)
	{
		ans=-1;
		scanf("%d",&k);
		for(int i=1;i<=n;i++) a[i]+=a[i-1]+p[i];
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				if(a[j]-a[i-1]>=k*(j-i+1)) ans=Max(ans,j-i+1);
		cout<<ans<<" ";
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
