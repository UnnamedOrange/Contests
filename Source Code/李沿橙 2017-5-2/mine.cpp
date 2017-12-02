#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;

const int maxn=105;
int n,m;
int mine[maxn][maxn];

void input()
{
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			char ch;
			cin>>ch;
			if(ch=='?')
			{

			}
			else if(ch=='*')
			{
				mine[i][j]=-1;
			}
		}
	}
}

void output()
{
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			if(mine[i][j]==-1)
			{
				printf("*");
			}
			else
			{
				printf("%d",mine[i][j]);
			}
		}
		puts("");
	}
}

void run()
{
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			if(mine[i][j]==-1) continue;
			if(mine[i+1][j]==-1) mine[i][j]++;
			if(mine[i-1][j]==-1) mine[i][j]++;
			if(mine[i][j+1]==-1) mine[i][j]++;
			if(mine[i][j-1]==-1) mine[i][j]++;
			if(mine[i+1][j+1]==-1) mine[i][j]++;
			if(mine[i+1][j-1]==-1) mine[i][j]++;
			if(mine[i-1][j+1]==-1) mine[i][j]++;
			if(mine[i-1][j-1]==-1) mine[i][j]++;
		}
	}
	output();
}

int main()
{
#ifndef DEBUG
	freopen("mine.in","r",stdin);
	freopen("mine.out","w",stdout);
#endif
	input();
	run();
	return 0;
}
