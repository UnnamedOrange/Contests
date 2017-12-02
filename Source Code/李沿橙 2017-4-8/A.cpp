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

int m,k;

int main()
{
	scanf("%d%d",&m,&k);
	if(m%19!=0)
	{
		printf("NO");
		return 0;
	}
	int count_=0;
	while(m)
	{
		if(m%10==3) count_++;
		m/=10;
	}
	if(count_==k)
	{
		printf("YES");
	}
	else
	{
		printf("NO");
	}
	return 0;
}
