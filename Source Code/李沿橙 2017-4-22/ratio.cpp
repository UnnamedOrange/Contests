#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;

long long A,B,L;

long long gcd(long long a,long long b)
{
	if(b==0) return a;
	return gcd(b,a%b);
}

struct rate
{
	long long up;
	long long down;

	rate(long long up,long long down):up(up),down(down)
	{

	}

	bool operator <(const rate &b) const
	{
		long long newDown=down*b.down/gcd(down,b.down);
		long long left=newDown/down*up;
		long long right=newDown/b.down*b.up;
		return left<right;
	}

	void div()
	{
		long long d=gcd(up,down);
		up/=d;
		down/=d;
	}
};

void input()
{
	scanf("%lld%lld%lld",&A,&B,&L);
}

void run()
{
	rate comp(A,B);
	rate ans(101,1);
	int div=ceil(A/B);
	for(int i=1; i<=L; i++)
	{
		for(int j=1; j<=L; j++)
		{
			rate temp(i,j);
			//printf("%d %d\n",temp.up,temp.down);
			if(temp<comp) break;
			ans=std::min(ans,temp);
		}
	}
	ans.div();
	printf("%lld %lld",ans.up,ans.down);
}

int main()
{
#ifndef DEBUG
	freopen("ratio.in","r",stdin);
	freopen("ratio.out","w",stdout);
#endif
	input();
	run();
	return 0;
}
