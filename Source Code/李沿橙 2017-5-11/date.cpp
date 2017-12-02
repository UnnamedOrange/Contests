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

int start;
int end;
const int months[2][13]=
{
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31}
};

bool is_LeapYear(int year)
{
	if(year%400==0) return true;
	if(year%100==0) return false;
	if(year%4==0) return true;
	return false;
}

bool is_ValidDate(int date)
{
	if(date>end) return false;
	if(date<start) return false;

	int year=date/10000;
	int month=date/100%100;
	int day=date%100;

	if(month>12 || month<=0) return false;
	if(day>months[is_LeapYear(year)][month] || day<=0) return false;

	char buffer[16]= {0};
	sprintf(buffer,"%08d",date);
	int length=strlen(buffer);
	int times=length/2;
	for(int i=0; i<times; i++)
	{
		if(buffer[i]!=buffer[length-i-1])
		{
			return false;
		}
	}
	//printf("%s\n",buffer);
	return true;
}

int makeDate(int year)
{
	char buffer[16]= {0};
	sprintf(buffer,"%04d",year);
	int length=strlen(buffer);
	for(int i=0,j=2*length-1; i<length; i++,j--)
	{
		buffer[j]=buffer[i];
	}
	int ret;
	sscanf(buffer,"%d",&ret);
	return ret;
}

void run_Regular()
{
	int s=start/10000;
	int e=end/10000;
	int ans=0;
	for(int i=s; i<=e; i++)
	{
		if(is_ValidDate(makeDate(i)))
		{
			ans++;
		}
	}
	printf("%d",ans);
}

void input()
{
	scanf("%d%d",&start,&end);
}

int main()
{
#ifndef DEBUG
	freopen("date.in","r",stdin);
	freopen("date.out","w",stdout);
#endif
	input();
	run_Regular();
	return 0;
}
