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

const INT maxn = 500005;
const INT mod = 1e9 + 7;
INT n;
INT A[maxn];
INT minTemp[maxn];
INT maxTemp[maxn];
INT minSum[maxn];
INT maxSum[maxn];
INT hybridSum[maxn];

void add(INT& x, const INT y)
{
	x += y;
	if (x >= mod) x -= mod;
}

INT divide(INT l = 1, INT r = n)
{
	if (l == r) return A[l] * A[l] % mod;
	INT mid = (l + r) >> 1;
	INT mul = 0;
	add(mul, divide(l, mid));
	add(mul, divide(mid + 1, r));

	minTemp[mid] = maxTemp[mid] = minSum[mid] = maxSum[mid] = hybridSum[mid] = 0;
	minSum[mid + 1] = minTemp[mid + 1] = A[mid + 1];
	maxSum[mid + 1] = maxTemp[mid + 1] = A[mid + 1];
	hybridSum[mid + 1] = minTemp[mid + 1] * maxTemp[mid + 1] % mod;
	for (int j = mid + 2; j <= r; j++)
	{
		minTemp[j] = std::min(minTemp[j - 1], A[j]);
		minSum[j] = minSum[j - 1];
		add(minSum[j], minTemp[j]);
		maxTemp[j] = std::max(maxTemp[j - 1], A[j]);
		maxSum[j] = maxSum[j - 1];
		add(maxSum[j], maxTemp[j]);
		hybridSum[j] = minTemp[j] * maxTemp[j] % mod;
		add(hybridSum[j], hybridSum[j - 1]);
	}

	INT minL = mid;
	INT maxL = mid;
	INT minR = mid;
	INT maxR = mid;
	for (int i = mid; i >= l; i--)
	{
		if (A[i] < A[minL]) minL = i;
		if (A[i] > A[maxL]) maxL = i;

		INT minTR = minR;
		INT maxTR = maxR;
		while (minTR + 1 <= r && minTemp[minTR + 1] >= A[minL]) minTR++;
		while (maxTR + 1 <= r && maxTemp[maxTR + 1] <= A[maxL]) maxTR++;

		if (minTR <= maxTR)
		{
			add(mul, A[minL] * A[maxL] % mod * (minTR - mid) % mod);
			add(mul, (minSum[maxTR] - minSum[minTR] + mod) * A[maxL] % mod);
			add(mul, (hybridSum[r] - hybridSum[maxTR] + mod) % mod);
		}
		else
		{
			add(mul, A[minL] * A[maxL] % mod * (maxTR - mid) % mod);
			add(mul, (maxSum[minTR] - maxSum[maxTR] + mod) * A[minL] % mod);
			add(mul, (hybridSum[r] - hybridSum[minTR] + mod) % mod);
		}
		minR = minTR;
		maxR = maxTR;
	}
	return mul;
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		A[i] = readIn();
	}
	cout << divide() << endl;
}

int main()
{
#ifndef JUDGE
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
#endif
	run();
	return 0;
}
