#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;
#define FOR(x, f, t) for(int x = (f); x <= (t); x++)
inline int readIn()
{
	int a;
	scanf("%d",&a);
	return a;
}

const int maxn = 1005;
int n;
int kingA, kingB;
struct People
{
	int A;
	int B;

	void input()
	{
		A=readIn();
		B=readIn();
	}

	bool operator< (const People& b) const
	{
		return A*B < b.A*b.B;
	}
} people[maxn];
struct BigInt
{
	static const int digit = 1e9;
	static const int size = 445;
	std::vector<long long> num;
	int length;

	BigInt(int init = -1)
	{
		if(init==-1)
		{
			num.resize(size,digit-1);
			length = size;
		}
		else
		{
			num.resize(size);
			num[0] = init;
			length = bool(init);
		}
	}
	void operator*= (int b)
	{
		for(int i=0; i<length; i++)
		{
			num[i]*=b;
		}
		for(int i=0; i<length; i++)
		{
			num[i+1]+=num[i]/digit;
			num[i]%=digit;
		}
		if(num[length]) length++;
	}
	void operator/= (int b)
	{
		long long div = 0;
		long long mod = 0;
		for(int i=length-1; i>=0; i--)
		{
			num[i]+=mod * digit;
			mod = num[i] % b;
			num[i] = num[i] / b;
		}
		if(length && !num[length - 1]) length--;
	}
	BigInt operator/ (int b)
	{
		BigInt ret = *this;
		ret/=b;
		return ret;
	}
	bool operator< (const BigInt& b) const
	{
		if(length<b.length) return true;
		else if(length>b.length) return false;
		for(int i=length-1; i>=0; i--)
		{
			if(num[i]<b.num[i]) return true;
			else if(num[i]>b.num[i]) return false;
		}
		return false;
	}
	void print()
	{
		if(length) printf("%lld",num[length-1]);
		else printf("0");
		for(int i = length-2; i>=0; i--)
		{
			printf("%09lld",num[i]);
		}
		puts("");
	}
};

void run()
{
	n=readIn();
	kingA=readIn();
	kingB=readIn();
	FOR(i, 1, n)
	{
		people[i].input();
	}
	std::sort(people+1, people+1+n);

	BigInt ans = 0;
	BigInt mul = kingA;
	FOR(i, 1, n)
	{
		ans = std::max(ans, mul / people[i].B);
		mul*=people[i].A;
	}
	ans.print();
}

int main()
{
	run();
	return 0;
}
