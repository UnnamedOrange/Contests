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

const int X=5;
const int Y=7;
int n;
bool isAns;
int rect[7][X][Y];
int ins[7][3];
int count_[7][15];

bool empty(int index)
{
	for(int i=1; i<=10; i++)
	{
		if(count_[index][i]) return false;
	}
	return true;
}
void fall(int r[X][Y])
{
	int temp[X][Y] = {0};
	for(int x=0; x<X; x++)
	{
		int cy = 0;
		for(int y=0; y<Y; y++)
		{
			if(r[x][y])
			{
				temp[x][cy++] = r[x][y];
			}
		}
	}
	memcpy(r,temp, sizeof(temp));
}
bool destruct(int index, int r[X][Y])
{
	bool sign[X][Y]= {false};
	bool bRet = false;
	for(int x=0; x<X; x++)
	{
		int count_ = 1;
		int color=r[x][0];
		for(int y=1; y<Y; y++)
		{
			if(r[x][y] != color)
			{
				if(color && count_ >= 3)
				{
					for(int i = y-count_; i<y; i++) sign[x][i]=true;
				}
				color=r[x][y];
				count_ = 1;
			}
			else if(!r[x][y])
			{
				count_=0;
				color=0;
			}
			else
			{
				count_++;
			}
		}
		if(color && count_ >= 3)
		{
			for(int i = Y-count_; i<Y; i++) sign[x][i]=true;
		}
	}
	for(int y=0; y<Y; y++)
	{
		int count_ = 1;
		int color=r[0][y];
		for(int x=1; x<X; x++)
		{
			if(r[x][y] != color)
			{
				if(color && count_ >= 3)
				{
					for(int i = x-count_; i<x; i++) sign[i][y]=true;
				}
				color=r[x][y];
				count_ = 1;
			}
			else if(!r[x][y])
			{
				count_=0;
				color=0;
			}
			else
			{
				count_++;
			}
		}
		if(color && count_ >= 3)
		{
			for(int i = X-count_; i<X; i++) sign[i][y]=true;
		}
	}
	for(int x=0; x<X; x++)
	{
		for(int y=0; y<Y; y++)
		{
			if(sign[x][y])
			{
				bRet = true;
				count_[index][r[x][y]]--;
				r[x][y] = 0;
			}
		}
	}
	return bRet;
}
void operate(int index, int x, int y, int g)
{
	memcpy(rect[index+1],rect[index],sizeof(rect[index+1]));
	memcpy(count_[index+1],count_[index],sizeof(count_[index]));
	index++;

#define r rect[index]
	std::swap(r[x][y], r[x+g][y]);
	fall(r);
	bool bOk = true;
	while(bOk)
	{
		bOk = false;
		bOk |= destruct(index, r);
		if(bOk) fall(r);
	}
#undef r
}
void dfs(int index = 0)
{
	if(index>n) return;
	if(empty(index))
	{
		isAns = true;
		for(int i=0; i<index; i++)
		{
			printf("%d %d %d\n",ins[i][0],ins[i][1],ins[i][2]);
		}
		return;
	}
	else if(index==n) return;

	for(int x = 0; x<X; x++)
	{
		for(int y = 0; y<Y && rect[index][x][y]; y++)
		{
			for(int g=1; g>=-1; g-=2)
			{
				if(x+g<0 || x+g>=X) continue;
				if(g==-1 && rect[index][x+g][y]) continue;
				if(rect[index][x+g][y] == rect[index][x][y]) continue;

				ins[index][0]=x;
				ins[index][1]=y;
				ins[index][2]=g;
				operate(index,x,y,g);
				for(int i=1; i<=10; i++)
				{
					if(count_[index][i] && count_[index][i]<3) return;
				}
				dfs(index+1);
				if(isAns) return;
			}
		}
	}
}

void run()
{
	n=readIn();
	for(int x=0; x<X; x++)
	{
		int y = 0;
		while(rect[0][x][y] = readIn())
		{
			count_[0][rect[0][x][y]]++;
			y++;
		}
	}
	dfs();
	if(!isAns)
		printf("-1\n");
}

int main()
{
	run();
	return 0;
}
