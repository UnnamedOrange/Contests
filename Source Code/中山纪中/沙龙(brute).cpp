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

const INT maxn = 100005;
INT n;
INT seq[maxn];
bool isWdf(INT x)
{
	if (!x) return false;
	while (x)
	{
		if (x % 10 != 4 && x % 10 != 7) return false;
		x /= 10;
	}
	return true;
}
INT ans;

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		seq[i] = readIn();
	}
	for (int i = 1; i <= n; i++)
	{
		std::set<INT> wdf;
		for (int j = i; j <= n; j++)
		{
			if (isWdf(seq[j])) wdf.insert(seq[j]);
			for (int k = j + 1; k <= n; k++)
			{
				for (int l = k; l <= n; l++)
				{
					if (isWdf(seq[l]) && wdf.count(seq[l])) break;
					ans++;
				}
			}
		}
	}
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
