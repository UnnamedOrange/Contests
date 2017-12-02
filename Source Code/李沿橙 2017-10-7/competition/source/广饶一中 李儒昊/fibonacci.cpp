#include<iostream>
#include<cstdio>
#include<cstring>

#define N 3000007
#define ll long long

using namespace std;
ll n,m,x,y,ans,cnt1,cnt2;
ll feb[N];

inline ll read()
{
	ll x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}

inline ll swap(ll x, ll y)
{
	ll tmp=x;x=y;y=tmp;
}

int main()
{
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	feb[1]=feb[2]=1;
	for(int i=3;i<=60;i++) feb[i]=feb[i-1]+feb[i-2];
	m=read();
	while(m--)
	{
		x=read();y=read();
		for(int i=60;x!=y;i--)
		{
			if(x>feb[i]) x-=feb[i];
			if(y>feb[i]) y-=feb[i];
		}
		printf("%lld\n",x);
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
