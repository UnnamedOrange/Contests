#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
#include <list>
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int mod = 998244353;
const int maxn = int(3e4) + 5;
int n, m;

LL power(LL x, int y)
{
	LL ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}
int fac[maxn];
int invFac[maxn];
int power2[maxn];
void init()
{
	int to = 3e4;
	fac[0] = 1;
	for (int i = 1; i <= to; i++)
		fac[i] = (LL)fac[i - 1] * i % mod;
	invFac[to] = power(fac[to], mod - 2);
	for (int i = to - 1; ~i; i--)
		invFac[i] = (LL)invFac[i + 1] * (i + 1) % mod;

	power2[0] = 1;
	for (int i = 1; i <= to; i++)
		power2[i] = (power2[i - 1] << 1) % mod;
}
inline LL C(int down, int up)
{
	return down < up ? 0 : (LL)fac[down] * invFac[up] % mod * invFac[down - up] % mod;
}

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 305;
	int f[maxN][maxN];

	brute() : f()
	{
		f[0][0] = 1;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				for (int k = 0; k < j; k++) if (f[i - 1][k])
				{
					f[i][j] = (f[i][j] +
						(LL)power2[k] * C(j, k) % mod * f[i - 1][k]) % mod;
				}
		LL ans = 0;
		for (int i = 0; i <= m; i++)
			ans = (ans + (LL)f[n][i] * C(m, i)) % mod;
		printOut(ans);
	}
};
struct work
{
	typedef std::vector<int> Base;
	struct Poly : public Base
	{
		Poly() : Base(1) {}
		Poly(int size) : Base(size) {}
		void shrink()
		{
			while (size() > 1 && !back())
				pop_back();
		}
		static const int root = 3;
		static const int limit = 23;
		static const int base = 119;
		static void NTT(int* a, int logn, bool INTT)
		{
			static int revbit[1 << 16];
			int n = 1 << logn;
			for (int i = 1; i < n; i++)
				revbit[i] = (revbit[i >> 1] >> 1) | ((i & 1) << (logn - 1));
			for (int i = 1; i < n; i++)
				if (i < revbit[i])
					std::swap(a[i], a[revbit[i]]);

			for (int i = 1; i <= logn; i++)
			{
				int S = 1 << i;
				int half = S >> 1;
				int g1 = power(root, base * (1 << (limit - i)));
				if (INTT) g1 = power(g1, mod - 2);
				for (int j = 0; j < n; j += S)
				{
					int* A = a + j;
					int g = 1;
					for (int k = 0; k < half; k++)
					{
						register int temp;
						register int t = (LL)g * A[k + half] % mod;
						A[k + half] = (temp = A[k] - t) < 0 ? temp + mod : temp;
						A[k] = (temp = A[k] + t) >= mod ? temp - mod : temp;
						g = (LL)g * g1 % mod;
					}
				}
			}
			if (INTT)
			{
				int inv = power(n, mod - 2);
				for (int i = 0; i < n; i++)
					a[i] = (LL)a[i] * inv % mod;
			}
		}
		Poly operator*(const Poly& c) const
		{
			static int a[1 << 16];
			static int b[1 << 16];
			Poly ret(size() + c.size() - 1);
			int logn = 0;
			while (1 << logn < ret.size()) logn++;
			int n = 1 << logn;
			std::memcpy(a, data(), sizeof(int) * size());
			std::memset(a + size(), 0, sizeof(int) * (n - size()));
			std::memcpy(b, c.data(), sizeof(int) * c.size());
			std::memset(b + c.size(), 0, sizeof(int) * (n - c.size()));
			NTT(a, logn, false);
			NTT(b, logn, false);
			for (int i = 0; i < n; i++)
				a[i] = (LL)a[i] * b[i] % mod;
			NTT(a, logn, true);
			std::memcpy(ret.data(), a, sizeof(int) * ret.size());
			ret.shrink();
			return ret;
		}
		void Mod(int s)
		{
			if (size() <= s) return;
			resize(s);
		}
	};

	Poly solve(int n)
	{
		Poly ret;
		if (n == 1)
		{
			ret.resize(m + 1);
			ret[0] = 0;
			for (int i = 1; i <= m; i++)
				ret[i] = invFac[i];
			return ret;
		}
		Poly half = solve(n >> 1);
		Poly half2 = half;
		for (int i = 0, mul = power2[n >> 1], pwr = 1; i < half2.size(); i++, pwr = (LL)pwr * mul % mod)
			half2[i] = (LL)half2[i] * pwr % mod;
		ret = half * half2;
		ret.Mod(m + 1);
		if (n & 1)
		{
			half.resize(m + 1);
			half[0] = 0;
			for (int i = 1, mul = power2[n - 1], pwr = mul; i < half.size(); i++, pwr = (LL)pwr * mul % mod)
				half[i] = (LL)pwr * invFac[i] % mod;
			ret = ret * half;
			ret.Mod(m + 1);
		}
		return ret;
	}

	work()
	{
		Poly f = solve(n);
		f.resize(m + 1);
		LL ans = 0;
		for (int i = 0; i <= m; i++)
			ans = (ans + (LL)f[i] * fac[i] % mod * C(m, i)) % mod;
		printOut(ans);
	}
};

void run()
{
	init();
	n = readIn();
	m = readIn();

	if (n <= 300 && m <= 300)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("or.in", "r", stdin);
	freopen("or.out", "w", stdout);
#endif
	run();
	return 0;
}