#include<bits/stdc++.h>
using namespace std;
#define maxn 200000
int n=1,sum1[maxn],sum0[maxn],ans=999999;
char a[maxn];
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	while(cin>>a[n])
	{
		if(a[n]=='0')sum0[n]=sum0[n-1]+1,sum1[n]=sum1[n-1];
		else sum1[n]=sum1[n-1]+1,sum0[n]=sum0[n-1];
		n++;
	}
	n-=1;
	for(int k=0;k<=n;k++)
	{
		int x=max(sum1[k]-sum1[1],0),y=max(sum0[n]-sum0[k+1],0);
		ans=min(x+y,ans);
	}
	printf("%d",ans);
}
