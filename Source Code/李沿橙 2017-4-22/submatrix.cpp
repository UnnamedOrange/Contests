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

int N,M,R,C;
int rect[20][20];
std::vector<std::vector<int> > rPosibleSet;
std::vector<std::vector<int> > cPosibleSet;
std::vector<int> tempQueue;
int ans=0x3fffffff;

void input()
{
	scanf("%d%d%d%d",&N,&M,&R,&C);
	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=M; j++)
		{
			scanf("%d",&rect[i][j]);
		}
	}
}

void deal(std::vector<int> &rSet,std::vector<int> &cSet)
{
	int temp=0;
	for(int i=0; i<rSet.size(); i++)
	{
		for(int j=1; j<cSet.size(); j++)
		{
			temp+=abs(rect[rSet[i]][cSet[j]]-rect[rSet[i]][cSet[j-1]]);
		}
	}

	for(int i=0; i<cSet.size(); i++)
	{
		for(int j=1; j<rSet.size(); j++)
		{
			temp+=abs(rect[rSet[j]][cSet[i]]-rect[rSet[j-1]][cSet[i]]);
		}
	}
	ans=std::min(ans,temp);
}

void search(int depth,int startNum,int endNum,std::vector<std::vector<int> > &Set)
{
	if(depth==0)
	{
		Set.push_back(tempQueue);
		return;
	}
	for(int i=startNum; i<=endNum-depth+1; i++)
	{
		tempQueue.push_back(i);
		search(depth-1,i+1,endNum,Set);
		tempQueue.pop_back();
	}
}

void run()
{
	search(R,1,N,rPosibleSet);
	search(C,1,M,cPosibleSet);
	for(int i=0; i<rPosibleSet.size(); i++)
	{
		for(int j=0; j<cPosibleSet.size(); j++)
		{
			deal(rPosibleSet[i],cPosibleSet[j]);
		}
	}
	printf("%d",ans);
}

int main()
{
#ifndef DEBUG
	freopen("submatrix.in","r",stdin);
	freopen("submatrix.out","w",stdout);
#endif
	input();
	run();
	return 0;
}
