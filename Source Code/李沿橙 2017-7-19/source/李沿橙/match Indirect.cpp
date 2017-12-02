//Indirect sort
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
INT height1[maxn];
INT index1[maxn];
INT height2[maxn];
INT index2[maxn];
bool comp1(const INT& a, const INT& b)
{
	return height1[a] < height1[b];
}
bool comp2(const INT& a, const INT& b)
{
	return height2[a] < height2[b];
}
INT sequence[maxn];
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
		if (j >= y || i < mid && sequence[i] <= sequence[j])
		{
			temp[k++] = sequence[i++];
		}
		else
		{
			ans += mid - i;
			temp[k++] = sequence[j++];
		}
	}
	for (i = x; i < y; i++)
	{
		sequence[i] = temp[i];
	}
}

void run()
{
	n = readIn();
	for (int i = 0; i < n; i++)
	{
		height1[i] = readIn();
		index1[i] = i;
	}
	for (int i = 0; i < n; i++)
	{
		height2[i] = readIn();
		index2[i] = i;
	}
	std::sort(index1, index1 + n, comp1);
	std::sort(index2, index2 + n, comp2);

	for (int i = 0; i < n; i++)
	{
		sequence[index1[i]] = index2[i];
	}

	mergesort(0, n);
	cout << ans % mod << endl;
}

int main()
{
	run();
	return 0;
}
