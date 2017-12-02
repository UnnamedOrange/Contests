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
const int MAXN = 2e6;

int Height[MAXN];

enum {
	Begin, Peak, Trough
};

int main(void)
{
#ifndef LOCAL
	freopen("wave.in", "r", stdin);
	freopen("wave.out", "w", stdout);
#endif

	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; ++i)
		scanf("%d %d", &Height[i]);

	int Count = 0, Status = Peak;
	for (int i = 2; i <= n; ++i) {
		if (Height[i] - Height[i - 1] >= k)
			if (Status != Peak) {
				++Count;
				Status = Peak;
			}
		if (Height[i] - Height[i - 1] <= k)
			if (Status != Trough) {
				++Count;
				Status = Trough;
			}
	}

	cout << Count << endl;

	return 0;
}

/*

10 3
2 6 7 9 0 3 7 6 4 4

 */
