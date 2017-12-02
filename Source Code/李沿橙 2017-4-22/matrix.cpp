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

int N,I,J;

void input()
{
	scanf("%d%d%d",&N,&I,&J);
}

void run()
{
	int level=0;
	{
		std::vector<int> temp(N+1);
		double mid=(double)(N+1)/2;
		int times=mid-abs(mid-I);
		for(int i=1; i<=times; i++)
		{
			temp[i]=i;
		}
		for(int i=1,j=N; i<=times; i++,j--)
		{
			temp[j]=i;
		}
		for(int i=times+1; i<=N; i++)
		{
			if(temp[i])
				break;
			temp[i]=times;
		}
		level=temp[J];
	}

	int score=N*N-(N-2*level+2)*(N-2*level+2);
	int x=level,y=level-1;
	for(int i=1; i<=N-level*2+2; i++)
	{
		y++;
		score++;
		if(x==I && y==J)
		{
			printf("%d",score);
			return;
		}
	}
	for(int i=2; i<=N-level*2+2; i++)
	{
		x++;
		score++;
		if(x==I && y==J)
		{
			printf("%d",score);
			return;
		}
	}
	for(int i=2; i<=N-level*2+2; i++)
	{
		y--;
		score++;
		if(x==I && y==J)
		{
			printf("%d",score);
			return ;
		}
	}
	for(int i=2; i<=N-level*2+2; i++)
	{
		x--;
		score++;
		if(x==I && y==J)
		{
			printf("%d",score);
			return ;
		}
	}
}

int main()
{
#ifndef DEBUG
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
#endif
	input();
	run();
	return 0;
}
