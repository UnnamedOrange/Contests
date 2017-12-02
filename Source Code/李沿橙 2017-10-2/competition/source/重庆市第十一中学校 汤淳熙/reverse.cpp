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
const int MAXL = 1e5 + 5;

char s[MAXL];
int n;

struct Main {
	int Sum[MAXL];

	inline int Black(int From, int To)
	{
		return To - Sum[To] - From + Sum[From - 1] + 1;
	}

	inline int White(int From, int To)
	{
		return Sum[To] - Sum[From - 1];
	}

	int Work(int From, int To)
	{
		if (From == To) return 0;

		int Half = (From + To) / 2;

		return min(Work(From, Half) + Black(Half + 1, To),
			Work(Half + 1, To) + White(From, Half));
	}

	Main(void) : Sum()
	{
		for (int i = 1; i <= n; ++i)
			Sum[i] = Sum[i - 1] + s[i] - '0';

		printf("%d\n", Work(1, n));
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);
#endif // LOCAL

	scanf("%s", s + 1);
	n = strlen(s + 1);

	delete new Main();

	return 0;
}
