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

int preCalc[13];

void run_Regular()
{
	int store=0;
	int cash=0;
	int month=0;
	for(int i=1; i<=12; i++)
	{
		cash+=300;
		if(cash<preCalc[i])
		{
			month=i;
			break;
		}
		cash-=preCalc[i];
		store+=120*(cash/100);
		cash%=100;
	}
	if(month)
	{
		printf("%d",-month);
	}
	else
	{
		printf("%d",store+cash);
	}
}

void input()
{
	for(int i=1; i<=12; i++)
	{
		scanf("%d",&preCalc[i]);
	}
}

int main()
{
#ifndef DEBUG
	freopen("save.in","r",stdin);
	freopen("save.out","w",stdout);
#endif
	input();
	run_Regular();
	return 0;
}
