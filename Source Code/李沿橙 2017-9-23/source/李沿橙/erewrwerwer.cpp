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

const INT maxn = 100005;
const INT maxm = 13;
const char szToMatch[] = "erewrwerwer";
INT n, m;
INT s[maxn];
INT t[maxm];

inline INT toCode(char ch)
{
	if(ch == 'e') return 1;
	else if(ch == 'w') return 2;
	else if(ch == 'r') return 3;
	else if(ch == '?') return 4; //data bug 
	return 0;
}
void read()
{
	char ch = getchar();
	while(!toCode(ch)) ch = getchar();
	INT code;
	while(code = toCode(ch))
	{
		s[++n] = code;
		ch = getchar();
	}
}
void switchMatch()
{
	m = strlen(szToMatch);
	for(int i = 0; i < m; i++)
	{
		t[i + 1] = toCode(szToMatch[i]);
	}
}

const INT mod = INT(1e9) + 7;
#define RunInstance(x) delete new x
struct work
{
	INT f[maxn][maxm];
	INT sum[maxn][maxm];
	work() : f(), sum()
	{
		sum[0][0] = f[0][0] = 1;
		for(int i = 1; i <= n; i++)
		{
			sum[i][0] = f[i][0] = 1;

			INT to = std::min(INT(i), INT(m));
			for(int j = 1; j <= to; j++)
			{
				if(s[i] == t[j])
				{
					f[i][j] = sum[i - 1][j - 1];
				}
				else
				{
					f[i][j] = 0;
				}
				sum[i][j] = (sum[i - 1][j] + f[i][j]) % mod;
			}
		}
		cout << sum[n][m] << endl;
	}
};

void run()
{
	switchMatch();
	read();

	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("erewrwerwer.in", "r", stdin);
	freopen("erewrwerwer.out", "w", stdout);
#endif
	run();
	return 0;
}
