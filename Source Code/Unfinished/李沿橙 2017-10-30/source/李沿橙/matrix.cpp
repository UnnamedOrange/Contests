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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

INT n, m, q;
INT k;
#define RunInstance(x) delete new x
struct brute
{
	std::vector<INT> a;

	brute()
	{
		a.reserve(n * m);
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
				a.push_back(i * j);
		std::partial_sort(a.begin(), a.begin() + n, a.end());
		while (q--)
		{
			printOut(a[readIn() - 1]);
		}
	}
};
struct cheat
{
	static const INT maxn = INT(1e6) + 5;

	struct Object
	{
		INT num;
		INT j;
		Object() {}
		Object(INT num, INT j) : num(num), j(j) {}
		Object next()
		{
			return Object(num + j, j);
		}
		bool operator< (const Object& b) const
		{
			if (num != b.num) return num > b.num;
			return j > b.j;
		}
	};
	std::priority_queue<Object> pq;
	INT ans[maxn];

	cheat()
	{
		for (int i = 1; i <= n; i++)
			pq.push(Object(i, i));

		for (int i = 1; i <= n; i++)
		{
			Object t = pq.top();
			pq.pop();
			ans[i] = t.num;
			if (t.num / t.j < m) pq.push(t.next());
		}
		while (q--)
		{
			printOut(ans[readIn()]);
		}
	}
};
struct work
{
	bool check(INT s)
	{
		register long long ret = 0;
		register INT temp;
		for (register int i = 1; i <= s; i = temp + 1)
		{
			temp = s / (s / i);
			ret += (temp - i + 1) * (s / i);
		}
		return ret < k;
	}
	work()
	{
		while (q--)
		{
			k = readIn();
			INT l = 1, r = k;
			while (r - l > 0)
			{
				INT mid = (l + r) >> 1;
				if (check(mid)) l = mid + 1;
				else r = mid;
			}
			printOut(l);
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	q = readIn();
	if (n < m) std::swap(n, m);

	if (n <= 1000 && m <= 1000)
		RunInstance(brute);
	else if (n <= 5000 && m <= 5000)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
#endif
	run();
	return 0;
}
