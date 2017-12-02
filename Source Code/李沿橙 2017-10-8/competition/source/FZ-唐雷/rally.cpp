#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stack>
using namespace std;
int mp[405][405];
int s[405][405];
int n,m,k,ans;
int cnt[1000005];
stack<int>del;
int p(int x){return x>=k?x-k:x;}
int main()
{
freopen("rally.in","r",stdin);
freopen("rally.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i)
	for(int j=1;j<=m;++j)
	{
		scanf("%d",&mp[i][j]);
		s[i][j]=p((1ll*s[i-1][j]+s[i][j-1]-s[i-1][j-1]+mp[i][j])%k+k);
		//if(!s[i][j])ans++;
	}
	for(int l=1;l<=m;++l)
	{
		for(int i=l;i<=m;++i)//lie
		{
			for(int j=1;j<=n;++j)//hang
			{
				int v=p(s[j][i]-s[j][i-l]+k);
				if(!v)ans++;
				ans+=cnt[v];
				cnt[v]++;
				del.push(v);
			}
			while(!del.empty()){cnt[del.top()]--;del.pop();}
		}
	}
	printf("%d\n",ans);
	return 0;
}
