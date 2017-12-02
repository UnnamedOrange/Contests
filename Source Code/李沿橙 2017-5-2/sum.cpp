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

const int mod = 10007;
int n,m;
std::vector<int> num;
std::vector<std::vector<int> > color;
long long ans;

void input()
{
	scanf("%d%d",&n,&m);
	num.resize(n+1);
	color.resize(m+1);
	for(int i=1; i<=n; i++)
	{
		scanf("%d",&num[i]);
	}
	for(int i=1; i<=n; i++)
	{
		int input;
		scanf("%d",&input);
		color[input].push_back(i);
	}
}

void run()
{
	for(int i=1; i<=m; i++)
	{
		for(int j=0; j<color[i].size(); j++)
		{
			for(int k=j+1; k<color[i].size(); k++)
			{
				if((color[i][k]-color[i][j])%2==0)
				{
					ans=(ans+(long long)(color[i][k]+color[i][j])*(num[color[i][k]]+num[color[i][j]]))%mod;
				}
			}
		}
	}
	int temp=ans;
	printf("%d",temp);
}

int main()
{
#ifndef DEBUG
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
#endif
	input();
	run();
	return 0;
}
