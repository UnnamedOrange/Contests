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

static INT code(char ch)
{
	if(ch == '.') return 1;
	if(ch >= '0' && ch <= '9') return ch - '0';
	if(ch >= 'A' && ch <= 'E') return ch - 'A' + 1;
	return -1;
}
INT readStr()
{
	INT val = 0;
	char ch = getchar();
	while(code(ch) == -1) ch = getchar();
	while(code(ch) != -1)
	{
		val *= 10;
		val += code(ch);
		ch = getchar();
	}
	//cout << val << endl;
	return val;
}

const INT maxn = 100005;
INT n, m;
struct binary
{
	INT num;
	INT index;
	bool operator< (const binary& b) const
	{
		return num < b.num;
	}
} input[maxn];
INT origin[maxn];

INT lower_bound(INT x)
{
	INT left = 1;
	INT right = n;
	while(right - left > 1)
	{
		INT mid = (left + right) >> 1;
		if(origin[mid] < x)
		{
			left = mid;
		}
		else
		{
			right = mid;
		}
	}
	if(origin[left] == x) return left;
	else if(origin[right] == x) return right;
	return 0;
}

void run()
{
	n = readIn();
	INT a = readIn();
	for(int i = 1; i <= n; i++)
	{
		input[i].num = readStr();
		input[i].index = i;
	}
	std::sort(input + 1, input + 1 + n);
	for(int i = 1; i <= n; i++)
	{
		origin[i] = input[i].num;
	}
	while(a--)
	{
		m = readIn();
		std::vector<INT> LIS;
		for(int i = 1; i <= m; i++)
		{
			INT temp = readStr();
			INT pos = lower_bound(temp);
			if(pos)
			{
				if(LIS.empty() || LIS.back() < input[pos].index)
				{
					LIS.push_back(input[pos].index);
				}
				else
				{
					*std::lower_bound(LIS.begin(), LIS.end(), input[pos].index) = input[pos].index;
				}
			}
		}
		printf("%.6f\n", double(LIS.size()) / m);
	}
}

int main()
{
	run();
	return 0;
}
