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
	bool minus = false;
	INT a = 0;
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

const INT mod = 99999997;
const INT maxn = 100005;
INT n;
struct info
{
	INT height;
	INT index;
	INT sortIndex;
} infos[2][maxn];
bool comp1(const info& a, const info& b)
{
	return a.height < b.height;
}
bool comp2(const info& a, const info& b)
{
	return a.index < b.index;
}
INT sequence[2][maxn];
INT temp[maxn];
INT ans;

void mergesort(INT x, INT y)
{
	if (y - x == 1) return;
	INT mid = (x + y) / 2;
	mergesort(x, mid);
	mergesort(mid, y);
	INT i = x;
	INT j = mid;
	INT k = x;
	while (i < mid || j < y)
	{
		if (j >= y || i < mid && sequence[1][i] <= sequence[1][j])
		{
			temp[k++] = sequence[1][i++];
		}
		else
		{
			ans += mid - i;
			temp[k++] = sequence[1][j++];
		}
	}
	for (i = x; i < y; i++)
	{
		sequence[1][i] = temp[i];
	}
}

void run()
{
	n = readIn();
	for (int i = 0; i < n; i++)
	{
		infos[0][i].height = readIn();
		infos[0][i].index = i;
	}
	for (int i = 0; i < n; i++)
	{
		infos[1][i].height = readIn();
		infos[1][i].index = i;
	}
	std::sort(infos[0], infos[0] + n, comp1);
	for (int i = 0; i < n; i++)
	{
		infos[0][i].sortIndex = i;
	}
	std::sort(infos[0], infos[0] + n, comp2);

	std::sort(infos[1], infos[1] + n, comp1);
	for (int i = 0; i < n; i++)
	{
		infos[1][i].sortIndex = i;
	}
	std::sort(infos[1], infos[1] + n, comp2);

	for (int i = 0; i < n; i++)
	{
		sequence[0][infos[0][i].sortIndex] = i;
	}
	for (int i = 0; i < n; i++)
	{
		sequence[1][i] = sequence[0][infos[1][i].sortIndex];
	}

	mergesort(0, n);
	cout << ans % mod << endl;
}

int main()
{
	run();
	return 0;
}