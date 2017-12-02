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

const int maxn=10;
int n;
int score[maxn];
int ans;

inline int readIn()
{
	int a;
	scanf("%d",&a);
	return a;
}

long long hash(std::vector<int> &vec) //算出数组对应的hash值
{
	long long temp=0;
	for(int i=0; i<vec.size(); i++)
	{
		temp=temp*29+vec[i];
	}
	return temp;
}

int searchGuest(int host, int guest, int scoreOfHost);
std::map<long long, int> hashMap[maxn];
int searchHost(int host = 1) //搜索主场
{
	if(host == n) //已经搜索完毕
	{
		return !score[host]; //如果分已经匹配完，说明有了一种方案
	}
	std::vector<int> hashOrigin;
	for(int i=host; i<=n; i++)
	{
		hashOrigin.push_back(score[i]);
	}
	std::sort(hashOrigin.begin(),hashOrigin.end());
	long long hashVal=hash(hashOrigin);
	if(hashMap[host].count(hashVal)) return hashMap[host][hashVal];
	else return hashMap[host][hashVal]=searchGuest(host, host+1, score[host]);
}

int searchGuest(int host, int guest, int scoreOfHost)
{
	if(guest>n)
	{
		if(scoreOfHost) return 0;
		else return searchHost(host+1);
	}
	if(scoreOfHost > (n-guest+1)*3) return 0;

	int ans=0;
	if(score[guest]>=3)
	{
		score[guest]-=3;
		ans+=searchGuest(host, guest+1, scoreOfHost);
		score[guest]+=3;
	}
	if(score[guest] && scoreOfHost)
	{
		score[guest]--;
		ans+=searchGuest(host, guest+1, scoreOfHost-1);
		score[guest]++;
	}
	if(scoreOfHost>=3)
	{
		ans+=searchGuest(host, guest+1,scoreOfHost-3);
	}
	return ans;
}

int main()
{
	n=readIn();
	for(int i=1; i<=n; i++)
	{
		score[i]=readIn();
	}
	std::sort(score+1,score+1+n);
	printf("%d",searchHost());
	return 0;
}

