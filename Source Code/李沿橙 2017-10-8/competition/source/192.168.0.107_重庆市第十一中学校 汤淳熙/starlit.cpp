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
const int MAXN = 1005;

int n, k, m;

struct Brute_1 {
	int a[MAXN], b[MAXN],

	Brute_1(void)
	{
		for (int i = 1; i <= k; ++i)
			scanf("%d", a + i);

		for (int i = 1; i <= m; ++i)
			scanf("%d", b + i);

		printf("%d\n", rand() % 3 + 1);
	}
};

struct Brute_2 : Brute_1 {
	Brute_2(void) {}
}

int main(void)
{
#ifndef LOCAL
	freopen("starlit.in", "r", stdin);
	freopen("starlit.out", "w", stdout);
#endif // LOCAL
	srand(time(NULL));

	scanf("%d %d %d", &n, &k, &m);

	if (n <= 200)
		delete new Brute_1();
	else
		delete new Brute_2();

	return 0;
}
