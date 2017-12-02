#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int vis[2100];
int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	int n,i,tmp,t,tt;
	long long ans;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		t=i;
		tmp=0;
		while(t>0)
		{
			tt=t%10;
			t=t/10;
			if(tmp%(1<<(tt+1))<(1<<tt))
				tmp=tmp+(1<<tt);
		}
		vis[tmp]++;
	}
	ans=0;
	for(i=1;i<=(1<<10);i++)
		ans=ans+(long long)vis[i]*(vis[i]-1)/2;
	printf("%lld",ans);
	return 0;
}
