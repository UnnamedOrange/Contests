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
int num[605];
int ans;

int gcd(int x,int y)
{
	if(x%y==0) return y;
	return gcd(y,x%y);
}

int main()
{
	scanf("%d",&n);
	for(int i=0; i<n; i++)
	{
		scanf("%d",num+i);
	}

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(i==j) continue;
			int g=gcd(num[i],num[j]);
			if(g==1)
			{
				ans++;
			}
		}
	}
	printf("%d",ans/2);
	return 0;
}
