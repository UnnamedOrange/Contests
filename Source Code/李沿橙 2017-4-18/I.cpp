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
using std::cin;
using std::cout;
using std::endl;

int Time,Num;
int f[1005];

int main()
{
	scanf("%d%d",&Time,&Num);
	while(Num--)
	{
		int cost,value;
		scanf("%d%d",&cost,&value);
		for(int i=Time; i>=cost; i--)
		{
			f[i]=std::max(f[i],f[i-cost]+value);
		}
	}
	printf("%d",f[Time]);
	return 0;
}
