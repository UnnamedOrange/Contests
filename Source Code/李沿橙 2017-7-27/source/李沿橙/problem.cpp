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
typedef unsigned long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while(!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if(ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if(minus) a = -a;
	return a;
}

const INT maxn = 2005;
INT mod;
INT n, m;
INT C[maxn + 5][maxn + 5];
INT f[maxn + 5][maxn + 5];

void run()
{
	INT a = readIn();
	mod = readIn();
	for(int i = 1; i <= maxn; i++)
	{
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; j++)
		{
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}
	}
	for(int i = 1; i <= maxn; i++)
	{
		for(int j = 0; j <= maxn; j++)
		{
			if(j)
			{
				f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + (j <= i && !C[i][j]);
			}
			else
			{
				f[i][j] = f[i - 1][j] + (j <= i && !C[i][j]);
			}
		}
	}

	while(a--)
	{
		INT ans = 0;
		n = readIn();
		m = readIn();
		cout << f[n][m] << endl;
	}
}

int main()
{
	run();
	return 0;
}
