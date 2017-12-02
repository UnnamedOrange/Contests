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
const int MAXN = 405;

int n, m, k;

struct Brute_1 {
	int SumRgt[MAXN][MAXN], SumDown[MAXN][MAXN], Sum[MAXN][MAXN],
		Map[MAXN][MAXN];
	long long Cnt;

	struct Coord {
		int x, y;

		bool operator <= (const Coord &a) const
		{
			return x <= a.x && y <= a.y;
		}

		Coord(void) {}

		Coord(int x, int y) : x(x), y(y) {}
	};

	inline int GetSum(Coord c_1, Coord c_2)
	{
		return Sum[c_2.x][c_2.y] + Sum[c_1.x - 1][c_1.y - 1] -
			Sum[c_1.x - 1][c_2.y] - Sum[c_2.x][c_1.y - 1];
	}

	inline Coord Idx2Crd(int Idx)
	{
		Coord Result;
		Result.x = ceil((double)Idx / m);
		Result.y = Idx - (Result.x - 1) * m;

		return Result;
	}

	int Gcd(int x, int y)
	{
		return y == 0 ? x : Gcd(y, x % y);
	}

	Brute_1(void) : Sum(), SumRgt(), SumDown(), Map(), Cnt(0)
	{
		bool IsSame = true;
		int Last = -1;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &Map[i][j]);

				if (IsSame)
					if (Last == -1) Last = Map[i][j];
					else if (Last != Map[i][j])
						IsSame = false;

				SumRgt[i][j] = SumRgt[i][j - 1] + Map[i][j];
				SumDown[i][j] = SumDown[i - 1][j] + Map[i][j];

				Sum[i][j] = SumRgt[i][j] + SumDown[i][j] - Map[i][j] +
					Sum[i - 1][j - 1];
			}

		if (IsSame) {
			if (Gcd(Map[1][1], k) == k)
				printf("%lld\n",
					(long long)n * (n + 1) * m * (m + 1) / 4);
			else {
				for (int i = k; i <= n; i += k)
					for (int j = 1; j <= m; ++j) {
						if (Gcd(j, k) == k) continue;
						Cnt += (n - i + 1) * (m - j + 1);
					}

				for (int j = k; j <= m; j += k)
					for (int i = 1; i <= n; ++i)
						Cnt += (n - i + 1) * (m - j + 1);

				printf("%lld\n", Cnt);
			}

			return;
		}

		int Limit = n * m;
		for (int i = 1; i <= Limit; ++i)
			for (int j = i; j <= Limit; ++j) {
				Coord a = Idx2Crd(i),
					b = Idx2Crd(j);

				if (a <= b &&
					Gcd(GetSum(a, b), k) == k)
					++Cnt;
			}

		printf("%lld\n", Cnt);
	}
};

struct Brute_2 {
	// 准备写枚举优化

	Brute_2(void)
	{

	}
};

int main(void)
{
#ifndef LOCAL
	freopen("rally.in", "r", stdin);
	freopen("rally.out", "w", stdout);
#endif // LOCAL

	scanf("%d %d %d", &n, &m, &k);

	if (k == 1)
		printf("%lld\n", (long long)n * (n + 1) * m * (m + 1) / 4);
	else
		delete new Brute_1();

	return 0;
}
