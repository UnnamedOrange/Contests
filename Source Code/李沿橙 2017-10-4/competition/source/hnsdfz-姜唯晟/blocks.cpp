#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXN 1000005
int n,m;
long long k;
long long a[MAXN];
long long sum[MAXN];
using namespace std;

int ck(int x)
{
	for(int l=1,r=l+x-1;r<=n;l++,r++)
	{
		if(sum[r]-sum[l-1]>=(long long)x*k) return 1;
	}
	return 0;
}

int main()
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%lld",&k);
		int ansl=0,ansr=n;
		while(ansl<ansr)
		{
			int ansmid=(ansl+ansr)/2+1;
			if(ck(ansmid)) ansl=ansmid;
			else ansr=ansmid-1;
		}
		printf("%d ",ansl);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
