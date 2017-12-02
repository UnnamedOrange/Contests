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
#define FOR(x, f, t) for(int x = (f); x <= (t); x++)
inline int readIn()
{
	int a;
	scanf("%d",&a);
	return a;
}

const int maxn = 100005;
const int maxm = 100005;
int n,m;
struct CITY
{
	int index;
	int height;

	CITY(int index = 0, int height = 0):index(index), height(height)
	{

	}
	bool operator< (const CITY& b) const
	{
		return height < b.height;
	}
} cities[maxn];
int start[maxm];
int x[maxm];

int height;
struct sub   //用于初始化
{
	CITY destination;
	void operator=(const CITY& b)
	{
		destination = b;
	}
	bool operator<(const sub& b) const
	{
		int s1 = std::abs(height - destination.height);
		int s2 = std::abs(height - b.destination.height);
		if(s1==s2) return destination.height < b.destination.height;
		return s1<s2;
	}
} subs[4];
int nextA[maxn];
int nextB[maxn];
const int maxIndex = 17;
int next[maxIndex][maxn]; //从i开2^k轮后到的位置
long long disA[maxIndex][maxn]; //从i开2^k轮A的路程
long long disB[maxIndex][maxn]; //从i开2^k轮B的路程

void input()
{
	n=readIn();
	FOR(i, 1, n)
	{
		cities[i].height=readIn();
		cities[i].index = i;
	}
	x[0]=readIn();
	m=readIn();
	FOR(i, 1, m)
	{
		start[i]=readIn();
		x[i]=readIn();
	}
}
void init()
{
	std::set<CITY> des;
	des.insert(cities[n]);

	for(int i = n-1; i >= 1; i--)   //要从右往左更新，因为只能从左往右走
	{
		des.insert(cities[i]); //先插入：我们要知道要更新的城市的位置
		std::set<CITY>::iterator it = des.find(cities[i]); //要更新的城市的位置

		int nCmp = 0;
		if(it!=des.begin())
		{
			it--;
			subs[nCmp++] = *it;
			if(it!=des.begin())
			{
				it--;
				subs[nCmp++] = *it;
				it++;
			}
			it++;
		}
		if(it!=des.end())
		{
			it++; //不用复原了
			subs[nCmp++] = *it;
			if(it!=des.end())
			{
				it++;
				subs[nCmp++] = *it;
			}
		}

		height = cities[i].height;
		std::sort(subs, subs+nCmp);
		nextB[i] = subs[0].destination.index;
		if(i<=n-2) nextA[i] = subs[1].destination.index;
	}
}

void go(int from, int X, long long& lengthA, long long& lengthB)
{
	for(int i = maxIndex - 1; ~i; i--) //相当于二进制
	{
		if(next[i][from] && disA[i][from] + disB[i][from] <= X)
		{
			lengthA += disA[i][from];
			lengthB += disB[i][from];
			X -= disA[i][from] + disB[i][from];
			from = next[i][from];
		}
	}
	int last = nextA[from]; //看看A还能不能走
	if(!last) return;
	int lastDis = std::abs(cities[last].height - cities[from].height);
	if(lastDis <= X) lengthA+=lastDis;
}

void run()
{
	input();
	init(); //初始化A,B开一次开到哪里去了

	for(int i = 1; i <= n; i++) //初始化开1轮的情况
	{
		int pos1 = nextA[i];
		int pos2 = nextB[pos1];
		if(pos1) disA[0][i] = std::abs(cities[pos1].height - cities[i].height);
		if(pos2) disB[0][i] = std::abs(cities[pos2].height - cities[pos1].height);
		next[0][i] = pos2;
	}
	for(int i = 1; i <= maxIndex - 1; i++) //初始化开2^k轮的情况
	{
		for(int j = 1; j <= n; j++)
		{
			next[i][j] = next[i - 1][next[i - 1][j]];
			disA[i][j] = disA[i - 1][j] + disA[i - 1][next[i - 1][j]];
			disB[i][j] = disB[i - 1][j] + disB[i - 1][next[i - 1][j]];
		}
	}

	//solve1
	long long ansA=1e15;
	long long ansB=0;
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		long long lengthA=0, lengthB=0;
		go(i, x[0], lengthA, lengthB);
		if(lengthB && (!ans || ansA * lengthB > ansB * lengthA))
		{
			ans = i;
			ansA = lengthA;
			ansB = lengthB;
		}
	}
	printf("%d\n",ans);

	//solve2
	for(int i = 1; i <= m; i++)
	{
		long long lengthA=0, lengthB=0;
		go(start[i], x[i], lengthA, lengthB);
		printf("%lld %lld\n",lengthA, lengthB);
	}
}

int main()
{
	run();
	return 0;
}
