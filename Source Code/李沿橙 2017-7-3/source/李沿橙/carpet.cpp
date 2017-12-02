#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;
inline int readIn()
{
	int a;
	scanf("%d",&a);
	return a;
}

const int maxn=10005;
int n;
struct CARPET
{
	int lx;
	int ly;
	int rx;
	int ry;

	CARPET():lx(0),ly(0),rx(0),ry(0)
	{

	}
	void input()
	{
		lx=readIn();
		ly=readIn();
		rx=readIn()+lx;
		ry=readIn()+ly;
	}

	bool isInRect(int x, int y)
	{
		return lx <= x && x <= rx && ly <= y && y <= ry;
	}
} carpets[maxn];

void run()
{
	n=readIn();
	for(int i=1; i<=n; i++) carpets[i].input();
	int ans=-1;
	int x=readIn();
	int y=readIn();
	for(int i=1; i<=n; i++)
	{
		if(carpets[i].isInRect(x,y))
		{
			ans=i;
		}
	}
	printf("%d\n",ans);
}

int main()
{
	run();
	return 0;
}
