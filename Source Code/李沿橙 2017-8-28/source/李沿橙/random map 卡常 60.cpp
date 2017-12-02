#pragma GCC optimize("O2")
#pragma G++ optimize("O2")
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

const INT maxn = INT(1e6) + 5;
INT n;
INT A[maxn];

typedef std::map<INT, INT>::iterator Iterator;
std::map<INT, INT> num, sub;

INT ans = ~(1ll << (sizeof(INT) * 8 - 1));

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		A[i] = readIn();
	}

	INT l = 1;
	INT repeat = 0;
	num[A[1]]++;
	for(int i = 2; i <= n; i++)
	{
		num[A[i]]++;

		Iterator it, pre, next, end;
		pre = next = it = num.find(A[i]);
		if(pre != num.begin())
			pre--;
		next++;
		end = num.end();

		INT oldSub;
		INT newSub;
		INT cntSub;
		if(it->second == 1)
		{
			if(pre != it && next != end)
			{
				oldSub = next->first - pre->first;
				sub[oldSub]--;
				if(!sub[oldSub]) sub.erase(oldSub);
			}

			if(pre != it)
			{
				newSub = it->first - pre->first;
				sub[newSub]++;
			}
			if(next != end)
			{
				newSub = next->first - it->first;
				sub[newSub]++;
			}
		}
		else if(it->second == 2) repeat++;


		if(repeat) cntSub = 0;
		else cntSub = sub.begin()->first;
		ans = std::min(ans, std::max(cntSub, i - l + 1));
		while(i - l > 1 && cntSub < i - l + 1)
		{
			pre = next = it = num.find(A[l]);
			if(pre != num.begin())
				pre--;
			next++;
			end = num.end();
			l++;

			if(it->second > 2) it->second--;
			else if(it->second == 2)
			{
				repeat--;
				it->second--;

				if(!repeat)
				{
					cntSub = sub.begin()->first;
				}
			}
			else
			{
				if(pre != it && next != end)
				{
					newSub = next->first - pre->first;
					sub[newSub]++;
				}

				if(pre != it)
				{
					oldSub = it->first - pre->first;
					sub[oldSub]--;
					if(!sub[oldSub]) sub.erase(oldSub);
				}
				if(next != end)
				{
					oldSub = next->first - it->first;
					sub[oldSub]--;
					if(!sub[oldSub]) sub.erase(oldSub);
				}
				num.erase(it);
			}

			if(repeat) cntSub = 0;
			else cntSub = sub.begin()->first;
			ans = std::min(ans, std::max(cntSub, i - l + 1));
		}
	}
	cout << ans << endl;
}

int main()
{
#ifndef JUDGE
	freopen("random.in", "r", stdin);
	freopen("random.out", "w", stdout);
#endif
	run();
	return 0;
}
