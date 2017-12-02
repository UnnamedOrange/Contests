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

const INT mod = 1e9 + 7;
const INT maxn = 2e5 + 5;
INT n, k, x;
bool sign;
std::priority_queue<INT, std::vector<INT>, std::greater<INT> > pq;

void run()
{
	n = readIn();
	k = readIn();
	x = readIn();
	for (int i = 1; i <= n; i++)
	{
		INT input = readIn();
		if (input < 0) sign = !sign; //regard 0 as a positive
		pq.push(std::abs(input));
	}

	for (int i = 1; i <= k; i++)
	{
		INT handle = pq.top();
		pq.pop();
		if (sign) //negative
		{
			handle += x;
		}
		else //positive
		{
			if (handle < x)
			{
				sign = !sign;
				handle = x - handle;
			}
			else
			{
				handle -= x;
			}
		}
		pq.push(handle);
	}

	INT mul = 1;
	for (int i = 1; i <= n; i++)
	{
		mul = mul * (pq.top() % mod) % mod;
		pq.pop();
	}
	if (sign) mul = mod - mul;
	cout << mul << endl;
}

int main()
{
	run();
	return 0;
}
