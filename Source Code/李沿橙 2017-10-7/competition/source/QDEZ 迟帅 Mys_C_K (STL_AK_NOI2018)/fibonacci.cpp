#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lint long long
#define T 70
using namespace std;
lint f[T],s[T];
int main()
{
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	lint n=1000000000000;
	int t=2;f[0]=f[1]=f[2]=1;
	while(f[t]+f[t-1]<=n)
		f[t+1]=f[t]+f[t-1],t++;
	s[0]=f[0];
	for(int i=1;i<=t;i++)
		s[i]=s[i-1]+f[i];
	int m;scanf("%d",&m);
	while(m--)
	{
		lint x,y;int xt=t,yt=t;
		scanf("%lld%lld",&x,&y);
		while(x^y)
		{
			while(x<=s[xt]) xt--;
			while(y<=s[yt]) yt--;
			if(x>y) x-=s[xt];
			else y-=s[yt];
		}
		printf("%lld\n",x);
	}
	return 0;
}
