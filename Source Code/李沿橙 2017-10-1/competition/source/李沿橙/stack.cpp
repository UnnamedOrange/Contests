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
#include <bitset>
using std::cin;
using std::cout;
using std::endl;
typedef int INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();

	while(!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();

	if(ch == '-')
	{
		minus = true;
		ch = getchar();
	}

	while(ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}

	if(minus) a = -a;

	return a;
}

const INT mod = 7;
const INT maxn = 1005;
INT n;

#define RunInstance(x) delete new x
struct work
{
	INT f[maxn];

	work() : f()
	{
		f[0] = 1;
		f[1] = 1;
		for(int i = 2; i <= n; i++)
		{
			for(int j = 0; j < i; j++)
			{
				f[i] = (f[i] + f[j] * f[i - j - 1] % mod) % mod;
			}
		}
		cout << f[n] << endl;
	}
};
struct cheat
{
	INT ans;
	INT count_;
	INT in;
	void search(INT depth = 0)
	{
		if(depth == n * 2)
		{
			ans++;
			return;
		}

		if(count_ != n)
		{
			count_++;
			in++;
			search(depth + 1);
			in--;
			count_--;
		}

		if(in)
		{
			in--;
			search(depth + 1);
			in++;
		}
	}
	cheat() : ans(), count_(), in()
	{
		search();
		cout << ans % mod << endl;
	}
};

void run()
{
	n = readIn();
//	if(n <= 15) RunInstance(cheat);
//	else
	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("stack.in", "r", stdin);
	freopen("stack.out", "w", stdout);
#endif
	run();
	return 0;
}
