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

int n;
int rect[15][15];

int main()
{
	scanf("%d",&n);
	int times=n*n;
	int i=0;
	int x=1,y=-1;
	while(i<=times)
	{
		while(i<=times && x-1>=0 && y+1<n)
		{
			x--;
			y++;
			i++;
			rect[x][y]=i;
		}
		if(y+1<n) y++;
		else x++;
		rect[x][y]=++i;
		while(i<=times && x+1<n && y-1>=0)
		{
			x++;
			y--;
			i++;
			rect[x][y]=i;
		}
		if(x+1<n) x++;
		else y++;
		rect[x][y]=++i;
	}

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			printf("%d ",rect[i][j]);
		}
		puts("");
	}
	return 0;
}
