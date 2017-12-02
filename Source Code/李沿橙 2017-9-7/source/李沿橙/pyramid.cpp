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

const INT maxn = 20005;
const INT maxm = 105;
INT n, m;
INT num[maxn];

struct deque
{
	INT container[maxn];
	INT head, tail;

	deque() : container(), head(), tail() {}

	INT size() const
	{
		return tail - head;
	}
	INT& push_back(INT x)
	{
		container[tail++] = x;
	}
	void pop_back()
	{
		tail--;
	}
	void pop_front()
	{
		head++;
	}

	INT& front()
	{
		return container[head];
	}
	INT& front2()
	{
		return container[head + 1];
	}
	INT& back()
	{
		return container[tail - 1];
	}
	INT& back2()
	{
		return container[tail - 2];
	}
};

#define RunInstance(x) delete new x
struct work
{
	INT f[maxn][maxm];
	deque mono[maxm];

	INT up(INT param, INT s1, INT s2)
	{
		return f[s1][param] - f[s2][param];
	}
	INT down(INT s1, INT s2)
	{
		return s1 - s2;
	}

	work() : f()
	{
		//f[i][j] = std::max(f[i][j], f[k][j - 1] + num[i] * (i - k));
		m = std::min(n, m);

		f[1][1] = num[1];
		INT ans = f[1][m];
		mono[1].push_back(1);
		for(int i = 2; i <= n; i++)
		{
			f[i][1] = num[i] * i;
			while(mono[1].size() > 1 && up(1, i, mono[1].back()) * down(mono[1].back(), mono[1].back2()) >
			        down(i, mono[1].back()) * up(1, mono[1].back(), mono[1].back2()))
				mono[1].pop_back();
			mono[1].push_back(i);

			for(int j = 2; j <= m; j++)
			{
				while(mono[j - 1].size() > 1 &&
				        up(j - 1, mono[j - 1].front2(), mono[j - 1].front()) > num[i] *
				        down(mono[j - 1].front2(), mono[j - 1].front()))
					mono[j - 1].pop_front();

				f[i][j] = f[mono[j - 1].front()][j - 1] + num[i] * (i - mono[j - 1].front());

				while(mono[j].size() > 1 && up(j, i, mono[j].back()) * down(mono[j].back(), mono[j].back2()) >
				        down(i, mono[j].back()) * up(j, mono[j].back(), mono[j].back2()))
					mono[j].pop_back();
				mono[j].push_back(i);
			}
			ans = std::max(ans, f[i][m]);
		}
		cout << ans << endl;
	}
};

void run()
{
	n = readIn();
	m = readIn();
	INT all = 0;
	for(int i = 1; i <= n; i++)
	{
		INT l = readIn();
		INT r = readIn();
		num[i] = r - l + 1;
	}

	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("pyramid.in", "r", stdin);
	freopen("pyramid.out", "w", stdout);
#endif
	run();
	return 0;
}
