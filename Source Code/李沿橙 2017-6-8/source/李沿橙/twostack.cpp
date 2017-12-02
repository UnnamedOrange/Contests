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
inline int readIn(int a = 0)
{
	scanf("%d",&a);
	return a;
}

int n;

std::vector<char> handle;
struct stack:public std::vector<int>
{
	char identity;

	stack(char identity):identity(identity)
	{
	}

	void print()
	{
		printf("%c: ",identity);
		for(int i=0; i<std::vector<int>::size(); i++)
		{
			printf("%d ", std::vector<int>::operator[](i));
		}
		puts("");
	}

	int top()
	{
		return std::vector<int>::operator[](std::vector<int>::size()-1);
	}

	void Push(const int &a)
	{
		std::vector<int>::push_back(a);
		handle.push_back(identity);
		//print();
	}

	void Pop()
	{
		std::vector<int>::pop_back();
		handle.push_back(identity+1);
		//print();
	}
} stack1('a'),stack2('c');

namespace Regular
{
	int cnt;
	void pop()
	{
		bool sign;
		do
		{
			sign=false;
			while(!stack1.empty() && stack1.top()==cnt+1)
			{
				cnt++;
				stack1.Pop();
				sign=true;
			}
			while(!stack2.empty() && stack2.top()==cnt+1)
			{
				cnt++;
				stack2.Pop();
				sign=true;
			}
		}
		while(sign);
	}

	void run()
	{

		for(int i=1; i<=n; i++)
		{
			int read=readIn();
			pop();
			if(read==cnt+1)
			{
				stack1.Push(read);
				stack1.Pop();
				cnt++;
			}
			else
			{
				if(stack1.empty())
					stack1.Push(read);
				else if(stack1.top() > read)
					stack1.Push(read);
				else if(stack2.empty())
					stack2.Push(read);
				else if(stack2.top() > read)
					stack2.Push(read);
				else
					break;
			}
			pop();
		}

		if(cnt==n)
		{
			for(int i=0; i<handle.size(); i++)
			{
				printf("%c ",handle[i]);
			}
		}
		else
		{
			puts("0");
		}
	}
	void input()
	{
		n=readIn();
	}
}

int main()
{
	Regular::input();
	Regular::run();
	return 0;
}
