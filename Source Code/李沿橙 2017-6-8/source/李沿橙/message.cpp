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
inline int readIn(int a = 0)
{
	scanf("%d",&a);
	return a;
}

const int maxn=55;
int r,c;
int rect[maxn][maxn];
int f[2*maxn][maxn][maxn];
int DP()
{
	int steps=r+c;
	for(int i=3; i<=steps; i++)
	{
		for(int x1=1; x1<=std::min(r,i-1); x1++)
		{
			for(int x2=1; x2<=std::min(r,i-1); x2++)
			{
				if(x1==x2 && i!=steps) continue;
				int temp=0;
				temp=std::max(temp, f[i-1][x1][x2]);
				if(x1-1!=x2)
					temp=std::max(temp, f[i-1][x1-1][x2]);
				if(x1!=x2-1)
					temp=std::max(temp, f[i-1][x1][x2-1]);
				temp=std::max(temp, f[i-1][x1-1][x2-1]);

				f[i][x1][x2]=temp+rect[x1][i-x1]+rect[x2][i-x2];
			}
		}
	}
	return f[steps][r][r];
}

int main()
{
	r=readIn();
	c=readIn();
	for(int i = 1; i <= r; i++)
		for(int j = 1; j <= c; j++)
		{
			rect[i][j]=readIn();
		}
	printf("%d\n",DP());
}
