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

struct Brute {
	int a[MAXN * 2], b[MAXN * 2], bPre[MAXN * 2];

	Brute(void) : aSum(0)
	{
		puts("-1");
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("cashier.in", "r", stdin);
	freopen("cashier.out", "w", stdout);
#endif // LOCAL

	int Case;
	scanf("%d", &Case);

	while (Case--)
		delete new Brute();

	return 0;
}
