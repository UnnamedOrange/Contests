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
inline void printOut(INT x)
{
	char buffer[8];
	INT length = 0;
	do
	{
		buffer[length++] = x % 10 + '0';
	}
	while(x /= 10);
	do
	{
		putchar(buffer[--length]);
	}
	while(length);
}

INT Gcd(INT a, INT b)
{
	if(!b) return a;
	return Gcd(b, a % b);
}

const INT INF = ~(INT(1) << (sizeof(INT) * 8 - 1));
const INT maxn = 500005;
INT n;
INT a[maxn];

#define RunInstance(x) delete new x
struct work
{
	INT size;
	INT minVal[19][maxn];
	INT gcd[19][maxn];

	void goDouble()
	{
		for(int i = 1; i <= n; i++)
		{
			minVal[0][i] = a[i];
			gcd[0][i] = a[i];
		}

		while(1 << (size + 1) < n) size++;
		for(int i = 1; i <= size; i++)
		{
			for(int j = 1; j + (1 << i) - 1 <= n; j++)
			{
				minVal[i][j] = std::min(minVal[i - 1][j], minVal[i - 1][j + (1 << (i - 1))]);
				gcd[i][j] = Gcd(gcd[i - 1][j], gcd[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
	INT getMin(INT l, INT r)
	{
		INT k = 0;
		INT length = r - l + 1;
		while(1 << (k + 1) < length) k++;
		return std::min(minVal[k][l], minVal[k][r - (1 << k) + 1]);
	}
	INT getGcd(INT l, INT r)
	{
		INT k = 0;
		INT length = r - l + 1;
		while(1 << (k + 1) < length) k++;
		return Gcd(gcd[k][l], gcd[k][r - (1 << k) + 1]);
	}

	std::vector<INT> ans;

	bool check(INT L)
	{
		std::vector<INT> temp;
		INT to = n - L;
		for(int i = 1; i <= to; i++)
		{
			if(getMin(i, i + L) == getGcd(i, i + L)) temp.push_back(i);
		}
		if(temp.size()) ans = temp;
		return temp.size();
	}

	work() : minVal(), gcd(), size()
	{
		goDouble();

		INT l = 0, r = n - 1;
		while(r - l > 1)
		{
			INT mid = (l + r) >> 1;
			if(check(mid))
			{
				l = mid;
			}
			else
			{
				r = mid - 1;
			}
		}
		if(l != r && check(l + 1)) l++;

		printOut(ans.size());
		putchar(' ');
		printOut(l);
		putchar('\n');
		printOut(ans[0]);
		for(int i = 1; i < ans.size(); i++)
		{
			putchar(' ');
			printOut(ans[i]);
		}
	}
};
struct cheat
{
	cheat()
	{
		INT L = -1;
		std::vector<INT> ans;
		for(int i = 1; i <= n; i++)
		{
			INT minVal = a[i];
			INT g = a[i];
			INT length;
			for(int j = i; j <= n; j++)
			{
				minVal = std::min(minVal, a[j]);
				g = Gcd(g, a[j]);
				if(!(g % minVal)) length = j - i;
			}
			if(length > L)
			{
				L = length;
				ans.clear();
				ans.push_back(i);
			}
			else if(length == L)
			{
				ans.push_back(i);
			}
		}

		printOut(ans.size());
		putchar(' ');
		printOut(L);
		putchar('\n');
		printOut(ans[0]);
		for(int i = 1; i < ans.size(); i++)
		{
			putchar(' ');
			printOut(ans[i]);
		}
		putchar('\n');
	}
};
void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		a[i] = readIn();
	}

	if(n <= 3000) RunInstance(cheat);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("point.in", "r", stdin);
	freopen("point.out", "w", stdout);
#endif
	run();
	return 0;
}
