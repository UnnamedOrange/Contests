#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <cfloat>
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
const int MAXN = 1e3 + 5;

int n, m;

struct Brute_1 {
	map<int, int> Cvt;
	int BIT[MAXN][MAXN], Idx = 0;

	inline int LowBit(int x)
	{
		return x & (-x);
	}

	void Edit(int Where, int x, int Add)
	{
		for (int i = x; i <= n; i += LowBit(i))
			BIT[Where][i] += Add;
	}

	int SumMore(int Where, int x)
	{
		int Result = 0;

		for (int i = x; i > 0; i -= LowBit(i))
			Result += BIT[Where][i];

		return Result;
	}

	int Sum(int Where, int From, int To = -1)
	{
		if (To == -1) To = From;

		return SumMore(Where, To) -
			SumMore(Where, From - 1);
	}

	Brute_1(void) : BIT()
	{
		for (int i = 1; i <= n; ++i) {
			int x;
			scanf("%d", &x);

			if (Cvt[x] == 0)
				Cvt[x] = ++Idx;

			Edit(Cvt[x], i, 1);
		}

		while (m--) {
			int Type;
			scanf("%d", &Type);

			if (Type == 1) {
				int From, To, Colour;
				scanf("%d %d %d", &From, &To, &Colour);

				int CvtIdx = Cvt[Colour];

				printf("%d\n",
					Sum(CvtIdx, From, To));
			} else if (Type == 2) {
				int x;
				scanf("%d", &x);

				int aIdx = -1, bIdx = -1;
				for (int i = 1; i <= Idx; ++i)
					if (Sum(i, x) == 1) {
						aIdx = i;
						break;
					}
				for (int i = 1; i <= Idx; ++i)
					if (Sum(i, x + 1) == 1) {
						bIdx = i;
						break;
					}

				Edit(aIdx, x, -1);
				Edit(aIdx, x + 1, 1);

				Edit(bIdx, x, 1);
				Edit(bIdx, x + 1, -1);
			}
		}
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
#endif // LOCAL

	scanf("%d %d", &n, &m);

	delete new Brute_1();

	return 0;
}
