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

int n;
int cLength;
std::vector<int> arcLength;
std::vector<int> res;
int ans;

namespace Regular
{
	bool isRect()
	{
		int interval[4]= {0};
		interval[0]=cLength-arcLength[res[3]] + arcLength[res[0]];
		interval[1]=arcLength[res[1]]-arcLength[res[0]];
		interval[2]=arcLength[res[2]]-arcLength[res[1]];
		interval[3]=arcLength[res[3]]-arcLength[res[2]];
		int temp[4]= {arcLength[res[0]],arcLength[res[1]],arcLength[res[2]],arcLength[res[3]]};
		return interval[0]==interval[2] && interval[1]==interval[3];
	}

	void dfs(int iStart = 1)
	{
		if(res.size()==4)
		{
			ans+=isRect();
			return;
		}
		for(int i = iStart; i <= n; i++)
		{
			res.push_back(i);
			dfs(i+1);
			res.pop_back();
		}
	}

	void run()
	{
		dfs();
		printf("%d",ans);
	}
	void input()
	{
		n=readIn();
		arcLength.resize(n+1);
		for(int i=1; i<=n; i++)
		{
			int t = readIn();
			cLength+=t;
			arcLength[i]=arcLength[i-1] + t;
		}
	}
}

int main()
{
	Regular::input();
	Regular::run();
	return 0;
}
