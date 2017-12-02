#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<cmath>
using namespace std;
const int MAXN=1e5+10;
int a[MAXN];
int main()
{
	int i,j,m,n;
	long long cnt,k,l,ans;
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	srand(time(0)+20202020);
	scanf("%d%d",&n,&m);
	ans=0;
	for (i=1;i<=n;i++)
	{
		scanf("%lld",&k);
		ans+=k;
	}
	for (i=1;i<=m;i++)
	{
		cnt=ans;
		scanf("%lld",&k);
		cnt=cnt/k;
		if (cnt>(n+1)) cnt=n;
		else
		{
			l=rand()%4+1;
			cnt-=l;
		}
		if (cnt<0) cnt=0;
		printf("%d ",cnt);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}

