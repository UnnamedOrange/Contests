#include<iostream>
#include<cstring>
#include<cstdio>
#define lint long long
#define N 3010
#define P(i) x=i,y=0;while(x) y|=(1<<(x%10)),x/=10;ans+=cnt[y],cnt[y]++;
using namespace std;
int cnt[N];
int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	int n;scanf("%d",&n);
	lint ans=0;int i,x,y;
	for(i=1;(i+3)<=n;i+=4)
	{	P(i);P(i+1);P(i+2);P(i+3);	}
	for(i;i<=n;i++)
	{	P(i);	}
	printf("%lld\n",ans);return 0;
}
