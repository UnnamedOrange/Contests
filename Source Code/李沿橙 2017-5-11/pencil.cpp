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

int n;
int number[3];
int price[3];

void run_Regular()
{
	int ans=0x7fffffff;
	for(int i=0; i<3; i++)
	{
		int num=n/number[i]+bool(n%number[i]);
		ans=std::min(ans,num*price[i]);
	}
	printf("%d",ans);
}

void input()
{
	scanf("%d",&n);
	for(int i=0; i<3; i++)
	{
		scanf("%d%d",&number[i],&price[i]);
	}
}

int main()
{
#ifndef DEBUG
	freopen("pencil.in","r",stdin);
	freopen("pencil.out","w",stdout);
#endif
	input();
	run_Regular();
	return 0;
}
