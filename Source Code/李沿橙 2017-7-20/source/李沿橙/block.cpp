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
	bool minus = false;
	INT a = 0;
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

const INT maxn = 100005;
INT n;

void run()
{
	n = readIn();
	INT ans = 0;
	INT pre = 0;
	for(int i = 1; i <= n; i++)
	{
		INT cnt = readIn();
		if(cnt > pre)
		{
			ans += cnt - pre;
		}
		pre = cnt;
	}
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
