#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <cfloat>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <set>
#include <map>
using namespace std;
const int MAXN = 1e7 + 5;

int n;

struct Brute {
	int Status[MAXN], Cnt;

	inline bool IsSame(int x, int y)
	{
		int xStatus = 0,
			yStatus = 0;

		if (Status[x] == 0) {
			while (x) {
				xStatus |= (1 << (x % 10));
				x /= 10;
			}
			Status[x] = xStatus;
		} else xStatus = Status[x];

		if (Status[y] == 0) {
			while (y) {
				yStatus |= (1 << (y % 10));
				y /= 10;
			}
			Status[y] = yStatus;
		} else yStatus = Status[y];

		return xStatus == yStatus;
	}

	Brute(void) : Status(), Cnt(0)
	{
		for (int i = 1; i <= n - 1; ++i)
			for (int j = i + 1; j <= n; ++j)
				if (IsSame(i, j))
					++Cnt;

		printf("%d\n", Cnt);
	}
};

struct Main : Brute {

	Main(void)
	{

	}
};

/*

	求数对 (x, y) 满足 x, y ∈ [1, n], x < y，x、y 使用了相同的数字

 */

int main(void)
{
#ifndef LOCAL
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
#endif // LOCAL

	scanf("%d", &n);

	delete new Brute();

	return 0;
}
