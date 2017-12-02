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
typedef long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT maxn = INT(1e7) + 5;
INT n;

#define RunInstance(x) delete new x
struct work
{
	static const INT size = (1 << 10) + 5;
	INT nCode[size];
	INT code[maxn];

	static inline INT C_2(INT x)
	{
		return x < 2 ? 0 : x * (x - 1) / 2;
	}

	work() : nCode(), code()
	{
		for(int i = 1; i <= 10; i++)
		{
			code[i] = 1 << i;
		}
		bool working = true;
		for(int i = 1; working; i++)
		{
			for(int j = 0; working && j < 10; j++)
			{
				INT num = i * 10 + j;
				code[num] = code[i] | (1 << j);
				if(num >= n) working = false;
			}
		}
		for(int i = 1; i <= n; i++)
		{
			nCode[code[i]]++;
		}

		INT ans = 0;
		INT to = 1 << 10;
		for(int i = 1; i < to; i++)
		{
			ans += C_2(nCode[i]);
		}
		cout << ans << endl;
	}
};

void run()
{
	n = readIn();
	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
#endif
	run();
	return 0;
}
