#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
int gg[1005][1005],cnt[1005];
double dp[305][1005];
int n,a[305],mex[305],sg[305][305];
int gcd(int x,int y){return !y?x:gcd(y,x%y);}
void init()
{
	for(int i=0;i<=1000;++i)
	for(int j=0;j<=1000;++j)
	gg[i][j]=gcd(i,j);
}
int main()
{
freopen("cards.in","r",stdin);
freopen("cards.out","w",stdout);
	init();
	scanf("%d",&n);
	int mx=0,res=0,end=0;
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		mx=max(mx,a[i]);
		end=gcd(end,a[i]);
		dp[1][a[i]]=1.0/(double)n;
	}
	for(int i=2;i<=n;++i)
	{
		for(int j=2;j<=mx;++j)
		{
			memset(cnt,0,sizeof(cnt));
			for(int l=1;l<=n;++l)cnt[gg[j][a[l]]]++;
			if(cnt[j]<i-1)continue;
			else cnt[j]-=i-1;
			for(int l=1;l<=1000;++l)dp[i][l]+=(double)cnt[l]/(n-i+1)*dp[i-1][j];
		}
	}
	double ans=0;
	for(int i=1;i<=n;i+=2)ans+=dp[i][1];
	printf("%.9lf ",1-ans);
	sg[n+1][1]=1;int tim=0;
	for(int i=n;i>=1;--i)
	for(int j=0;j<=mx;++j)
	{
		if(j==1){sg[i][j]=1;continue;}
		tim++;
		memset(cnt,0,sizeof(cnt));
		for(int l=1;l<=n;++l)cnt[gg[j][a[l]]]++;
		if(j&&i!=1&&cnt[j]<i-1)continue;
		else if(j)cnt[j]-=i-1;
		for(int l=1;l<=1000;++l)
		{
			if(cnt[l])mex[sg[i+1][l]]=tim;//can
		}
		for(sg[i][j]=0;mex[sg[i][j]]==tim;++sg[i][j]);
	}
	printf("%.9lf\n",sg[1][0]?1.0:0.0);
	return 0;
}
