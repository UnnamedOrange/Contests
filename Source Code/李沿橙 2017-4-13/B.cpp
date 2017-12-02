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

int n;
int num[7];
const int months[][12]=
{
	{ 31,28,31,30,31,30,31,31,30,31,30,31 },
	{ 31,29,31,30,31,30,31,31,30,31,30,31 }
};

bool is_LeapYear(int year)
{
	if(year%400==0) return true;
	if(year%100==0) return false;
	if(year%4==0) return true;
	return false;
}

int main()
{
	scanf("%d",&n);
	int w=0;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<12; j++)
		{
			num[(w+12)%7]++;
			w=(w+months[is_LeapYear(1900+i)][j]);
		}
	}

	printf("%d ",num[5]);
	printf("%d ",num[6]);
	for(int i=0; i<5; i++)
	{
		printf("%d ",num[i]);
	}
	return 0;
}
