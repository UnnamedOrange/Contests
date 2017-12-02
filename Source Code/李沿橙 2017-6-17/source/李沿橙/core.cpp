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
	int a=0;
	scanf("%d",&a);
	return a;
}


const int maxn=305;
int n,m;
int rect[maxn][maxn];

void Floyd()
{
	for(int k=1; k<=n; k++)
	{
		for(int i=1; i<=n; i++)
		{
			for(int j=1; j<=n; j++)
			{
				if(i!=k && j!=k && i!=j)
					rect[i][j]=std::min(rect[i][j],rect[i][k]+rect[k][j]);
			}
		}
	}
}

int findD()
{
	int maxi=0;
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			if(rect[i][j]>maxi)
			{
				maxi=rect[i][j];
			}
		}
	}
	return maxi;
}

namespace Regular
{
	void run()
	{
		Floyd();
		int d=findD(); //寻找直径的长度
		std::set<int> EdgeNode; //寻找直径的端点
		for(int i=1; i<=n; i++)
		{
			for(int j=1; j<=n; j++)
			{

			}
		}
	}
	void input()
	{
		memset(rect,0x3f,sizeof(rect));
		n=readIn();
		m=readIn();
		for(int i=1; i<=n; i++) rect[i][i]=0;
		for(int i=1; i<=m; i++)
		{
			int from=readIn();
			int to=readIn();
			rect[from][to]=rect[to][from]=readIn();
		}
	}
}

int main()
{
#ifndef DEBUG
	freopen("core.in","r",stdin);
	freopen("core.out","w",stdout);
#endif
	Regular::input();
	Regular::run();
	return 0;
}
