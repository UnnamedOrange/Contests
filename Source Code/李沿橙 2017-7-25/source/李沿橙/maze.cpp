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

const INT maxn = 1000005;
INT n, m, K;
INT value[maxn];
INT sum[maxn];
INT index[maxn];

bool comp(const INT& a, const INT& b)
{
	return value[a] > value[b];
}

void run()
{
	m = readIn();
	n = readIn();
	K = readIn();
	for(int i = 1; i <= n; i++)
	{
		value[i] = readIn();
		sum[i] = sum[i - 1] + value[i];
	}

	INT minRound = K / m + bool(K % m);
	INT maxRound = std::min(K, n);
	INT ans = 0;
	for(int i = minRound; i <= maxRound; i++)
	{
		for(int j = 1; j <= i; j++)
		{
			index[j] = j;
		}
		std::sort(index + 1, index + 1 + i, comp);
		INT steps = K - i;
		INT temp = sum[i];
		INT lowNum = 1;
		while(steps)
		{
			if(steps >= m - 1)
			{
				temp += value[index[lowNum]] * (m - 1);
				steps -= m - 1;
			}
			else
			{
				temp += value[index[lowNum]] * steps;
				steps = 0;
			}
			lowNum++;
		}
		ans = std::max(ans, temp);
	}
	cout << ans << endl;
}

int main()
{
#ifndef DEBUG
	freopen("maze.in", "r", stdin);
	freopen("maze.out", "w", stdout);
#endif
	run();
	return 0;
}
