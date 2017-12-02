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
const int MAXN = 1e8 + 5;

int n, m,
	Array[MAXN];

struct Brute_1 {

	Brute_1(void)
	{

	}
};

int main(void)
{
#ifndef LOCAL
	freopen("blocks.out", "w", stdout);
	freopen("blocks.in", "r", stdin);
#endif // LOCAL

	scanf("%d %d", &n, &m);

	int Sum = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &Array[i]);
		Sum += Array[i];
	}

	while (m--) {
		int k;
		scanf("%d", &k);
		
		if (k >= n) printf("0 ");
		else printf("%d ", (n - k) * 2 > n ? n : (n - k) * 2);
	}

	return 0;
}

/*

10 5
1 7 9 9 5 9 3 4 5 8
5 7 20 9 1

 */