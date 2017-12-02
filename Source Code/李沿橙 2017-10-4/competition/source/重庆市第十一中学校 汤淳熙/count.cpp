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
const long long	MOD = 998244353;

int F, T, k;
int Pow[MAXN] = { 0 };

struct Brute {
	inline int f(int x) { return x == 1 ? 2 : x; }

	long long PowerMod(int a, int n)
	{
		long long Answer = 1, Temp = a;
		while (n) {
			if (n & 1)
				Answer = (Answer * Temp) % MOD;

			n >>= 1;
			Temp = ((Temp % MOD) * (Temp % MOD)) % MOD;
		}

		return Answer;
	}

	Brute(void)
	{
		long long Sum = 0;
		for (int i = F; i <= T; ++i)
			Sum = (Sum + PowerMod(f(i), k)) % MOD;

		printf("%lld\n", Sum);
	}
};

struct Main : Brute {

	Main(void) {}
};

int main(void)
{
#ifndef LOCAL
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
#endif // LOCAL

	scanf("%d %d %d", &F, &T, &k);

	if (T <= 1e7)
		delete new Brute();
	else
		delete new Main();

	return 0;
}
