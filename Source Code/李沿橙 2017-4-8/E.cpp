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

bool is_LeapYear(int year)
{
	if(year%400 == 0)
	{
		return true;
	}
	if(year%100 == 0)
	{
		return false;
	}
	if(year%4 == 0)
	{
		return true;
	}
	return false;
}

int year,month,day,tail;
const int months[][12] =
{
	{31,28,31,30,31,30,31,31,30,31,30,31},
	{31,29,31,30,31,30,31,31,30,31,30,31}
};

void work()
{
	char buffer[15]= {0};
	scanf("%d-%d-%d %s",&year,&month,&day,buffer);
	tail=buffer[strlen(buffer)-1];
	int y=2000,m=1,d=1,w=6-1;
	for(; y<year; y++)
	{
		w=(w+365+is_LeapYear(y))%7;
	}

	for(; m<month; m++)
	{
		w=(w+months[is_LeapYear(y)][m-1])%7;
	}

	w=(w+day-d)%7;
	d=day;
	w++;

	if(w==1 && (tail=='1' || tail=='6'))
	{
		printf("yes\n");
	}
	else if(w==2 && (tail=='2' || tail=='7'))
	{
		printf("yes\n");
	}
	else if(w==3 && (tail=='3' || tail=='8'))
	{
		printf("yes\n");
	}
	else if(w==4 && (tail=='4' || tail=='9'))
	{
		printf("yes\n");
	}
	else if(w==5 && (tail=='5' || tail=='0' || tail>='A' && tail<='Z'))
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}
}

int main()
{
	int a;
	scanf("%d",&a);
	while(a--)
	{
		work();
	}
	return 0;
}
