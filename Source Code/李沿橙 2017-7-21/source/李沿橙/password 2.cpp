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

const INT maxn = 10005;
INT n;
INT sum1[maxn];
std::vector<INT> ans;
INT count_;
bool bOk;

void search(INT l = 1, INT r = n)
{
	INT count1 = sum1[r] - sum1[l - 1];
	if(count1 == r - l + 1 || count1 == 0)
	{
		if(count1 + count_ == sum1[n]) //剩下确定全部填0
		{
			while(ans.size() < n - 1)
			{
				ans.push_back(0);
			}
			ans.push_back(bool(count1));
			bOk = true;
		}
		else if(sum1[n] - count1 - count_ == n - ans.size() - 1) //剩下确定全部填1
		{
			while(ans.size() < n - 1)
			{
				ans.push_back(1);
			}
			ans.push_back(bool(count1));
			bOk = true;
		}
		return;
	}

	ans.push_back(0);
	search(l, r - count1);
	if(bOk) return;
	ans.pop_back();

	ans.push_back(1);
	count_++;
	search(r - count1 + 1, r);
	if(bOk) return;
	count_--;
	ans.pop_back();
}

bool comp(INT a, INT b)
{
	for(int i = 0; i < n; i++)
	{
		if(ans[a] < ans[b]) return true;
		else if(ans[a] > ans[b]) return false;
		a = (a + 1) % n;
		b = (b + 1) % n;
	}
	return false;
}

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		sum1[i] = sum1[i - 1] + readIn();
	}
	search();

	INT place = 0;
	for(int i = 1; i < n; i++)
	{
		if(comp(i, place))
		{
			place = i;
		}
	}
	for(int i = 0; i < n; i++, place = (place + 1) % n)
	{
		printf("%d ", ans[place]);
	}
}

int main()
{
#ifndef DEBUG
	freopen("password.in", "r", stdin);
	freopen("password.out", "w", stdout);
#endif
	run();
	return 0;
}
