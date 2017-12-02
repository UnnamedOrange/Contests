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

const INT maxn = 1005;
const INT maxh = 24;
INT a[maxh + 5];
INT b[maxh + 5];

#define RunInstance(x) delete new x
struct cheat1
{
	INT n;
	INT st[30];
	INT count1[1 << 20];

	cheat1() : n(), st(), count1()
	{
		for(int i = 1; i <= maxh; i++)
		{
			for(int j = 1; j <= b[i]; j++)
			{
				st[n++] = i;
			}
		}

		INT ans = -1;
		INT U = 1 << n;
		for(int i = 1; i < U; i++)
		{
			count1[i] = count1[i ^ (i & -i)] + 1;
		}
		for(int S = 0; S < U; S++)
		{
			if(~ans && count1[S] >= ans) continue;
			INT sign[40] = { 0 };
			for(int i = 0; i < n; i++)
			{
				if(S & (1 << i))
				{
					sign[st[i]]++;
					sign[st[i] + 8]--;
				}
			}
			for(int i = 1; i <= 32; i++)
			{
				sign[i] += sign[i - 1];
			}
			for(int i = 1; i <= 7; i++)
			{
				sign[i] += sign[i + maxh];
			}
			bool bOk = true;
			for(int i = 1; i <= maxh; i++)
			{
				if(sign[i] < a[i])
				{
					bOk = false;
					break;
				}
			}
			if(!bOk) continue;
			ans = count1[S];
		}
		cout << ans << endl;
	}
};
struct work
{

};

void run()
{
	INT T = readIn();
	while(T--)
	{
		INT n = 0;
		for(int i = 1; i <= maxh; i++)
		{
			a[i] = readIn();
		}
		for(int i = 1; i <= maxh; i++)
		{
			b[i] = readIn();
			n += b[i];
		}

		if(n <= 20 && !T) RunInstance(cheat1);
		else RunInstance(work);
	}
}

int main()
{
#ifndef JUDGE
	freopen("cashier.in", "r", stdin);
	freopen("cashier.out", "w", stdout);
#endif
	run();
	return 0;
}
