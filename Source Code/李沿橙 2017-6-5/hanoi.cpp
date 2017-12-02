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

int a;
int n,m;
int f[25];

namespace Regular
{
	void outputEx()
	{
		for(int i=1; i<=n; i++)
		{
			int base=int(pow(3,i-1));
			int ans = ((m)/base)%6+1;
			if(ans>=4)
				ans=6-ans+1;
			printf("%d ",ans);
		}
		puts("");
	}
//	void output()
//	{
//		for(int i=1; i<=n; i++)
//		{
//			printf("%d ",f[i]);
//		}
//		puts("");
//	}
//	void move(int index,int from,int to)
//	{
//		if(!m) return;
//		f[index]=to;
//		m--;
//		//output();
//	}
//	void hanoi(int index, int from=1, int to=3)
//	{
//		if(from==1 && to==3)
//		{
//			hanoi(index,1,2);
//			hanoi(index,2,3);
//			return;
//		}
//		if(index==1)
//		{
//			move(index,from,to);
//			return;
//		}
//		else if(from==1 && to==2)
//		{
//			if(m) hanoi(index-1,1,2);
//			if(m) hanoi(index-1,2,3);
//			move(index,1,2);
//			if(m) hanoi(index-1,3,2);
//		}
//		else if(from==2 && to==3)
//		{
//			if(m) hanoi(index-1,2,1);
//			move(index,2,3);
//			if(m) hanoi(index-1,1,2);
//			if(m) hanoi(index-1,2,3);
//		}
//		else if(from==3 && to==2)
//		{
//			if(m) hanoi(index-1,3,2);
//			if(m) hanoi(index-1,2,1);
//			move(index,3,2);
//			if(m) hanoi(index-1,1,2);
//		}
//		else if(from==2 && to==1)
//		{
//			if(m) hanoi(index-1,2,3);
//			move(index,2,1);
//			if(m) hanoi(index-1,3,2);
//			if(m) hanoi(index-1,2,1);
//		}
//	}

	void run()
	{
		while(a--)
		{
			scanf("%d%d",&n,&m);
//			for(int i=1; i<=n; i++)
//			{
//				f[i]=1;
//			}
			//output();
			outputEx();
			//hanoi(n);
			//output();
		}
	}
	void input()
	{
		scanf("%d",&a);
	}
}

int main()
{
#ifndef DEBUG
	freopen("hanoi.in","r",stdin);
	freopen("hanoi.out","w",stdout);
#endif
	Regular::input();
	Regular::run();
	return 0;
}
