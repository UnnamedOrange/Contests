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

const INT mod = 998244353;
const INT maxn = 55;
const INT maxm = 25;
INT n;
char str[maxn][maxm];
INT length[maxn];

INT f[maxn][maxm][27][2];

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", str[i] + 1);
		length[i] = strlen(str[i] + 1);
		for(int j = 1; j <= length[i]; j++)
		{
			if(str[i][j] == '?') str[i][j] = 0;
			else str[i][j] = str[i][j] + 1 - 'a';
		}
	}

	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= length[i]; j++)
		{
			
		}
	}
}

int main()
{
#ifndef JUDGE
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
#endif
	run();
	return 0;
}
