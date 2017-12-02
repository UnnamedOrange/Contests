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

const INT maxn = 45;
INT n, m;
INT cost[maxn];
INT ans;

void cheat2()
{
	INT* f = (INT*)calloc(sizeof(INT), m + 1);
	f[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = m; j >= cost[i]; j--)
		{
			f[j] += f[j - cost[i]];
		}
	}
	for (int i = 0; i <= m; i++)
	{
		ans += f[i];
	}
	cout << ans << endl;
	free(f);
}
void cheat1()
{
	INT U = (1 << n) - 1;
	INT* costSum = (INT*)calloc(sizeof(INT), U + 1);
	costSum[0] = 0;
	ans = 1;
	for (int S = 1; S <= U; S++)
	{
		INT pos = 0;
		while (!(S & (1 << pos))) pos++;
		costSum[S] = costSum[S ^ (1 << pos)] + cost[pos + 1];
		if (costSum[S] <= m) ans++;
	}
	cout << ans << endl;
	free(costSum);
}

INT len1, len2;
INT seq1[maxn];
INT seq2[maxn];
INT costSum1[(1 << 20) + 5];
INT costSum2[(1 << 20) + 5];

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
	{
		cost[i] = readIn();
	}

	if (n <= 20)
	{
		cheat1();
		return;
	}
	else if (m <= 1000)
	{
		cheat2();
		return;
	}

	INT mid = n >> 1;
	len1 = mid;
	len2 = n - mid;
	for (int i = 0; i < len1; i++)
	{
		seq1[i] = cost[i + 1];
	}
	for (int i = 0; i < len2; i++)
	{
		seq2[i] = cost[mid + i + 1];
	}

	//	for(int i = 0; i < len1; i++)
	//	{
	//		cout << seq1[i] << " ";
	//	}
	//	cout << endl;
	//	for(int i = 0; i < len2; i++)
	//	{
	//		cout << seq2[i] << " ";
	//	}

	INT U1 = 1 << len1;
	INT U2 = 1 << len2;
	for (int S = 1; S < U1; S++)
	{
		INT pos = 0;
		while (!(S & (1 << pos))) pos++;
		costSum1[S] = costSum1[S ^ (1 << pos)] + seq1[pos];
	}
	for (int S = 1; S < U2; S++)
	{
		INT pos = 0;
		while (!(S & (1 << pos))) pos++;
		costSum2[S] = costSum2[S ^ (1 << pos)] + seq2[pos];
	}
	std::sort(costSum1, costSum1 + U1);
	std::sort(costSum2, costSum2 + U2);

	INT pos2 = U2 - 1;
	for (int i = 0; i < U1; i++)
	{
		while (pos2 >= 0 && costSum1[i] + costSum2[pos2] > m)
		{
			pos2--;
		}
		ans += pos2 + 1;
	}
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
};
