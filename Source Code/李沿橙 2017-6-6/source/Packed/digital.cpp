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

int k,w;

struct LargeInt
{
	static const int carry=10000;
	std::vector<int> num;

	LargeInt(int x=1): num(1,x) //默认为1
	{

	}

	void C(int Up, int Down)
	{
		int maxi=std::max(Up, Down - Up);
		int temp=1;
		for(int i=maxi+1; i<=Down; i++)
		{
			temp*=i;
			if(temp*(i+1)>=carry)
			{
				mul(temp);
				temp=1;
			}
		}
		if(temp!=1)
		{
			mul(temp);
			temp=1;
		}
		for(int i=2; i<=Down-maxi; i++)
		{
			temp*=i;
			if(temp*(i+1)>=carry)
			{
				div(temp);
				temp=1;
			}
		}
		if(temp!=1)
		{
			div(temp);
			temp=1;
		}
	}

	void pop()
	{
		while(num.size() && !num[num.size()-1]) num.pop_back();
	}

	void update()
	{
		pop();
		for(int i=0; i<num.size(); i++)
		{
			if(num[i]>carry)
			{
				if(i+1>=num.size()) num.push_back(0);
				num[i+1]+=num[i]/carry;
				num[i]%=carry;
			}
		}
	}

	void print()
	{
		pop();
		printf("%d",num[num.size()-1]);
		for(int i=num.size()-2; i>=0; i--)
		{
			printf("%04d",num[i]);
		}
		puts("");
	}

	void add(const LargeInt &b)
	{
		pop();
		if(num.size()<b.num.size()) num.resize(b.num.size());
		for(int i=0; i<b.num.size(); i++)
		{
			num[i]+=b.num[i];
		}
		update();
	}

	void div(int x)
	{
		pop();
		int mod=0;
		int quo=0;
		for(int i=num.size()-1; i>=0; i--)
		{
			num[i]+=mod*carry;
			quo=num[i]/x;
			mod=num[i]%x;
			num[i]=quo;
		}
		pop();
	}

	void mul(int x)
	{
		pop();
		for(int i=0; i<num.size(); i++)
		{
			num[i]*=x; //x最大512，不会溢出
		}
		update();
	}
};

namespace Regular
{
	void run()
	{
		LargeInt ans(0);
		int digit=w/k;
		for(int i=2; i<=digit; i++)
		{
			if(i>(1<<k)-1) break;
			LargeInt temp;
			temp.C(i,(1<<k)-1);
			ans.add(temp);
		}
		if(w%k)
		{
			int times=std::min((1<<k)-1-digit, (1<<w%k)-1);
			for(int i=1; i<=times; i++)
			{
				LargeInt temp;
				temp.C(digit, (1<<k)-1-i);
				ans.add(temp);
			}
		}
		ans.print();
	}
	void input()
	{
		scanf("%d%d",&k,&w);
	}
}

int main()
{
	Regular::input();
	Regular::run();
	return 0;
}
