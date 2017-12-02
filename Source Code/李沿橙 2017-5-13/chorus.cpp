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
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;

const int maxn=105;
int n;
int height[maxn];
int f[2][maxn];

void run_Regular()
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<i; j++)
		{
			if(height[i]>height[j])
			{
				f[0][i]=std::max(f[0][i],f[0][j]+1);
			}
		}
	}

	for(int i=n-1; i>=0; i--)
	{
		for(int j=i+1; j<n; j++)
		{
			if(height[i]>height[j])
			{
				f[1][i]=std::max(f[1][i],f[1][j]+1);
			}
		}
	}

	int maxi=0;
	for(int i=0; i<n; i++)
	{
		int temp=f[0][i]+f[1][i]+1;
		if(temp>maxi)
		{
			maxi=temp;
		}
	}
	printf("%d",n-maxi);
}

void input()
{
	scanf("%d",&n);
	for(int i=0; i<n; i++)
	{
		scanf("%d",&height[i]);
	}
}

int main()
{
#ifndef DEBUG
	freopen("chorus.in","r",stdin);
	freopen("chorus.out","w",stdout);
#endif
	input();
	run_Regular();
	return 0;
}
