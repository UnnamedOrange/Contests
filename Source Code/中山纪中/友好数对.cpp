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
INT n, m;
INT seq[2][maxn];
long long ans;
#define lowbit(x) ((x) & -(x))

void cheat()
{
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			INT Xor = seq[0][i] ^ seq[1][j];
			INT del1 = Xor ^ lowbit(Xor);
			if(del1 && lowbit(del1) == del1)
			{
				ans++;
			}
		}
	}
	cout << ans << endl;
}

void hashWay()
{
	for(int i = 0; i < 30; i++)
	{
		for(int j = i + 1; j < 30; j++)
		{
			INT toXor = (1 << i) ^ (1 << j);
		}
	}
}

void run()
{
	n = readIn();
	m = readIn();
	for(int i = 1; i <= n; i++)
	{
		seq[0][i] = readIn();
	}
	for(int i = 1; i <= m; i++)
	{
		seq[1][i] = readIn();
	}
	
	if(n <= 2000 && m <= 2000)
	{
		cheat();
		return;
	}
	
	hashWay();
}

int main()
{
	run();
	return 0;
}
