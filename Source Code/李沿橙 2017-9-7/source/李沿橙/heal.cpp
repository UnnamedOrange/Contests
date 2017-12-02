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

const INT mod = 1000000007;
INT n, m;

void run()
{
	n = readIn();
	m = readIn();

	if(!n)
	{
		if(m == 1) cout << 1 << endl;
		else cout << 0 << endl;
	}
	else if(n == 1)
	{
		INT ans = m;
		INT to = sqrt(m);
		for(int i = 2; i <= to; i++)
		{
			if(m % i) continue;
			ans /= i;
			ans *= i - 1;
			while(!(m % i)) m /= i;
		}
		if(m > 1)
		{
			ans /= m;
			ans *= m - 1;
		}
		cout << ans << endl;
	}
}

int main()
{
#ifndef JUDGE
	freopen("heal.in", "r", stdin);
	freopen("heal.out", "w", stdout);
#endif
	run();
	return 0;
}
