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
#define FOR(i, f, t) for(int i = (f); i <= (t); i++)
inline int readIn()
{
	int a;
	scanf("%d", &a);
	return a;
}

const int maxn = 100005;
int n,s,t;
struct jury
{
	int x;
	int y;
	bool cannot; //t
	bool chosen; //s

	void input()
	{
		x = readIn();
		y = readIn();
	}
} people[maxn];

bool comp1(const jury& a, const jury& b)
{
	return a.y > b.y;
}

bool comp2(const jury& a, const jury& b)
{
	if(a.cannot != b.cannot) return a.cannot < b.cannot;
	if(a.x != b.x) return a.x > b.x;
	return a.y > b.y;
}

bool comp3(const jury& a, const jury& b)
{
	if(a.cannot != b.cannot) return a.cannot > b.cannot;
	if(a.y != b.y) return a.y > b.y;
	return a.x > b.x;
}

void run()
{
	n = readIn();
	s = readIn();
	t = readIn();
	FOR(i, 1, n) people[i].input();
	std::sort(people + 1, people + 1 + n, comp1);
	for(int i = n, j = 1; j <= (s - t); j++, i--)
		people[i].cannot = true;
	std::sort(people + 1, people + 1 + n, comp2);
	for(int i = 1; i <= t; i++)
		people[i].chosen = true;
	std::sort(people + 1, people + 1 + n, comp1);
	int maxIndex = 0;
	for(int i = n; i >= 1; i--)
	{
		if(people[i].chosen)
		{
			maxIndex = i;
			break;
		}
	}
	for(int i = maxIndex + 1; i <= n; i++)
	{
		people[i].cannot = true;
	}
	std::sort(people + 1, people + 1 + n, comp3);
	for(int i = 1; i <= (s - t); i++)
	{
		people[i].chosen = true;
	}

	long long ansX = 0;
	long long ansY = 0;
	for(int i = 1; i <= n; i++)
	{
		if(people[i].chosen)
		{
			ansX += people[i].x;
			ansY += people[i].y;
		}
	}
	cout<<ansX<<" "<<ansY<<endl;
}

int main()
{
	run();
	return 0;
}
