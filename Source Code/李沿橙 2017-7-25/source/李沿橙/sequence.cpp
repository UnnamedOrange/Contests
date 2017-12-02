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

INT n, k;
INT ansOr;
INT ansAnd;
INT bit[32];
std::deque<INT> dq;

void run()
{
	n = readIn();
	k = readIn();
	for(int i = 1; i <= n; i++)
	{
		INT num = readIn();
		ansOr |= num; //或贪心：尽量多

		dq.push_back(num);
		for(int i = 0; i < 31; i++)
		{
			bit[i] += bool(num & (1 << i));
		}

		if(dq.size() == k) //与贪心：尽量少
		{
			INT temp = 0;
			for(int i = 0; i < 31; i++)
			{
				if(bit[i] == k)
				{
					temp |= 1 << i;
				}
			}
			ansAnd = std::max(ansAnd, temp);

			INT popVal = dq.front();
			dq.pop_front();
			for(int i = 0; i < 31; i++)
			{
				bit[i] -= bool(popVal & (1 << i));
			}
		}
	}
	cout << ansOr << " " << ansAnd << endl;
}

int main()
{
#ifndef DEBUG
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif
	run();
	return 0;
}
