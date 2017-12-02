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
using std::cin;
using std::cout;
using std::endl;

const int maxn=105;
int n,d;
int rect[maxn][maxn];
enum
{
    EMPTY,
    HEALTHY,
    FLU
};

int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			char ch;
			cin>>ch;
			if(ch=='#')
			{
				rect[i][j]=EMPTY;
			}
			else if(ch=='.')
			{
				rect[i][j]=HEALTHY;
			}
			else if(ch=='@')
			{
				rect[i][j]=FLU;
			}
		}
	}
	scanf("%d",&d);
	d--;
	while(d--)
	{
		int temp[maxn][maxn]= {0};
		memcpy(temp,rect,sizeof(temp));
		for(int i=1; i<=n; i++)
		{
			for(int j=1; j<=n; j++)
			{
				if(rect[i][j]==FLU)
				{
					if(temp[i-1][j]!=EMPTY)
						temp[i-1][j]=FLU;
					if(temp[i+1][j]!=EMPTY)
						temp[i+1][j]=FLU;
					if(temp[i][j-1]!=EMPTY)
						temp[i][j-1]=FLU;
					if(temp[i][j+1]!=EMPTY)
						temp[i][j+1]=FLU;
				}
			}
		}
		memcpy(rect,temp,sizeof(rect));
	}
	int ans=0;
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			if(rect[i][j]==FLU) ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
