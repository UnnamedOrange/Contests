#pragma G++ optimize("O3")
#pragma GCC optimize("O3")

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
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
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT mod = INT(1e9) + 7;
INT n, m;
struct Matrix
{
	static const INT maxn = 100;
	INT N;
	INT r[maxn][maxn];
	Matrix(INT N = 0) : N(N), r() {}
	Matrix(INT N, INT unit) : N(N), r()
	{
		for (int i = 0; i < N; i++)
		{
			r[i][i] = unit;
		}
	}

	inline Matrix operator* (const Matrix& b)
	{
		Matrix ret(N);
		for (int i = 0; i < N; i++)
		{
			for (int k = 0; k < N; k++)
			{
				if (!r[i][k]) continue;
				for (int j = 0; j < N; j++)
				{
					ret.r[i][j] += r[i][k] * b.r[k][j] % mod;
					if (ret.r[i][j] >= mod) ret.r[i][j] -= mod;
				}
			}
		}
		return ret;
	}

	inline Matrix operator^ (INT b)
	{
		Matrix temp(*this);
		Matrix ret(N, 1);
		while (b)
		{
			if (b & 1) ret = ret * temp;
			temp = temp * temp;
			b >>= 1;
		}
		return ret;
	}
} origin;

void run()
{
	n = readIn();
	m = readIn();

	origin.N = m - 1;
	//initialize the Matrix
	for (int i = 0; i < m - 1; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			origin.r[i][j] = 1;
		}
	}
	for (int i = 1; i < m - 1; i++)
	{
		origin.r[i - 1][i] = m - i;
	}

	//quick power
	origin = origin ^ (n - 1);

	INT ans = 0;
	for (int i = 0; i < m - 1; i++)
	{
		ans += origin.r[0][i];
		if (ans >= mod) ans -= mod;
	}
	printf("%lld\n", ans * m % mod);
}

int main()
{
	run();
	return 0;
}