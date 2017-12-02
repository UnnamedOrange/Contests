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
typedef int INT;
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

const INT maxn = 105;
INT n, k, x, y;

char A[maxn][205];
INT length[maxn];
INT f[15][25];

INT KMP(INT Index, char* s)
{
	INT ans = 0;
	INT l = strlen(s);
	INT matched = 0;
	for (int i = 0; i < l; i++)
	{
		while (matched && s[i] != A[Index][matched]) matched = f[Index][matched];
		if (s[i] == A[Index][matched]) matched++;
		if (matched == length[Index]) ans++;
	}
	return ans;
}
void initFalure(INT Index)
{
	f[Index][0] = f[Index][1] = 0;
	for (int i = 1; i < length[Index]; i++)
	{
		INT pre = f[Index][i];
		while (pre && A[Index][i] != A[Index][pre]) pre = f[Index][pre];
		f[Index][pre + 1] = A[Index][i] == A[Index][pre] ? pre + 1 : 0;
	}
}

void run()
{
	n = readIn();
	k = readIn();
	x = readIn();
	y = readIn();
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", A[i]);
		length[i] = strlen(A[i]);
		initFalure(i);
	}

	INT ans = 0;
	for (int i = x + 1; i <= y; i++)
	{
		INT times = 0;
		char buffer[10];
		sprintf(buffer, "%d", i);
		for (int j = 1; j <= n; j++)
		{
			times += KMP(j, buffer);
		}
		if (times >= k)
		{
			ans++;
		}
	}
	cout << ans << endl;
}

int main()
{
#ifndef JUDGE
	freopen("word.in", "r", stdin);
	freopen("word.out", "w", stdout);
#endif
	run();
	return 0;
}
