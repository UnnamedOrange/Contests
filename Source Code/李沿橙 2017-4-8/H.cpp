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

char buffer1[25];
char buffer2[25];
int length1;
int length2;

bool dfs(int x,int y)
{
	if(x>=length1 && y>=length2)
	{
		return true;
	}
	else if(x>=length1 || y>=length2)
	{
		return false;
	}

	if(buffer1[x]!='*' && buffer1[x]!='?')
	{
		if(buffer1[x]!=buffer2[y])
		{
			return false;
		}
		else
		{
			return dfs(x+1,y+1);
		}
	}
	else if(buffer1[x]=='?')
	{
		return dfs(x+1,y+1);
	}
	else
	{
		bool ans=false;
		for(int i=y; i<=length2; i++)
		{
			ans=ans || dfs(x+1,i);
		}
		return ans;
	}
}

int main()
{
	std::cin.getline(buffer1,25);
	std::cin.getline(buffer2,25);
	length1=strlen(buffer1);
	length2=strlen(buffer2);
	bool ans=dfs(0,0);
	if(ans)
	{
		printf("matched");
	}
	else
	{
		printf("not matched");
	}
	return 0;
}
