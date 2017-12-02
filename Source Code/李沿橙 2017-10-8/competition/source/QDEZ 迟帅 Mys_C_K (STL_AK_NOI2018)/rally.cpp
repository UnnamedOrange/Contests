#include<iostream>
#include<cstdio>
#include<cstring>
#define lint long long
#define N 410
#define K 1000010
using namespace std;
int s[N][N],cnt[K],vis[N],top;
int main()
{
	freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	int k;scanf("%d",&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int x;scanf("%d",&x);x%=k;
			s[i][j]=(s[i-1][j]+x)%k;
		}
	lint ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			int c=0,top=1;
			cnt[0]=1,vis[1]=0;
			for(int p=1;p<=m;p++)
			{
				(c+=s[j][p]-s[i-1][p])%=k;
				if(c<0) c+=k;
				if(!cnt[c]) vis[++top]=c,cnt[c]=1;
				else cnt[c]++;
			}
			for(int p=1;p<=top;p++)
			{
				int x=vis[p];
				ans+=cnt[x]*(cnt[x]-1)/2;
				cnt[x]=0;
			}
		}
	printf("%lld\n",ans);return 0;
}
