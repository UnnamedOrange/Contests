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
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;

int n;
struct Student
{
	char name[30];
	int averageScore;
	int commentScore;
	bool is_Leader;
	bool is_Western;
	int nArtical;

	void input()
	{
		char ch[2];
		scanf("%s",name);
		cin>>averageScore>>commentScore>>ch[0]>>ch[1]>>nArtical;
		is_Leader=ch[0]=='Y';
		is_Western=ch[1]=='Y';
	}

	int money() const
	{
		int ans=0;
		if(averageScore>80 && nArtical) ans+=8000;
		if(averageScore>85 && commentScore>80) ans+=4000;
		if(averageScore>90) ans+=2000;
		if(averageScore>85 && is_Western) ans+=1000;
		if(commentScore>80 && is_Leader) ans+=850;
		return ans;
	}
} student[105];

namespace Regular
{
	void run()
	{
		int maxindex=0;
		int maxi=0;
		int sum=0;
		for(int i=0; i<n; i++)
		{
			int money=student[i].money();
			sum+=money;
			if(money>maxi)
			{
				maxi=money;
				maxindex=i;
			}
		}
		printf("%s\n%d\n%d",student[maxindex].name,maxi,sum);
	}
};

void input()
{
	scanf("%d",&n);
	for(int i=0; i<n; i++)
	{
		student[i].input();
	}
}

int main()
{
#ifndef DEBUG
	freopen("scholar.in","r",stdin);
	freopen("scholar.out","w",stdout);
#endif
	input();
	Regular::run();
	return 0;
}
