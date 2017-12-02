#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;
inline int readIn()
{
	int a;
	scanf("%d",&a);
	return a;
}

const int mod = 10007;
int a,b,k,n,m;

struct BigInt
{
	static const int digit = 1e8;
	static const int size = 1000;
	long long num[size];

	int len() const
	{
		for(int i=size-1; i>=0; i--)
		{
			if(num[i]) return i+1;
		}
		return 0;
	}

	void fact(int from, int to)
	{
		memset(num, 0, sizeof(num));
		num[0]=1;
		int length = 1;
		for(int i=from; i<=to; i++)
		{
			for(int j=0; j<length; j++)
			{
				num[j]*=i;
			}
			for(int j=0; j<length; j++)
			{
				if(num[j]>=digit)
				{
					length = std::max(length, j+2);
					num[j+1]+=num[j]/digit;
					num[j]%=digit;
				}
			}
		}
	}

	void div(int from, int to)
	{
		int length = len();
		for(int i=to; i>=from; i--)
		{
			long long Div = 0;
			long long Mod = 0;
			for(int j = length - 1; j>=0; j--)
			{
				num[j] += Mod * digit;
				Div = num[j] / i;
				Mod = num[j] % i;
				num[j] = Div;
				if(j==length - 1 && !num[j])
				{
					length--;
				}
			}
		}
	}
	
	int Mod()
	{
		int length=len();
		long long ans = num[length-1];
		for(int i=length-2; i>=0; i--)
		{
			ans*=digit;
			ans+=num[i];
			ans%=mod;
		}
		return ans%mod;
	}
};

long long power(long long a, long long b) //a^b
{
	if(!b) return 1ll;
	long long ret=power(a,b>>1ll);
	ret*=ret;
	ret%=mod;
	if(b&1ll)
	{
		ret*=a;
		ret%=mod;
	}
	return ret;
}

void run()
{
	a=readIn();
	b=readIn();
	k=readIn();
	n=readIn();
	m=readIn();

	int index = std::min(n,m);
	BigInt bi;
	bi.fact(k-index+1, k);
	bi.div(2,index);
	int ans = bi.Mod();
	ans = ans * power(a,n) % mod * power(b,m) % mod;
	printf("%d\n",ans);
}

int main()
{
	run();
	return 0;
}
