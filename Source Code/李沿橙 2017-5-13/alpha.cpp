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
const int maxn=30;
char expression[3][maxn];
#define index(expre,alpha) expression[expre][alpha] - 'A'

namespace Regular
{
	std::map<int,int> MapTTF;
	std::vector<int> order;
	void makelist()
	{
		std::set<char> Set;
		for(int i=n-1; i>=0; i--)
		{
			for(int j=0; j<3; j++)
			{
				if(!Set.count(expression[j][i]))
				{
					Set.insert(expression[j][i]);
					order.push_back(expression[j][i]-'A');
					MapTTF[expression[j][i]-'A']=order.size()-1;
				}
			}
		}
	}

	bool vis[maxn];
	std::vector<int> sequeue;
	bool bOk;
	void print()
	{
		bool sign=false;
		for(int i=0; i<sequeue.size(); i++)
		{
			if(sign) printf(" ");
			printf("%d",sequeue[MapTTF[i]]);
			sign=true;
		}
		puts("");
	}
	bool check()
	{
		int carry=0;
		int size=sequeue.size();
		for(int i=n-1,j=0; j<n; i--,j++)
		{
			if(MapTTF[index(0,i)]>=size ||
			        MapTTF[index(1,i)]>=size ||
			        MapTTF[index(2,i)]>=size)
			{
				return true;
			}
			int num1=sequeue[MapTTF[index(0,i)]];
			int num2=sequeue[MapTTF[index(1,i)]];
			int num3=sequeue[MapTTF[index(2,i)]];
			if((num1+num2+carry)%n != num3)
			{
				return false;
			}
			carry=(num1+num2+carry)/n;
		}
		if(carry) return false;
		return true;
	}
	void search()
	{
		if(!check())
		{
			return;
		}
		if(sequeue.size()==n)
		{
			print();
			bOk=true;
			return;
		}
		for(int i=0; i<n; i++)
		{
			if(!vis[i])
			{
				sequeue.push_back(i);
				vis[i]=true;
				search();
				if(bOk) return;
				sequeue.pop_back();
				vis[i]=false;
			}
		}
	}
	void run()
	{
		makelist();
		search();
	}
}

namespace Violent
{
	bool vis[maxn];
	std::vector<int> sequeue;
	bool bOk;
	void print()
	{
		bool sign=false;
		for(int i=0; i<sequeue.size(); i++)
		{
			if(sign) printf(" ");
			printf("%d",sequeue[i]);
			sign=true;
		}
		puts("");
	}
	bool check()
	{
		int carry=0;
		int size=sequeue.size();
		for(int i=n-1,j=0; j<n; i--,j++)
		{
			if(index(0,i)>=size ||
			        index(1,i)>=size ||
			        index(2,i)>=size)
			{
				return true;
			}
			int num1=sequeue[index(0,i)];
			int num2=sequeue[index(1,i)];
			int num3=sequeue[index(2,i)];
			if((num1+num2+carry)%n != num3)
			{
				return false;
			}
			carry=(num1+num2+carry)/n;
		}
		if(carry) return false;
		return true;
	}
	void search()
	{
		if(!check())
		{
			return;
		}
		if(sequeue.size()==n)
		{
			print();
			bOk=true;
			return;
		}
		for(int i=0; i<n; i++)
		{
			if(!vis[i])
			{
				sequeue.push_back(i);
				vis[i]=true;
				search();
				if(bOk) return;
				sequeue.pop_back();
				vis[i]=false;
			}
		}
	}
	void run()
	{
		search();
	}
}

void input()
{
	scanf("%d",&n);
	for(int i=0; i<3; i++)
	{
		scanf("%s",expression[i]);
	}
}

int main()
{
#ifndef DEBUG
	freopen("alpha.in","r",stdin);
	freopen("alpha.out","w",stdout);
#endif
	input();
	if(n<=10)
		Violent::run();
	else
		Regular::run();
	return 0;
}
