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

const int maxn=1050;
char buffer[maxn];
int length;

enum
{
    left_,
    right_,
    or_,
    and_,
    not_
};

std::map<char,int> symbol;

const int priority[5][5]=
{
	//     (		)		|		&		£¡
	/*(*/	false,	false,	false,	false,	false,
	/*)*/	false,	false,	true,	true,	true,
	/*|*/	false,	false,	true,	true,	true,
	/*&*/	false,	false,	false,	true,	true,
	/*!*/	false,	false,	false,	false,	false
};

bool calc_1(bool reg1,int op)
{
	if(op==not_) return !reg1;
	return false;
}

bool calc_2(bool reg1,bool reg2,int op)
{
	if(op==and_) return reg1 && reg2;
	else if(op==or_) return reg1 || reg2;
	return false;
}

void calc(std::stack<bool> &ovs,std::stack<int> &ops, int op)
{
	while(!ops.empty() && priority[op][ops.top()])
	{
		int opt=ops.top();
		ops.pop();
		if(opt==not_)
		{
			bool reg1=ovs.top();
			ovs.pop();
			ovs.push(calc_1(reg1,opt));
		}
		else
		{
			bool reg1,reg2=ovs.top();
			ovs.pop();
			reg1=ovs.top();
			ovs.pop();
			ovs.push(calc_2(reg1,reg2,opt));
		}
	}
}

void deal()
{
	std::stack<bool> ovs;
	std::stack<int> ops;
	ops.push(left_);
	for(int i=0; i<length; i++)
	{
		if(buffer[i]==' ') continue;
		if(buffer[i]=='V')
		{
			ovs.push(true);
		}
		else if(buffer[i]=='F')
		{
			ovs.push(false);
		}
		else
		{
			int op=symbol[buffer[i]];
			if(op==left_)
			{
				ops.push(left_);
			}
			else if(op==right_)
			{
				calc(ovs,ops,op);
				ops.pop();
			}
			else
			{
				calc(ovs,ops,op);
				ops.push(op);
			}
		}
	}
	calc(ovs,ops,right_);
	ops.pop();
	printf("%s\n",ovs.top()?"V":"F");
}

int main()
{
	symbol['(']=left_;
	symbol[')']=right_;
	symbol['|']=or_;
	symbol['&']=and_;
	symbol['!']=not_;
	while(cin.getline(buffer,maxn))
	{
		length=strlen(buffer);
		if(!length) continue;
		deal();
	}
	return 0;
}
