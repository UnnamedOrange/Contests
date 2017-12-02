#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
int n;
long long ans=0;
long long cnt[2050];
using namespace std;
int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int tmp=i,cn=0,gewei=0;
		while(tmp>0)
		{
			gewei=tmp%10;
			cn=(cn|(1<<gewei));
			tmp/=10;
		}
		cnt[cn]++;
	}
	for(int i=0;i<=2048;i++)
	{
		if(cnt[i]==0) continue;
		else ans+=cnt[i]*(cnt[i]-1)/2;
	}
	printf("%lld\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
