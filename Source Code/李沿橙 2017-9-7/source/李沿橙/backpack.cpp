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

const INT INF = ~(INT(1) << (sizeof(INT) * 8 - 1));
const INT maxn = 100005;
INT n;
long long m;
struct Object
{
	INT cost;
	INT value;
	INT enlarge;
} objects[maxn];

#define RunInstance(x) delete new x
struct work
{
	static bool comp1(const Object& a, const Object& b)
	{
		return a.enlarge < b.enlarge;
	}
	static bool comp2(const Object& a, const Object& b)
	{
		return a.value > b.value;
	}
	static bool comp3(const Object& a, const Object& b)
	{
		return a.cost < b.cost;
	}

	work()
	{
		std::sort(objects + 1, objects + 1 + n, comp1);
		INT nonNegative = n + 1;
		for(int i = 1; i <= n; i++)
		{
			if(objects[i].enlarge >= 0)
			{
				nonNegative = i;
				break;
			}
		}

		std::sort(objects + 1, objects + 1 + nonNegative - 1, comp2);
		std::sort(objects + nonNegative, objects + 1 + n, comp3);
		
		for(int i = nonNegative; i <= n; i++)
		{
			if(m < objects[i].cost)
			{
				cout << "No" << endl;
				return;
			}
			m += objects[i].enlarge;
		}
		for(int i = 1; i < nonNegative; i++)
		{
			if(m < objects[i].cost)
			{
				cout << "No" << endl;
				return;
			}
			m += objects[i].enlarge;
		}
		cout << "Yes" << endl;
	}
};

void run()
{
	INT T = readIn();
	while(T--)
	{
		n = readIn();
		m = readIn();
		for(int i = 1; i <= n; i++)
		{
			objects[i].cost = readIn();
			objects[i].value = readIn();
			objects[i].enlarge = objects[i].value - objects[i].cost;
		}
		RunInstance(work);
	}
}

int main()
{
#ifndef JUDGE
	freopen("backpack.in", "r", stdin);
	freopen("backpack.out", "w", stdout);
#endif
	run();
	return 0;
}
