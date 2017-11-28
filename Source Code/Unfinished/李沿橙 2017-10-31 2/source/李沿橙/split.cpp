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
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	char buffer[15];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	}
	while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	}
	while (length);
	putchar('\n');
}

const INT mod = INT(1e9) + 7;
INT n;
struct Matrix
{
	static const INT maxn = 10;
	INT r[maxn][maxn];
	INT* operator[](INT x)
	{
		return r[x];
	}
	const INT* operator[](INT x) const
	{
		return r[x];
	}
	Matrix() : r() {}
	Matrix(bool unit) : r()
	{
		for(int i = 0; i < maxn; i++)
			r[i][i] = 1;
	}
	Matrix operator*(const Matrix& b) const
	{
		const Matrix& a = *this;
		Matrix ret;
		for(int i = 0; i < maxn; i++)
		{
			for(int k = 0; k < maxn; k++)
			{
				if(a[i][k])
				{
					for(int j = 0; j < maxn; j++)
					{
						ret[i][j] = (ret[i][j] + a[i][k] * b[k][j]) % mod;
					}
				}
			}
		}
		return ret;
	}
	Matrix operator^ (INT y) const
	{
		Matrix ret(true);
		Matrix x(*this);
		while(y)
		{
			if(y & 1) ret = ret * x;
			x = x * x;
			y >>= 1;
		}
		return ret;
	}
} transfit;

void run()
{
	for(int i = 1; i < Matrix::maxn; i++)
		transfit[i][0] = 1;
	for(int i = 1; i < Matrix::maxn; i++)
		transfit[i - 1][i] = 1;

	INT T = readIn();
	while(T--)
	{
		n = readIn();
		Matrix f = transfit ^ n;
		INT ans = 0;
		for(int i = 0; i < Matrix::maxn; i++)
			ans = (ans + f[0][i]) % mod;
		printOut(ans);
	}
}

int main()
{
#ifndef JUDGE
	freopen("split.in", "r", stdin);
	freopen("split.out", "w", stdout);
#endif
	run();
	return 0;
}
