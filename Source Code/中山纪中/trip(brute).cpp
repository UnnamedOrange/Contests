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

INT n, m;
std::vector<INT> origin;

void run()
{
	n = readIn();
	m = readIn();
	origin.resize(n + 1);
	for (int i = 1; i <= n; i++)
	{
		origin[i] = readIn();
	}
	while (m--)
	{
		INT l = readIn();
		INT r = readIn();

		INT ans = -1;
		std::stack<INT> mono;
		mono.push(origin[l]);
		for (int i = l + 1; i <= r; i++)
		{
			while (!mono.empty() && mono.top() < origin[i])
				mono.pop();
			mono.push(origin[i]);
		}
		ans += mono.size();
		while (!mono.empty()) mono.pop();
		mono.push(origin[r]);
		for (int i = r - 1; i >= l; i--)
		{
			while (!mono.empty() && mono.top() < origin[i])
				mono.pop();
			mono.push(origin[i]);
		}
		ans += mono.size();

		printf("%d\n", ans);
	}
}

int main()
{
#ifndef JUDGE
	freopen("trip.in", "r", stdin);
	freopen("trip.out", "w", stdout);
#endif
	run();
	return 0;
}
