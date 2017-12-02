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
const int MAXN = 1e5 + 5;

struct Main {
	long long xLine[MAXN], yLine[MAXN];

	Main(void)
	{
		int n;
		scanf("%d", &n);

		for (int i = 1; i <= n; ++i)
			scanf("%lld", xLine + i);
		for (int i = 1; i <= n; ++i)
			scanf("%lld", yLine + i);

		sort(xLine + 1, xLine + n + 1);
		sort(yLine + 1, yLine + n + 1);

		int Qry;
		scanf("%d", &Qry);

		while (Qry--) {
			int x, y;
			scanf("%d %d", &x, &y);

			int Lft = 1, Rgt = n;

			while (Lft <= Rgt) {
				int Mdl = (Lft + Rgt) / 2;

				if (xLine[Mdl] * y +
					yLine[Mdl] * x >=
					xLine[Mdl] * yLine[Mdl])
					Lft = Mdl + 1;
				else Rgt = Mdl - 1;
			}

			 printf("%d\n", Rgt);
		}
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("geometry.in", "r", stdin);
	freopen("geometry.out", "w", stdout);
#endif // LOCAL

	delete new Main();

	return 0;
}
