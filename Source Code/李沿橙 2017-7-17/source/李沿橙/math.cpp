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
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline int readIn()
{
	bool minus = false;
	int a = 0;
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
	if(minus) a = -a;
	return a;
}

INT k, p;
INT mod;

INT power(INT x, INT index)
{
	if(!index) return 1;
	INT temp = power(x, index >> 1);
	temp *= temp;
	temp %= mod;
	if(index & 1)
	{
		temp *= x;
		temp %= mod;
	}
	return temp;
}

void run()
{
	k = readIn();
	p = readIn();
	mod = p * p;
	INT kp = k * p;
	INT index_ = 2 * p - 1;
	INT ans = 0;
	for(INT i = 1; i <= kp; i++)
	{
		ans += power(i, index_);
		ans %= mod;
	}
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
