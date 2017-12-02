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

const INT maxn = 55;
INT n;
INT h[maxn];

void run()
{
	INT T = readIn();
	while(T--)
	{
		n = readIn();
		for(int i = 1; i <= n; i++)
		{
			h[i] = readIn();
		}
		std::sort(h + 1, h + 1 + n);

		INT ans = 0;
		INT minVal = h[1];
		std::deque<INT> q;
		q.push_back(h[1]);
		for(int i = 2; i <= n; i++)
		{
			if(q.back() <= q.front())
			{
				ans = std::max(ans, h[i] - q.back());
				q.push_back(h[i]);
			}
			else
			{
				ans = std::max(ans, h[i] - q.front());
				q.push_front(h[i]);
			}
		}

		q.clear();
		q.push_back(h[1]);
		for(int i = 2; i < n; i++)
		{
			if(h[i + 1] - q.front() <= ans)
			{
				q.push_back(h[i]);
			}
			else
			{
				q.push_front(h[i]);
			}
		}
		q.push_back(h[n]);

		INT minPos;
		for(int i = 0; i < n; i++)
		{
			if(q[i] == minVal)
			{
				minPos = i;
				break;
			}
		}
		cout << q[minPos];
		for(int i = minPos + 1; i < n; i++)
		{
			cout << ' ' << q[i];
		}
		for(int i = 0; i < minPos; i++)
		{
			cout << ' ' << q[i];
		}
		cout << endl;
	}
}

int main()
{
#ifndef JUDGE
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	run();
	return 0;
}
