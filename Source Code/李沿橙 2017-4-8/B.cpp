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

const int months[]=	{31,28,31,30,31,30,31,31,30,31,30,31};
int w;

int main()
{
	scanf("%d",&w);
	w--;
	for(int i=1; i<=12; i++)
	{
		if((w+12)%7 == 5-1)
		{
			printf("%d\n",i);
		}
		w=(w+months[i-1])%7;
	}
	return 0;
}
